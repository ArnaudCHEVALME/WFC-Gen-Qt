#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <iostream>
#include <QLayout>
#include "src/view/MainWidget.h"
#include "src/view/PatternWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget window;

    window.show();
    return QApplication::exec();
}
