//
// Created by nono on 02/04/23.
//

#ifndef WFC_IMAGE_GENERATOR_RULESWINDOW_H
#define WFC_IMAGE_GENERATOR_RULESWINDOW_H


#include <QMainWindow>
#include "../model/Rule.h"

class RulesWindow : public QMainWindow {
public:
    void setRules(std::unordered_map<const QImage *, Rule *>* rules);
};


#endif //WFC_IMAGE_GENERATOR_RULESWINDOW_H
