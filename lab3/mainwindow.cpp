#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->radioButton, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetProjection(0); ui->openGLWidget->updateGL();});
    connect(ui->radioButton_2, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetProjection(1); ui->openGLWidget->updateGL();});
    connect(ui->radioButton_3, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetProjection(2); ui->openGLWidget->updateGL();});
    connect(ui->detail, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->ChangeDetailLevel( ui->detail->toPlainText().toInt());});

}


MainWindow::~MainWindow()
{
    delete ui;
}

