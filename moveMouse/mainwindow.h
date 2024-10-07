#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void updateCursorPosition();

private:
    QLabel *cursorPositionLabel;
    QLabel *cursorFreezingLabel;
    QTimer *timer;
    // bool isLeftButtonPressed;
};

#endif // MAINWINDOW_H
