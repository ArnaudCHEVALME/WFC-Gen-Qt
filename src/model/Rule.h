//
// Created by nono on 02/04/23.
//

#ifndef WFC_IMAGE_GENERATOR_RULE_H
#define WFC_IMAGE_GENERATOR_RULE_H

#include <unordered_map>
#include <vector>
#include <QImage>
#include "Utils/Direction.h"

class Rule {
private:
    const QImage *image;
    std::unordered_map<Direction, std::vector<const QImage *> *> rules;
public:

    explicit Rule(const QImage *img);

    void addRule(Direction dir, const QImage *img);

    void removeRule(Direction dir, const QImage *img);

    std::vector<const QImage *> *getImgInDir(Direction dir);

    bool isPossibleInDir(Direction dir, const QImage *img);
};


#endif //WFC_IMAGE_GENERATOR_RULE_H
