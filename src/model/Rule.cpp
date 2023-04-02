//
// Created by nono on 02/04/23.
//

#include "Rule.h"
#include <QDebug>

Rule::Rule( const QImage *img) {
    this->image = img;
}

void Rule::addRule(Direction dir, const QImage *img) {
    if (rules.count(dir) == 0) {
        rules[dir] = new std::vector<const QImage *>();
    }
    if (std::find(rules[dir]->begin(), rules[dir]->end(), img) == rules[dir]->end()) {
        rules[dir]->push_back(img);
    }
}


void Rule::removeRule(Direction dir, const QImage *img) {
    if (rules.count(dir) == 0) {
        rules[dir] = new std::vector<const QImage *>();
    }
    if (std::find(rules.at(dir)->begin(), rules.at(dir)->end(), img) != rules.at(dir)->end()) {
        rules.at(dir)->erase(std::remove(rules.at(dir)->begin(), rules.at(dir)->end(), img), rules.at(dir)->end());
    }
}

std::vector<const QImage *> *Rule::getImgInDir(Direction dir) {
    return rules.at(dir);
}

bool Rule::isPossibleInDir(Direction dir, const QImage *img) {
    return std::find(rules.at(dir)->begin(), rules.at(dir)->end(), img) != rules.at(dir)->end();
}

