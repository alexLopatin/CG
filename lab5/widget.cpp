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

QVector3D CalculateNormal(QVector3D a, QVector3D b, QVector3D c)
{
    return QVector3D::normal(a,b,c);
}

std::vector<GLfloat> Widget::GenerateObject()
{
    std::vector<GLfloat> data;
    float a = 0.5f;
    float b = 0.25f;
    float x = -a;
    float y = 0;
    float z = -0.5f;
    for(int i = 1; i <= stepsCount ; i++)
    {
        y = b*sqrt(abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);

        data.push_back(-a);
        data.push_back(0);
        data.push_back(z);

        x += 2*a / stepsCount;
        y = b*sqrt(abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);
        x -= 2*a / stepsCount;
        //======================
        data.push_back(-a);
        data.push_back(0);
        data.push_back(z);
        y = -b*sqrt( abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);
        x += 2*a / stepsCount;
        y = -b*sqrt(abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);
    }
    data.push_back(-a);
    data.push_back(0);
    data.push_back(z);
    data.push_back(x);
    data.push_back(y);
    data.push_back(z);
    data.push_back(x);
    data.push_back(-y);
    data.push_back(z);
    std::vector<QVector3D> normals;
    a *=0.6f;
    b *=0.6f;
    z = 0.5f;
    x = -a;
    for(int i = 1; i <= stepsCount; i++)
    {
        data.push_back(-a);
        data.push_back(0);
        data.push_back(z);
        y = b*sqrt(abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);
        x += 2*a / stepsCount;
        y = b*sqrt(abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);
        x -= 2*a / stepsCount;
        //======================

        y = -b*sqrt(abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);

        data.push_back(-a);
        data.push_back(0);
        data.push_back(z);

        x += 2*a / stepsCount;
        y = -b*sqrt(abs(1- x*x/(a*a)));
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);
    }
    data.push_back(-a);
    data.push_back(0);
    data.push_back(z);
    data.push_back(x);
    data.push_back(y);
    data.push_back(z);
    data.push_back(x);
    data.push_back(-y);
    data.push_back(z);
    a = 0.5f;
    b = 0.25f;
    float xU = -a*0.6f;
    float xD = -a;
    float yU = 0;
    float yD = 0;
    z = 0.5f;

    for(int i = 1; i <= stepsCount; i++)
    {
        QVector3D first(xU, yU, z);
        data.push_back(xU);
        data.push_back(yU);
        data.push_back(z);

        data.push_back(xD);
        data.push_back(yD);
        data.push_back(-z);
        QVector3D second(xD, yD, -z);

        xU += 2*a*0.6f / stepsCount;
        yU = 0.6f*b*sqrt(abs(1- xU*xU/(a*a*0.6f*0.6f)));
        data.push_back(xU);
        data.push_back(yU);
        data.push_back(z);
        QVector3D third(xU, yU, z);
        QVector3D normal = CalculateNormal(first, second,third);
        normals.push_back(normal);

        first = QVector3D(xD, yD, -z);
        data.push_back(xD);
        data.push_back(yD);
        data.push_back(-z);

        xD += 2*a / stepsCount;
        yD = b*sqrt(abs(1- xD*xD/(a*a)));

        second = QVector3D(xD, yD, -z);
        data.push_back(xD);
        data.push_back(yD);
        data.push_back(-z);

        third = QVector3D(xU, yU, z);
        data.push_back(xU);
        data.push_back(yU);
        data.push_back(z);

        normal = CalculateNormal(first, second, third);
        normals.push_back(normal);
    }

    xU = -a*0.6f;
    xD = -a;
    yU = 0;
    yD = 0;

    for(int i = 1; i <= stepsCount; i++)
    {
        data.push_back(xD);
        data.push_back(yD);
        data.push_back(-z);
        QVector3D second(xD, yD, -z);

        QVector3D first(xU, yU, z);
        data.push_back(xU);
        data.push_back(yU);
        data.push_back(z);


        xU += 2*a*0.6f / stepsCount;
        yU = -0.6f*b*sqrt(abs(1- xU*xU/(a*a*0.6f*0.6f)));
        data.push_back(xU);
        data.push_back(yU);
        data.push_back(z);
        QVector3D third(xU, yU, z);
        QVector3D normal = CalculateNormal(first, second,third);
        normals.push_back(-normal);

        first = QVector3D(xD, yD, -z);
        data.push_back(xD);
        data.push_back(yD);
        data.push_back(-z);

        xD += 2*a / stepsCount;
        yD = -b*sqrt(abs(1- xD*xD/(a*a)));

        third = QVector3D(xU, yU, z);
        data.push_back(xU);
        data.push_back(yU);
        data.push_back(z);

        second = QVector3D(xD, yD, -z);
        data.push_back(xD);
        data.push_back(yD);
        data.push_back(-z);

        normal = CalculateNormal(first, second, third);
        normals.push_back(-normal);
    }
    data.push_back(xU);
    data.push_back(yU);
    data.push_back(z);
    QVector3D first(xU, yU, z);
    data.push_back(xU);
    data.push_back(-yU);
    data.push_back(z);
    QVector3D second(xU, -yU, z);
    data.push_back(xD);
    data.push_back(yD);
    data.push_back(-z);
    QVector3D third(xU, yU, -z);
    normals.push_back(CalculateNormal(first,second,third));

    data.push_back(xU);
    data.push_back(-yU);
    data.push_back(z);
    first = QVector3D(xU, -yU, z);
    data.push_back(xD);
    data.push_back(-yD);
    data.push_back(-z);
    second = QVector3D(xD, -yD, -z);
    data.push_back(xD);
    data.push_back(yD);
    data.push_back(-z);
    third = QVector3D(xD, yD, -z);
    normals.push_back(CalculateNormal(first,second,third));

    countOfVertices = data.size();
    for(int i = 1; i <= 3*(2*stepsCount + 1); i++)
    {
        data.push_back(0);
        data.push_back(0);
        data.push_back(-1);

    }
    for(int i = 1; i <= 3*(2*stepsCount + 1); i++)
    {
        data.push_back(0);
        data.push_back(0);
        data.push_back(1);

    }

    for(int i = 0; i < normals.size(); i++)
    {
        data.push_back(normals[i].x());
        data.push_back(normals[i].y());
        data.push_back(normals[i].z());
        data.push_back(normals[i].x());
        data.push_back(normals[i].y());
        data.push_back(normals[i].z());
        data.push_back(normals[i].x());
        data.push_back(normals[i].y());
        data.push_back(normals[i].z());
    }

    return data;

}

void Widget::ChangeDetailLevel(int val)
{
    if(val > 1000)
        val = 1000;
    stepsCount = val;
    setupData();
    updateGL();
}

void Widget::setupData()
{
    glGenBuffers(1, &bufId);
    glBindBuffer(GL_ARRAY_BUFFER, bufId);
    std::vector<GLfloat> data = GenerateObject();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat),
    data.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>((int)countOfVertices * sizeof(GLfloat)));
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
    glDrawArrays(GL_TRIANGLES, 0,countOfVertices);
}
