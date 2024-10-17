#ifndef CANVASAREA_H
#define CANVASAREA_H

#include <QAbstractItemModel>
#include "polygon.h"
#include <QPaintEvent>
#include <QWidget>


class CanvasArea : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasArea(QWidget *parent = nullptr);
    std::shared_ptr<Polygon> findPolygon(QPointF p);
    std::vector<Polygon> allPolygons;
    void remove(std::shared_ptr<Polygon>);
    void create(std::vector<QPointF>& ver, std::vector<QColor>& col, std::vector<int>& prop, int layer = 0);
    void paintEvent(QPaintEvent *event);

};

#endif // CANVASAREA_H
