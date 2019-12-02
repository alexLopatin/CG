#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setText(  QString::number(ui->openGLWidget->a));
    ui->textEdit_2->setText(  QString::number(ui->openGLWidget->b));
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::ChangeA);
    connect(ui->textEdit_2, &QTextEdit::textChanged, this, &MainWindow::ChangeB);
}

void MainWindow::ChangeA()
{
    QString added = ui->textEdit->toPlainText();
    float a = added.toFloat();
    ui->openGLWidget->setA(a);
}
void MainWindow::ChangeB()
{
    QString added = ui->textEdit_2->toPlainText();
    float b = added.toFloat();
    ui->openGLWidget->setB(b);
}

MainWindow::~MainWindow()
{
    delete ui;
}

