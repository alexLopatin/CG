#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <QFile>


Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lightPos = QVector3D(0.0f, 0.0f, -1.7f);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    setupData();
    SetupShaders();
    SetProjection(0);
    glClearDepthf(100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_CLAMP);
    startTimer(30);

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
    glBindAttribLocation(progId, 1, "normal");
    glLinkProgram(progId);
    angleXAddr = glGetUniformLocation(progId, "angleX");
    angleYAddr = glGetUniformLocation(progId, "angleY");
    posAddr = glGetUniformLocation(progId, "lightPos");
    colorAddr = glGetUniformLocation(progId, "lightColor");
    glowAddr = glGetUniformLocation(progId, "GlowPow");
    tAddr = glGetUniformLocation(progId, "t");
    glUseProgram(progId);
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() < 0)
        scale += 0.02f;
    if(event->delta() > 0)
        scale -= 0.02f;
    if(scale < 0.5f)
        scale = 0.5f;
    if(scale > 2)
        scale = 2;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double sc = scale;
    glOrtho(-sc, sc, -sc, sc, sc, -sc);
    std::array<GLfloat, 16> projection;
    glGetFloatv(GL_PROJECTION_MATRIX, projection.data());
    glUniformMatrix4fv(glGetUniformLocation(progId, "ProjectionMatrix"), 1, GL_FALSE, projection.data());

    updateGL();
}

void Widget::SetProjection(int type)
{
    angleX = 0;
    angleY = 0;
    scale = 1.0f;
    std::array<GLfloat, 16> projection;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    \
    glGetFloatv(GL_PROJECTION_MATRIX, projection.data());
    if(type == 2)
        projection[10] = 0;
    glUniformMatrix4fv(glGetUniformLocation(progId, "ProjectionMatrix"), 1, GL_FALSE, projection.data());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(type == 1) {
        glRotatef(-35.264f, 1.0f, 0.0f, 0.0f);
        glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
    }
    glGetFloatv(GL_MODELVIEW_MATRIX, projection.data());
    glUniformMatrix4fv(glGetUniformLocation(progId, "ModelViewMatrix"), 1, GL_FALSE, projection.data());
}

void Widget::setupData()
{
    glGenBuffers(1, &bufId);
    glBindBuffer(GL_ARRAY_BUFFER, bufId);
    const GLfloat cube[] =
    {
        //first
        0.5f, 0.5f, 0.5f,

        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        //second
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        //third
        -0.5f, 0.5f, -0.5f,

        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        //four
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        //fifth
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        //sixth
        0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        //normals
        1.0f, 0, 0,
        1.0f, 0, 0,
        1.0f, 0, 0,
        1.0f, 0, 0,
        1.0f, 0, 0,
        1.0f, 0, 0,
        -1.0f, 0, 0,
        -1.0f, 0, 0,
        -1.0f, 0, 0,
        -1.0f, 0, 0,
        -1.0f, 0, 0,
        -1.0f, 0, 0,
        0, 1.0f, 0,
        0, 1.0f, 0,
        0, 1.0f, 0,
        0, 1.0f, 0,
        0, 1.0f, 0,
        0, 1.0f, 0,
        0, -1.0f, 0,
        0, -1.0f, 0,
        0, -1.0f, 0,
        0, -1.0f, 0,
        0, -1.0f, 0,
        0, -1.0f, 0,
        0, 0, 1.0f,
        0, 0, 1.0f,
        0, 0, 1.0f,
        0, 0, 1.0f,
        0, 0, 1.0f,
        0, 0, 1.0f,
        0, 0, -1.0f,
        0, 0, -1.0f,
        0, 0, -1.0f,
        0, 0, -1.0f,
        0, 0, -1.0f,
        0, 0, -1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, 216 * sizeof(GLfloat),
    cube, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>(108 * sizeof(GLfloat)));
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

void Widget::SetGlow(float val)
{
    glow = val;
    updateGL();
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
    //glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0,36);
}
