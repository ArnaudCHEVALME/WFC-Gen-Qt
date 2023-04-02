#include "Generator.h"
#include "Grid.h"
#include "../view/RulesWindow.h"

#include <iostream>
#include <stack>
#include <set>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>


Generator::Generator(std::vector<const QImage *> *imgsSrc, int width, int height) {
    this->imgsSrc = imgsSrc;
    this->output_width = width;
    this->output_height = height;
    rules = new std::unordered_map<const QImage *, Rule *>();
}

Generator::Generator(std::vector<const QImage *> *imgsSrc, int size) {
    this->imgsSrc = imgsSrc;
    this->output_width = size;
    this->output_height = size;
    rules = new std::unordered_map<const QImage *, Rule *>();
}

Generator::Generator(std::vector<const QImage *> *imgsSrc) {
    this->imgsSrc = imgsSrc;
    this->output_width = 10;
    this->output_height = 10;
    rules = new std::unordered_map<const QImage *, Rule *>();
}

// creates Rules for each image based on pixel colors in corresponding directions
void Generator::createRulesByColor() {
    for (int i = 0; i < imgsSrc->size(); i++) {
        auto img0 = imgsSrc->at(i);

        Rule *rule = new Rule(img0);
        for (int j = 0; j < imgsSrc->size(); j++) {
            auto img1 = imgsSrc->at(j);

            // check if the images are share the same colors in the corresponding directions
            for (int a = 0; a < 4; a++) {
                auto dir = static_cast<Direction>(a);
                int x0Middle, y0Middle, x1Middle, y1Middle;
                int x0Corner0, y0Corner0, x1Corner0, y1Corner0;
                int x0Corner1, y0Corner1, x1Corner1, y1Corner1;

                switch (dir) {
                    case UP:
                        x0Middle = img0->width() / 2;
                        y0Middle = 0;
                        x1Middle = img1->width() / 2;
                        y1Middle = img1->height() - 1;

                        x0Corner0 = 0;
                        y0Corner0 = 0;
                        x1Corner0 = 0;
                        y1Corner0 = img1->height() - 1;

                        x0Corner1 = img0->width() - 1;
                        y0Corner1 = 0;
                        x1Corner1 = img1->width() - 1;
                        y1Corner1 = img1->height() - 1;

                        break;
                    case DOWN:
                        x0Middle = img0->width() / 2;
                        y0Middle = img0->height() - 1;
                        x1Middle = img1->width() / 2;
                        y1Middle = 0;

                        x0Corner0 = 0;
                        y0Corner0 = img0->height() - 1;
                        x1Corner0 = 0;
                        y1Corner0 = 0;

                        x0Corner1 = img0->width() - 1;
                        y0Corner1 = img0->height() - 1;
                        x1Corner1 = img1->width() - 1;
                        y1Corner1 = 0;
                        break;
                    case LEFT:
                        x0Middle = 0;
                        y0Middle = img0->height() / 2;
                        x1Middle = img1->width() - 1;
                        y1Middle = img1->height() / 2;

                        x0Corner0 = 0;
                        y0Corner0 = 0;
                        x1Corner0 = img1->width() - 1;
                        y1Corner0 = 0;

                        x0Corner1 = 0;
                        y0Corner1 = img0->height() - 1;
                        x1Corner1 = img1->width() - 1;
                        y1Corner1 = img1->height() - 1;
                        break;
                    case RIGHT:
                        x0Middle = img0->width() - 1;
                        y0Middle = img0->height() / 2;
                        x1Middle = 0;
                        y1Middle = img1->height() / 2;

                        x0Corner0 = img0->width() - 1;
                        y0Corner0 = 0;
                        x1Corner0 = 0;
                        y1Corner0 = 0;

                        x0Corner1 = img0->width() - 1;
                        y0Corner1 = img0->height() - 1;
                        x1Corner1 = 0;
                        y1Corner1 = img1->height() - 1;
                        break;
                }

                // prints the coordinates variable









                // check if the images share the same colors in the corresponding directions
                if (img0->pixelColor(x0Middle, y0Middle) == img1->pixelColor(x1Middle, y1Middle) &&
                    img0->pixelColor(x0Corner0, y0Corner0) == img1->pixelColor(x1Corner0, y1Corner0) &&
                    img0->pixelColor(x0Corner1, y0Corner1) == img1->pixelColor(x1Corner1, y1Corner1)) {

                    rule->addRule(dir, img1);

                }
            }
        }
        // add the rule to the map of rules
        rules->insert(std::pair<const QImage *, Rule *>(img0, rule));

    }
}

void Generator::createRotations() {

    auto *rotations = new std::vector<const QImage *>();
    for (const auto &img: *imgsSrc) {

        for (int i = 1; i < 4; i++) {
            // rotate the image
            auto imgR = new QImage(img->transformed(QTransform().rotate(90 * i)));
            if (imgR->isNull()) {

            }

            // check if the rotation already exists in imgSrc
            bool rotationExists = false;
            for (const auto &existingImg: *imgsSrc) {
                if (*imgR == *existingImg) {
                    rotationExists = true;
                    break;
                }
            }
            // check if the rotation already exists in rotations
            for (const auto &existingImg: *rotations) {
                if (*imgR == *existingImg) {
                    rotationExists = true;
                    break;
                }
            }

            if (!rotationExists) {
                rotations->push_back(imgR);
            } else {
                delete imgR;
            }
        }
    }
    imgsSrc->insert(imgsSrc->end(), rotations->begin(), rotations->end());

    delete rotations;

}

void Generator::generate() {
    // create a grid of possible images for each pixel
    grid = Grid(output_height, output_width, imgsSrc);

    while (!grid.isFullyCollapsed()) {
        // pick image with the lowest entropy
        auto tileCoords = grid.getMinEntropyPos();

        // check if coords are valid
        if (tileCoords.first == -1 || tileCoords.second == -1)
            tileCoords = grid.collapseRandomTile();
        else
            grid.collapse(tileCoords);


        if (grid.getPossibleImages(tileCoords).size() == 0) {

            exit(1);
        }

        // propagate the changes
        std::set<std::pair<int, int>> visited;
        propagate(tileCoords, visited);
    }

}

void Generator::propagate(std::pair<int, int> tileCoords, std::set<std::pair<int, int>> &visited) {

    visited.insert(tileCoords);
    for (auto collapsedImg: grid.getPossibleImages(tileCoords)) {
        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                if ((row == 0 && col == 0) || row == col || row == -col)
                    continue;
                if (tileCoords.first + row < 0 || tileCoords.first + row >= grid.getHeight())
                    continue;
                if (tileCoords.second + col < 0 || tileCoords.second + col >= grid.getWidth())
                    continue;

                Direction dir = fromCoords(row, col);
                auto validNeighbours = rules->at(collapsedImg)->getImgInDir(dir);
                std::pair<int, int> neighbourCoords = std::make_pair(tileCoords.first + row,
                                                                     tileCoords.second + col);

                if (visited.find(neighbourCoords) ==
                    visited.end()) {  // check if neighbour has not been visited before



                    bool changed = grid.imgToKeep(neighbourCoords, validNeighbours);
                    if (changed)
                        propagate(neighbourCoords, visited);
                }
            }
        }
    }
}


Direction Generator::getOpposite(Direction dir) {
    switch (dir) {
        case UP:
            return DOWN;
        case RIGHT:
            return LEFT;
        case DOWN:
            return UP;
        default:
            return RIGHT;
    }
}

Direction Generator::fromCoords(int row, int col) {
    if (row == 0 && col == -1) {
        return LEFT;
    } else if (row == 1 && col == 0) {
        return DOWN;
    } else if (row == 0 && col == 1) {
        return RIGHT;
    } else {
        return UP;
    }
}

std::unordered_map<const QImage *, Rule *>* Generator::getRules() {
    return rules;
}

void Generator::generateImg() {
    createRotations();
    createRulesByColor();
    generate();
}

QImage Generator::getOutputImg() {
    return grid.getOutputImage();
}
