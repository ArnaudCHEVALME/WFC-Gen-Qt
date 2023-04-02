#include <QApplication>
#include <QFileDialog>
#include "src/view/MainWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget window;
    window.setWindowTitle("Pattern Generator");
    window.show();
    return QApplication::exec();
}
