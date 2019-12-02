#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>


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
    void setA(float val);
    void setB(float val);
private:
    float max = 1;
    void paintGL();
    void initializeGL();
    void DrawCurve(int stepCount);
    void DrawLine(float x1, float y1, float x2, float y2);
    Ui::Widget *ui;
};

#endif // WIDGET_H
