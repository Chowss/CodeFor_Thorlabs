#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    bool isNumber = false;
    ulonglong number = text.toULongLong(&isNumber);
    if (!isNumber || number < 2)
    {
        Tool::Warning("Not a valid number, please input a number between 2 ~ 18446744073709551615.");
        return;
    }

    ulonglong divNumber = 0;
    if (!Tool::isPrimeNumber(number, divNumber))
    {
        Tool::Warning(QString("Not a prime number, can be divied by %1").arg(divNumber));
        return;
    }

    Tool::Warning("It's a prime number.");
}
