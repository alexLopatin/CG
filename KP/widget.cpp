#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QMatrix4x4>

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lightPos = QVector3D(-3.0f, 0.0f, 5.0f);
    scale = 3;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() < 0)
        scale += 0.02f;
    if(event->delta() > 0)
        scale -= 0.02f;
    if(scale < 0.5f)
        scale = 0.5f;
    if(scale > 6)
        scale = 6;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double sc = scale;
    glOrtho(-sc, sc, -sc, sc, -sc, sc);
    std::array<GLfloat, 16> projection;
    glGetFloatv(GL_PROJECTION_MATRIX, projection.data());
    glUniformMatrix4fv(glGetUniformLocation(progId, "ProjectionMatrix"), 1, GL_FALSE, projection.data());
    glLoadIdentity();
    updateGL();
}

void Widget::SetMode(int i)
{
    mode = i;
    updateGL();
}

void Widget::SetupShaders()
{
    vshId = glCreateShader(GL_VERTEX_SHADER);
    QFile f("complex.vert");
    f.open(QFile::ReadOnly | QFile::Text);
    QByteArray buf(f.readAll());
    f.close();
    const char* src(buf.data());
    glShaderSource(vshId, 1, &src, 0);
    glCompileShader(vshId);
    fshId = glCreateShader(GL_FRAGMENT_SHADER);
    f.setFileName("complex.frag");
    f.open(QFile::ReadOnly | QFile::Text);
    buf = f.readAll();
    src = buf.data();
    glShaderSource(fshId, 1, &src, 0);
    glCompileShader(fshId);
    progId = glCreateProgram();
    glAttachShader(progId, vshId);
    glAttachShader(progId, fshId);
    glBindAttribLocation(progId, 0, "pos");
    glLinkProgram(progId);
    angleXAddr = glGetUniformLocation(progId, "angleX");
    angleYAddr = glGetUniformLocation(progId, "angleY");
    posAddr = glGetUniformLocation(progId, "lightPos");
    colorAddr = glGetUniformLocation(progId, "lightColor");
    glowAddr = glGetUniformLocation(progId, "GlowPow");
    tAddr = glGetUniformLocation(progId, "t");
    glUseProgram(progId);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double sc = scale;
    glOrtho(-sc, sc, -sc, sc, -sc, sc);
    std::array<GLfloat, 16> projection;
    glGetFloatv(GL_PROJECTION_MATRIX, projection.data());
    glUniformMatrix4fv(glGetUniformLocation(progId, "ProjectionMatrix"), 1, GL_FALSE, projection.data());
    glLoadIdentity();

}

void Widget::SetGlow(float val)
{
    glow = val;
    updateGL();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearDepthf(100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    SetupShaders();
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3.0f, 4.0f, 0.0f, 1.0f, 12.0f, 4.0f, &points[0][0][0]);
    glMapGrid2f(20, 0, 1, 20, 0, 1);
}

void Widget::LoadFile()
{
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Загрузить массив вершин"), "/", tr(""));
    std::ifstream instr;
    instr.open(fileName.toUtf8().constData());

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            float x, y, z;
            instr >> x >> y >> z;
            points[i][j][0] = x;
            points[i][j][1] = y;
            points[i][j][2] = z;
        }
    }
    instr.close();
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3.0f, 4.0f, 0.0f, 1.0f, 12.0f, 4.0f, &points[0][0][0]);

    glMapGrid2f(20, 0, 1, 20, 0, 1);
    updateGL();
}

void Widget::timerEvent(QTimerEvent*)
{
    t+= 0.02f;
    updateGL();
}

void Widget::resizeGL(int w, int h)
{
    if(w > h)
        glViewport(0,-(w-h)/2,w,w);
    else
        glViewport((w-h)/2,0,h,h);
}

void Widget::mouseMoveEvent(QMouseEvent * event)
{
    if(event->globalX()-mouseX > 0)
        angleY += 2;
    if(event->globalX()-mouseX < 0)
        angleY -= 2;
    if( abs(angleY) >=360)
        angleY = 0;
    if(event->globalY()-mouseY > 0)
        angleX += 2;
    if(event->globalY()-mouseY < 0)
        angleX -= 2;
    if( abs(angleX) >=360)
        angleX = 0;
    mouseX = event->globalX();
    mouseY = event->globalY();
    updateGL();
}

void Widget::ResetLines()
{
    isLinesVisible = !isLinesVisible;
    updateGL();
}

void DrawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void Widget::DrawLines()
{
    glUseProgram(0);
    glColor3f(1,0,0);

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            const float k(3.1415926535897932 / 180);
            QMatrix4x4 rotX(1, 0, 0, 0, 0, cos(-angleX*k), sin(-angleX*k), 0, 0, -sin(-angleX*k), cos(-angleX*k), 0, 0, 0, 0, 1);
            QMatrix4x4 rotY(cos(angleY*k), 0, -sin(angleY*k), 0, 0, 1, 0, 0, -sin(angleY*k), 0, cos(angleY*k), 0, 0, 0, 0, 1);
            //rotY.setToIdentity();
            if(i < 3)
            {

                QVector3D first(points[i][j][0]/scale, points[i][j][1]/scale, -points[i][j][2]/scale);
                first = first*rotX * rotY;
                QVector3D second(points[i + 1][j][0]/scale, points[i + 1][j][1]/scale, -points[i + 1][j][2]/scale);
                second = second*rotX * rotY;
                DrawLine(first.x(), first.y(), second.x(), second.y());
            }

            if(j < 3)
            {

                QVector3D first(points[i][j][0]/scale, points[i][j][1]/scale, -points[i][j][2]/scale);
                first = first*rotX * rotY;
                QVector3D second(points[i][j+ 1][0]/scale, points[i][j + 1][1]/scale, -points[i][j + 1][2]/scale);
                second = second*rotX * rotY;
                DrawLine(first.x(), first.y(), second.x(), second.y());
            }
        }
    }





    glUseProgram(progId);
}



void Widget::paintGL()
{
    const float k(3.1415926535897932 / 180);
    glUniform1f(angleXAddr, angleX * k);
    glUniform1f(angleYAddr, angleY * k);
    glUniform1f(glowAddr, glow);
    glUniform1f(tAddr, t);
    glUniform3f(posAddr, lightPos.x(), lightPos.y(), lightPos.z());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEvalMesh2(mode, 0, 20, 0, 20);
    if(isLinesVisible)
        DrawLines();
}
