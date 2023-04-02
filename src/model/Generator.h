//
// Created by nono on 13/03/23.
//

#ifndef WFC_IMAGE_GENERATOR_GENERATOR_H
#define WFC_IMAGE_GENERATOR_GENERATOR_H

#include "Rule.h"
#include "Grid.h"
#include <QImage>
#include <vector>
#include <set>

class Generator {

private:
    int output_width;
    int output_height;

    Grid grid;
    std::vector<const QImage *> *imgsSrc;

    std::unordered_map<const QImage *, Rule *> *rules;

    Direction getOpposite(Direction dir);

    Direction fromCoords(int row, int col);
private slots:

    void generateImg();

public:
    Generator(std::vector<const QImage *> *imgsSrc, int width, int height);

    Generator(std::vector<const QImage *> *imgsSrc, int size);

    Generator(std::vector<const QImage *> *imgsSrc);

    void createRotations();

    std::unordered_map<const QImage *, Rule *> getRules();

    void createRulesByColor();

    void createRulesCustom();

    void generate();

    void propagate(std::pair<int, int> tileCoords, std::set<std::pair<int, int>>& visited);

    QImage getOutputImg();

};


#endif //WFC_IMAGE_GENERATOR_GENERATOR_H
