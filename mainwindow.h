#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "polygon.h"
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void edit(int row, int column);
    void on_table_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    void addVertex();
    void mousePressEvent(QMouseEvent* event);
    void drawPolygon();
    void clear();
    void choiseColor();
    QColor color = Qt::black;
    std::shared_ptr<Polygon> polygon = nullptr;
};
#endif // MAINWINDOW_H
