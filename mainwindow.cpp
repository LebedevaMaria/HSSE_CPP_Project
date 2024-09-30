#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::print_message);
    connect(ui->secondButton, &QPushButton::clicked, this, &MainWindow::event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print_message(){
    qDebug() << "Button clicked";
    QString new_text = ui->textInput->toPlainText();
    qDebug() << "Input text: " << new_text ;
    ui->textOutput->setPlainText(new_text);
    qDebug() << "Text output";
}

void MainWindow::event(){
    qDebug() << "Second button clicked";
    ui->secondButton->setCheckable(true);
    qDebug() << "Second button awaits event";
}

// void MainWindow::on_sendButton_clicked()
// {
    // QString new_text = ui->textInput->toPlainText();
    // ui->textOutput->setPlainText(new_text);
// }

