//
// Created by nono on 13/03/23.
//

#ifndef WFC_IMAGE_GENERATOR_GENERATOR_H
#define WFC_IMAGE_GENERATOR_GENERATOR_H

#include "Rule/Rule.h"

class Generator {

private:
    int output_width;
    int output_height;

    std::vector<QImage> *imgsSrc;

    std::unordered_map<const QImage *, Rule *> rules;

public:
    Generator(std::vector<QImage> *imgsSrc, int width, int height);

    Generator(std::vector<QImage> *imgsSrc, int size);

    Generator(std::vector<QImage> *imgsSrc);

    void createRotations();

    void createRules();

};


#endif //WFC_IMAGE_GENERATOR_GENERATOR_H
