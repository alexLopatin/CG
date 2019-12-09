#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <algorithm>

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL()
{
    glClearColor(0.0,0.0,0.5,1.0);
}



void Widget::DrawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        //glVertex2f(x1, y1);
        //glVertex2f(x2, y2);
        glVertex2f(x1/max, y1/max);
        glVertex2f(x2/max, y2/max);
    glEnd();
}

void Widget::setA(float val)
{
    a = val;
    updateGL();
}

void Widget::setB(float val)
{
    b = val;
    updateGL();
}

void Widget::DrawScreenLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void Widget::DrawCoords()
{
    DrawScreenLine(-1, 0, 1, 0);
    DrawScreenLine(0, -1, 0, 1);
    DrawScreenLine(0.04, 0.96, 0, 1);
    DrawScreenLine(-0.04, 0.96, 0, 1);
    DrawScreenLine(0.96, 0.04, 1, 0);
    DrawScreenLine(0.96, -0.04, 1, 0);
}

void Widget::DrawCurve(int stepCount)
{
    float x = -a;
    for(int i = 0; i < stepCount; i++)
    {
        float y0 = b*sqrt(1- (x*x)/(a*a));
        float y1 = b*sqrt(1- ((x+2*a / stepCount)*(x+2*a / stepCount))/(a*a));

        DrawLine(x, y0, x+2*a / stepCount, y1);
        DrawLine(x, -y0, x+2*a / stepCount, -y1);
        x += 2*a / stepCount;
    }
    x -= 2*a / stepCount;
    DrawLine(x, b*sqrt(1- (x*x)/(a*a)), x, -b*sqrt(1- (x*x)/(a*a)));
}

void Widget::paintGL()
{
    if(width() > height())
        glViewport((width()-height())/2,0,height(),height());
    else
        glViewport(0,(height()-width())/2,width(),width());
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    max = std::max(a, b);
    DrawCoords();
    DrawCurve(1000);
}
