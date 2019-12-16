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
    QVector3D lightPos;
    void SetGlow(float val);
    void SetMode(int i);
    void LoadFile();
    void ResetLines();
protected:
    void resizeGL(int w, int h);
private:
    GLfloat points[4][4][3]= {
        { {-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
          {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
        {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
         {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
        {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
         {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
        {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
         {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
    };
    void DrawLines();
    int mode = GL_FILL;
    bool isLinesVisible = 0;
    int mouseX = 0;
        int mouseY = 0;
        float angleX, angleY;
        float glow = 1;
        float scale = 1.0f;
        float t = 0;
        GLuint vshId, fshId, progId;
        GLint angleXAddr, angleYAddr, colorAddr, posAddr, glowAddr, tAddr;
    void paintGL();
    void SetupShaders();

    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void timerEvent(QTimerEvent*);

    void initializeGL();
    Ui::Widget *ui;
};

#endif // WIDGET_H
