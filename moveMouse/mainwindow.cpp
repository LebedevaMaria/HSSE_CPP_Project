#include "mainwindow.h"
#include <QVBoxLayout>
#include <QCursor>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(600, 600);
    this->setFixedSize(600, 600);

    cursorPositionLabel = new QLabel(this);
    cursorPositionLabel->setAlignment(Qt::AlignCenter);
    cursorPositionLabel->setText("Позиция курсора относительно левого нижнего угла: (0, 0)");

    cursorFreezingLabel = new QLabel(this);
    cursorFreezingLabel->setAlignment(Qt::AlignCenter);
    cursorFreezingLabel->setText("Координаты при нажатии: (0, 0)");


    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(cursorPositionLabel);
    layout->addWidget(cursorFreezingLabel);
    setCentralWidget(centralWidget);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCursorPosition);
    timer->start(10);
}

MainWindow::~MainWindow()
{
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {

        int windowHeight = this->height();


        QPoint cursorPos = mapFromGlobal(QCursor::pos());
        int x = cursorPos.x();
        int y = windowHeight - cursorPos.y();


        cursorFreezingLabel->setText(QString("Координаты при нажатии: (%1, %2)").arg(x).arg(y));
    }
}

void MainWindow::updateCursorPosition()
{

    int windowHeight = this->height();


    QPoint cursorPos = mapFromGlobal(QCursor::pos());
    int x = cursorPos.x();
    int y = windowHeight - cursorPos.y();


    cursorPositionLabel->setText(QString("Позиция курсора относительно левого нижнего угла: (%1, %2)").arg(x).arg(y));

}
