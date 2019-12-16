#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->textEdit, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->SetGlow(ui->textEdit->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->radioButton, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetMode(GL_FILL); ui->openGLWidget->updateGL();});
    connect(ui->radioButton_2, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetMode(GL_LINE); ui->openGLWidget->updateGL();});
    connect(ui->radioButton_3, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->SetMode(GL_POINT); ui->openGLWidget->updateGL();});
    connect(ui->checkBox, &QRadioButton::clicked, ui->openGLWidget, [=]() {ui->openGLWidget->ResetLines(); ui->openGLWidget->updateGL();});

        connect(ui->textEdit_2, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->lightPos.setX(ui->textEdit_2->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
        connect(ui->textEdit_3, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->lightPos.setY(ui->textEdit_3->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
        connect(ui->textEdit_4, &QTextEdit::textChanged, ui->openGLWidget, [=]() {ui->openGLWidget->lightPos.setZ(ui->textEdit_4->toPlainText().toFloat()); ui->openGLWidget->updateGL();});
    connect(ui->pushButton, &QPushButton::released, ui->openGLWidget, [=]() {ui->openGLWidget->LoadFile();});

}


MainWindow::~MainWindow()
{
    delete ui;
}

