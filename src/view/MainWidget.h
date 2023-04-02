//
// Created by nono on 13/03/23.
//

#ifndef WFC_IMAGE_GENERATOR_MAINWIDGET_H
#define WFC_IMAGE_GENERATOR_MAINWIDGET_H


#include <QWidget>
#include <QGraphicsView>
#include "PatternWidget.h"

class MainWidget : public QWidget {
Q_OBJECT

private:
    PatternWidget *patternWidget;
    QGraphicsView *viewWidget;

    void displayResults(const QImage& result);

public :
    explicit MainWidget(QWidget *parent = nullptr);
};


#endif //WFC_IMAGE_GENERATOR_MAINWIDGET_H
