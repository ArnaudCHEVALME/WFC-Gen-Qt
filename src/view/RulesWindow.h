//
// Created by nono on 02/04/23.
//

#ifndef WFC_IMAGE_GENERATOR_RULESWINDOW_H
#define WFC_IMAGE_GENERATOR_RULESWINDOW_H


#include <QMainWindow>
#include "../model/Rule.h"

class RulesWindow : public QMainWindow {
public:
    RulesWindow(QWidget *parent = nullptr, std::unordered_map<const QImage *, Rule *> *rules = nullptr);
    RulesWindow(std::unordered_map<const QImage *, Rule *> *rules = nullptr);
};


#endif //WFC_IMAGE_GENERATOR_RULESWINDOW_H
