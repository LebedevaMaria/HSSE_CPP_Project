#include "canvasarea.h"
#include <QPainter>

CanvasArea::CanvasArea(QWidget *parent)
    : QWidget(parent)
{}

void CanvasArea::create(std::vector<QPointF>& ver, std::vector<QColor>& col, std::vector<int>& prop, int layer){
    Polygon polygon(ver, col, prop, layer);
    allPolygons.push_back(polygon);
}

void CanvasArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.begin(this);
    for (int i = 0; i < allPolygons.size(); i++){
        allPolygons[i].finalize(painter);
    }
    painter.end();
}

void CanvasArea::remove(std::shared_ptr<Polygon> pol) {
    int layer = pol->layer;
    auto findPolygon = std::find_if(allPolygons.begin(), allPolygons.end(), [layer](Polygon& p) {return p.layer == layer;});
    allPolygons.erase(findPolygon);
}

std::shared_ptr<Polygon> CanvasArea::findPolygon(QPointF p){
    std::vector<std::shared_ptr<Polygon>> insidePoint;
    for (int i = 0; i < allPolygons.size(); i++){
        if (allPolygons[i].findPoint(p)){
            insidePoint.push_back(std::make_shared<Polygon>(allPolygons[i]));
        }
    }
    if (insidePoint.size() == 0){
        return nullptr;
    }
    std::shared_ptr<Polygon> maxPolygon = insidePoint[0];
    int maxLayer = insidePoint[0]->layer;
    for (int i = 1; i < insidePoint.size(); i++){
        if (insidePoint[i]->layer > maxLayer) {
            maxLayer = insidePoint[i]->layer;
            maxPolygon = insidePoint[i];
        }
    }
    return maxPolygon;
}



