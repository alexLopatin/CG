#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    {
    ui->x1->setText(QString::number(ui->openGLWidget->points[0].x()));
    ui->x2->setText(QString::number(ui->openGLWidget->points[1].x()));
    ui->x3->setText(QString::number(ui->openGLWidget->points[2].x()));
    ui->x4->setText(QString::number(ui->openGLWidget->points[3].x()));
    ui->x5->setText(QString::number(ui->openGLWidget->points[4].x()));
    ui->y1->setText(QString::number(ui->openGLWidget->points[0].y()));
    ui->y2->setText(QString::number(ui->openGLWidget->points[1].y()));
    ui->y3->setText(QString::number(ui->openGLWidget->points[2].y()));
    ui->y4->setText(QString::number(ui->openGLWidget->points[3].y()));
    ui->y5->setText(QString::number(ui->openGLWidget->points[4].y()));
    connect(ui->x1, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[0].setX(ui->x1->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->x2, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[1].setX(ui->x2->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->x3, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[2].setX(ui->x3->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->x4, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[3].setX(ui->x4->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->x5, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[4].setX(ui->x5->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->y1, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[0].setY(ui->y1->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->y2, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[1].setY(ui->y2->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->y3, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[2].setY(ui->y3->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->y4, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[3].setY(ui->y4->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->y5, &QTextEdit::textChanged, this, [=]() {ui->openGLWidget->points[4].setY(ui->y5->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    }
}

void MainWindow::ChangeValue()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

