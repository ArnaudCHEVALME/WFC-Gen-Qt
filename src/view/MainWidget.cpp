//
// Created by nono on 13/03/23.
//

#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include "MainWidget.h"


MainWidget::MainWidget(QWidget *parent) {
    setWindowTitle("WFC Image generator");
    setWindowIcon(QIcon("../icon.png"));

    setMinimumSize(600,500);

    patternWidget = new PatternWidget(this);
    viewWidget = new QGraphicsView(this);

    auto *scene = new QGraphicsScene(this);
    viewWidget->setScene(scene);

    QPixmap pixmap("../icon.png");
    auto* pixmapItem = new QGraphicsPixmapItem(pixmap.scaled(size(), Qt::KeepAspectRatio));

    pixmapItem->setOpacity(0.1);



    scene->addItem(pixmapItem);


    auto *layout = new QHBoxLayout(this);
    layout->addWidget(patternWidget);
    layout->addWidget(viewWidget);

    setLayout(layout);

    connect(patternWidget, &PatternWidget::imgGenerated, this, &MainWidget::displayResults);
}

void MainWidget::displayResults(const QImage& result) {
    viewWidget->scene()->clear();
    viewWidget->scene()->addPixmap(QPixmap::fromImage(result).scaledToWidth(viewWidget->width()-5));
}
