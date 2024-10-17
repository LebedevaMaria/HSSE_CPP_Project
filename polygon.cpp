#include "polygon.h"
#include <QRandomGenerator>

Polygon::Polygon(std::vector<QPointF>& ver, std::vector<QColor>& col, std::vector<int>& prop, int layerNew) {
    if (layerNew > 0){
        layer = layerNew;
    } else {
        layer = all_layers;
        all_layers++;
    }
    for (int i = 0; i < ver.size(); i++) {
        std::shared_ptr<Edge> edge(new Edge);
        edges.push_back(edge);
        std::shared_ptr<Vertex> vertex(new Vertex);
        vertices.push_back(vertex);
    }

    for (int i = 0; i  < ver.size(); i++){
        vertices[i]->edge1 = edges[i];
        vertices[i]->edge2 = edges[(i + 1) % ver.size()];
        vertices[i]->position = ver[i];

        edges[i]->color = col[i];
        edges[i]->vertex1 = vertices[i];
        edges[i]->vertex2 = vertices[(i + 1) % ver.size()];
        edges[i]->line.setPoints(ver[i], ver[(i + 1) % ver.size()]);
        edges[i]->property = prop[i];
    }

    all_layers = std::max(all_layers, layer);
}

void Polygon::finalize(QPainter &painter){
    QPen pen;
    for (int i = 0; i < edges.size(); i++){
        std::shared_ptr<Edge> edge = edges[i];
        pen.setColor(edge->color);
        painter.setPen(pen);
        painter.drawLine(edge->line);
    }
}

std::vector<QColor> Polygon::getColorsEdges(){
    std::vector<QColor> colorsEdges(edges.size());
    for (int i = 0; i < edges.size(); i++){
        colorsEdges[i] = edges[i]->color;
    }
    return colorsEdges;
}

std::vector<std::pair<int, int>> Polygon::getCoords(){
    std::vector<std::pair<int, int>> coords(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        std::pair<int, int> coord(vertices[i]->position.x(), vertices[i]->position.y());
        coords[i] = coord;
    }
    return coords;
}

std::vector<int> Polygon::getProperties(){
    std::vector<int> properties(edges.size());
    for (int i = 0; i < edges.size(); i++){
        properties[i] = edges[i]->property;
    }
    return properties;
}

bool Polygon::findPoint(QPointF &point) {
    bool flag = true;
    int firstCoord;
    int secondCoord;
    while (flag){
        int count = 0;
        firstCoord = QRandomGenerator::global()->bounded(1000, 2000);
        secondCoord = QRandomGenerator::global()->bounded(1000, 2000);
        QLineF lineP{point, QPoint(firstCoord, secondCoord)};
        for (int i = 0; i < edges.size(); i++){
            QPointF inter;
            auto ans = lineP.intersects(edges[i]->line, &inter);
            if (ans != 1){
                continue;
            }
            if (edges[i]->vertex1.lock()->position == inter || edges[i]->vertex2.lock()->position == inter){
                count++;
            }
        }
        if (count == 0){
            flag = false;
        }
    }
    QLineF lineP{point, QPoint(firstCoord, secondCoord)};
    int count = 0;
    for (int i = 0; i < edges.size(); i++){
        QPointF inter;
        auto ans = lineP.intersects(edges[i]->line, &inter);
        if (ans != 1){
            continue;
        }
        if (inter == point) {
            return true;
        }
        count++;
    }
    return count % 2 == 1;
}
