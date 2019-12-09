#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->textEdit, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->SetGlow(ui->textEdit->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->radioButton, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetProjection(0); ui->openGLWidget->updateGL();});
    connect(ui->radioButton_2, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetProjection(1); ui->openGLWidget->updateGL();});
    connect(ui->radioButton_3, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetProjection(2); ui->openGLWidget->updateGL();});
    connect(ui->textEdit_2, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->lightPos.setX(ui->textEdit_2->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->textEdit_3, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->lightPos.setY(ui->textEdit_3->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->textEdit_4, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->lightPos.setZ(ui->textEdit_4->toPlainText().toFloat()); ui->openGLWidget->updateGL();});

}


MainWindow::~MainWindow()
{
    delete ui;
}

