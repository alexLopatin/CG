#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <algorithm>

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    points.push_back(QVector2D(1, 2));
    points.push_back(QVector2D(3, 4));
    points.push_back(QVector2D(5, 6));
    points.push_back(QVector2D(7, 8));
    points.push_back(QVector2D(9, 10));
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
    //float mY = std::max(abs(MinY()), abs(MaxY()));
    float middle = (Max() + Min())/2;
    glBegin(GL_LINES);
        glVertex2f(2*(x1-middle)/(Max() - Min()), y1/MaxY);
        glVertex2f(2*(x2-middle)/(Max() - Min()), y2/MaxY);
    glEnd();
}



float Widget::Lagrange(float x)
{
    float res = 0;
    for(int i = 0; i <(int)points.size(); i++ )
    {
        float l = points[i].y();
        for(int j = 0; j < (int)points.size(); j++)
        {
            if(j == i)
                continue;
            l *= (x - points[j].x())/(points[i].x() - points[j].x());
        }
        res += l;
    }
    return res;
}

float Widget::Min()
{
    float min = 100000000;
    for(int i = 0; i <(int)points.size(); i++ )
        if(min > points[i].x())
            min = points[i].x();
    return min;

}

float Widget::Max()
{
    float max = -100000000;
    for(int i = 0; i <(int)points.size(); i++ )
        if(max < points[i].x())
            max = points[i].x();
    return max;

}

void Widget::FindMax(int stepCount)
{
    float x = Min();
    float dist = Max() - Min();
    for(int i = 0; i < stepCount; i++)
    {
        float y0 = Lagrange(x);
        float y1 = Lagrange(x + dist/stepCount);
        if(MaxY < std::max(abs(y0), abs(y1)))
            MaxY = std::max(abs(y0), abs(y1));
        x += dist/stepCount;
    }
}

void Widget::DrawCurve(int stepCount)
{
    float x = Min();
    float dist = Max() - Min();
    for(int i = 0; i < stepCount; i++)
    {
        float y0 = Lagrange(x);
        float y1 = Lagrange(x + dist/stepCount);
        DrawLine(x, y0, x + dist/stepCount, y1);
        x += dist/stepCount;
    }
}

void Widget::paintGL()
{
    glViewport(0,0,width(),height());
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    MaxY = 0;
    FindMax(1000);
    DrawCurve(1000);
}
