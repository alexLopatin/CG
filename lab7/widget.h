#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QVector2D>
#include <vector>

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    float a = 1;
    float b = 2;
    std::vector<QVector2D> points;
private:
    void paintGL();
    void initializeGL();
    float Lagrange(float x);
    float Min();
    float Max();
    float MaxY = 1;
    void DrawCurve(int stepCount);
    void FindMax(int stepCount);
    void DrawLine(float x1, float y1, float x2, float y2);
    Ui::Widget *ui;
};

#endif // WIDGET_H
