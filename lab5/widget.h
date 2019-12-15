#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QVector3D>

namespace Ui {
class Widget;
}

class Widget : public QGLWidget,QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void SetGlow(float val);
    void SetProjection( int type);
    QVector3D lightPos;
    void ChangeDetailLevel(int val);
protected:
    void resizeGL(int w, int h);
private:
    int mouseX = 0;
    int mouseY = 0;
    float angleX, angleY;
    float glow = 1;
    float scale = 1.0f;
    float t = 0;
    GLuint bufId;
    GLuint vshId, fshId, progId;
    GLint angleXAddr, angleYAddr, colorAddr, posAddr, glowAddr, tAddr;
    std::vector<GLfloat> GenerateObject();
    void timerEvent(QTimerEvent*);
    void paintGL();
    void initializeGL();
    void mouseMoveEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent *event);
    void SetupShaders();
    void setupData();
    int countOfVertices = 0;
    int stepsCount = 100;
    Ui::Widget *ui;
};

#endif // WIDGET_H
