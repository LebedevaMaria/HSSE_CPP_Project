#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->coordX->setMaximum(400);
    ui->coordY->setMaximum(500);
    ui->table->horizontalHeader()->setStretchLastSection(true);
    ui->addPolygon->setEnabled(false);

    connect(ui->addColor, &QPushButton::released, this, &MainWindow::choiseColor);
    connect(ui->addVertex, &QPushButton::released, this, &MainWindow::addVertex);
    connect(ui->addPolygon, &QPushButton::released, this, &MainWindow::drawPolygon);
    connect(ui->newPolygon, &QPushButton::released, this, &MainWindow::clear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choiseColor() {
    QColorDialog dialog;
    color = dialog.getColor();
    QString style = QString("background-color:rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue());
    ui->addColor->setStyleSheet(style);
}

void MainWindow::clear(){
    ui->table->setRowCount(0);
    ui->Menu->setVisible(true);
    ui->property->setValue(0);
    ui->coordY->setValue(0);
    ui->coordX->setValue(0);
    ui->addPolygon->setEnabled(false);
}

void MainWindow::addVertex(){
    int countVertices = ui->table->rowCount();
    int prop = ui->property->value();
    int secondCoord = ui->coordY->value();
    int firstCoord = ui->coordX->value();
    ui->table->insertRow(countVertices);
    ui->table->setItem(countVertices, 0, new QTableWidgetItem(QString::number(firstCoord)));
    ui->table->setItem(countVertices, 1, new QTableWidgetItem(QString::number(secondCoord)));
    ui->property->setValue(0);
    ui->coordY->setValue(0);
    ui->table->setItem(countVertices, 2, new QTableWidgetItem(QString::number(prop)));
    ui->coordX->setValue(0);
    ui->table->setItem(countVertices, 3, new QTableWidgetItem());
    ui->table->item(countVertices, 3)->setBackground(color);
    countVertices = ui->table->rowCount();
    if(countVertices > 3) {
        ui->addPolygon->setEnabled(true);
    }
}

void MainWindow::drawPolygon(){
    std::vector<QPointF> vertices;
    std::vector<QColor> edgesColor;
    std::vector<int> properties;
    int countVertices = ui->table->rowCount();
    for(int row = 0; row < countVertices; row++){
        int firstCoord = ui->table->item(row, 0)->text().toInt();
        int secondCoord = ui->table->item(row, 1)->text().toInt();
        firstCoord = std::min(firstCoord, 400);
        secondCoord = std::min(secondCoord, 500);
        int prop = ui->table->item(row, 2)->text().toInt();
        QColor edgeColor = ui->table->item(row, 3)->background().color();
        QPointF ver(firstCoord, secondCoord);
        vertices.push_back(ver);
        properties.push_back(prop);
        edgesColor.push_back(edgeColor);
    }
    if (polygon == nullptr) {
        ui->canvas->create(vertices, edgesColor, properties);
    } else {
        ui->canvas->create(vertices, edgesColor, properties, polygon->layer);
        ui->canvas->remove(polygon);
    }
    ui->table->setRowCount(0);
    ui->addPolygon->setEnabled(false);
    ui->Menu->setVisible(false);
    ui->canvas->repaint();
    polygon = nullptr;

}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (ui->canvas->underMouse()){
        polygon = ui->canvas->findPolygon(QCursor::pos());
        if (polygon != nullptr){
            clear();
            ui->addPolygon->setEnabled(true);
            std::vector<QColor> colorEdges = polygon->getColorsEdges();
            std::vector<std::pair<int, int>> coords = polygon->getCoords();
            std::vector<int> properties = polygon->getProperties();
            for (int i = 0; i < colorEdges.size(); i++) {
                int row = ui->table->rowCount();
                ui->table->insertRow(row);
                ui->table->setItem(row, 0, new QTableWidgetItem(QString::number(coords[i].first)));
                ui->table->setItem(row, 1, new QTableWidgetItem(QString::number(coords[i].second)));
                ui->table->setItem(row, 2, new QTableWidgetItem(QString::number(properties[i])));
                ui->table->setItem(row, 3, new QTableWidgetItem());
                ui->table->item(row, 3)->setBackground(colorEdges[i]);
            }
        } else {
            return;
        }
    }
}

// void MainWindow::edit(int row, int column){
//     if (column == 0) {
//         int userCoordX = ui->table->item(row, 0)->text().toInt();
//         int goodCoordX = std::min(userCoordX, 400);
//         QTableWidgetItem* item = ui->table->takeItem(row, 0);
//         item->setText(QString::number(goodCoordX));
//         ui->table->setItem(row, 0, item);
//     } else if (column == 1){
//         int userCoordY = ui->table->item(row, 1)->text().toInt();
//         int goodCoordY = std::min(userCoordY, 500);
//         QTableWidgetItem* item = ui->table->takeItem(row, 1);
//         item->setText(QString::number(goodCoordY));
//         ui->table->setItem(row, 1, item);
//     } else if (column == 2) {
//         int userProp = ui->table->item(row, 2)->text().toInt();
//         QTableWidgetItem* item = ui->table->takeItem(row, 2);
//         item->setText(QString::number(userProp));
//         ui->table->setItem(row, 2, item);
//     } else {
//         QColorDialog colorDialog;
//         QColor newColor = colorDialog.getColor();
//         ui->table->item(row, 3)->setBackground(newColor);
//     }
// }

void MainWindow::on_table_cellClicked(int row, int column){
    if (column == 3) {
        QColorDialog colorDialog;
        QColor newColor = colorDialog.getColor();
        ui->table->item(row, 3)->setBackground(newColor);
    } else {
        return;
    }
}
