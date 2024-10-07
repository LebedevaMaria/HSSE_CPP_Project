#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // textureImage.load("texture.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(5);


    QBrush brush;
    // brush.setTextureImage(textureImage);
    // brush.setColor(Qt::green);
    // brush.setStyle(Qt::HorPattern);

    painter.setPen(pen);
    painter.setBrush(QBrush(":/texture.png"));

    // QPolygon p;
    // p << QPoint(50, 50) << QPoint(100, 150) << QPoint(200, 50) << QPoint(90, 90);
    // painter.drawPolygon(p);

    painter.drawRect(100, 100, 400, 200);
    // painter.drawEllipse(100, 100, 300, 300);
    // painter.drawLine(200, 200, 500, 500);
    painter.end();
}
