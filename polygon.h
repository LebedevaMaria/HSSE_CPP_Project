#ifndef POLYGON_H
#define POLYGON_H

#include <QPointF>
#include <QLineF>
#include <QColor>
#include <vector>
#include <memory>
#include <QPen>
#include <QPainter>

struct Edge;

struct Vertex {
    QPointF position;
    std::weak_ptr<Edge> edge1;
    std::weak_ptr<Edge> edge2;
};

struct Edge {
    std::weak_ptr<Vertex> vertex1;
    std::weak_ptr<Vertex> vertex2;
    int property;
    QColor color = Qt::black;
    QLineF line;
};

class Polygon {
public:
    Polygon(std::vector<QPointF>& ver, std::vector<QColor>& col, std::vector<int>& properties, int layer = 0);

    void finalize(QPainter &painter);
    bool findPoint(QPointF &point);
    std::vector<QColor> getColorsEdges();
    std::vector<std::pair<int, int>> getCoords();
    std::vector<int> getProperties();

    std::vector<std::shared_ptr<Vertex>> vertices;
    std::vector<std::shared_ptr<Edge>> edges;
    int layer;
    static inline int all_layers = 1;
};

#endif // POLYGON_H
