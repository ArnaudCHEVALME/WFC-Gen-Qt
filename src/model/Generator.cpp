#include "Generator.h"

Generator::Generator(std::vector<QImage> *imgsSrc, int width, int height) {
    this->imgsSrc = imgsSrc;
    this->output_width = width;
    this->output_height = height;
}

Generator::Generator(std::vector<QImage> *imgsSrc, int size) {
    this->imgsSrc = imgsSrc;
    this->output_width = size;
    this->output_height = size;
}

Generator::Generator(std::vector<QImage> *imgsSrc) {
    this->imgsSrc = imgsSrc;
    this->output_width = 10;
    this->output_height = 10;
}

// creates Rules for each image based on pixel colors in corresponding directions
void Generator::createRules() {
    createRotations();

    for (const QImage &img0: *imgsSrc) {
        Rule *rule = new Rule(&img0);
        for (const QImage &img1: *imgsSrc) {
            if (img0 == img1)
                continue;

            // check if the images are share the same colors in the corresponding directions
            for (int i = 0; i < 4; i++) {
                auto dir = static_cast<Direction>(i);
                int x0Middle, y0Middle, x1Middle, y1Middle;
                int x0Corner0, y0Corner0, x1Corner0, y1Corner0;
                int x0Corner1, y0Corner1, x1Corner1, y1Corner1;

                switch (dir) {
                    case UP:
                        x0Middle = img0.width() / 2;
                        y0Middle = 0;
                        x1Middle = img1.width() / 2;
                        y1Middle = img1.height() - 1;

                        x0Corner0 = 0;
                        y0Corner0 = 0;
                        x1Corner0 = 0;
                        y1Corner0 = img1.height() - 1;

                        x0Corner1 = img0.width() - 1;
                        y0Corner1 = 0;
                        x1Corner1 = img1.width() - 1;
                        y1Corner1 = img1.height() - 1;

                        break;
                    case DOWN:
                        x0Middle = img0.width() / 2;
                        y0Middle = img0.height() - 1;
                        x1Middle = img1.width() / 2;
                        y1Middle = 0;

                        x0Corner0 = 0;
                        y0Corner0 = img0.height() - 1;
                        x1Corner0 = 0;
                        y1Corner0 = 0;

                        x0Corner1 = img0.width() - 1;
                        y0Corner1 = img0.height() - 1;
                        x1Corner1 = img1.width() - 1;
                        y1Corner1 = 0;
                        break;
                    case LEFT:
                        x0Middle = 0;
                        y0Middle = img0.height() / 2;
                        x1Middle = img1.width() - 1;
                        y1Middle = img1.height() / 2;

                        x0Corner0 = 0;
                        y0Corner0 = 0;
                        x1Corner0 = img1.width() - 1;
                        y1Corner0 = 0;

                        x0Corner1 = 0;
                        y0Corner1 = img0.height() - 1;
                        x1Corner1 = img1.width() - 1;
                        y1Corner1 = img1.height() - 1;
                        break;
                    case RIGHT:
                        x0Middle = img0.width() - 1;
                        y0Middle = img0.height() / 2;
                        x1Middle = 0;
                        y1Middle = img1.height() / 2;

                        x0Corner0 = img0.width() - 1;
                        y0Corner0 = 0;
                        x1Corner0 = 0;
                        y1Corner0 = 0;

                        x0Corner1 = img0.width() - 1;
                        y0Corner1 = img0.height() - 1;
                        x1Corner1 = 0;
                        y1Corner1 = img1.height() - 1;
                        break;
                }


                // check if the images share the same colors in the corresponding directions
                if (img0.pixelColor(x0Middle, y0Middle) == img1.pixelColor(x1Middle, y1Middle) &&
                    img0.pixelColor(x0Corner0, y0Corner0) == img1.pixelColor(x1Corner0, y1Corner0) &&
                    img0.pixelColor(x0Corner1, y0Corner1) == img1.pixelColor(x1Corner1, y1Corner1)) {

                    rule->addRule(dir, const_cast<QImage *>(&img1));
                }
            }
        }
        // add the rule to the map of rules
        rules.insert(std::pair<const QImage *, Rule *>(const_cast<QImage *>(&img0), rule));
    }
}


void Generator::createRotations() {
    for (const QImage &img: *imgsSrc) {
        for (int i = 0; i < 3; i++) {
            auto imgR = img.transformed(QTransform().rotate(90));
            // check if the rotation already exists
            bool exists = false;
            for (const QImage &img2: *imgsSrc) {
                if (img2 == imgR) {
                    exists = true;
                    break;
                }
            }
            if (!exists)
                imgsSrc->push_back(imgR);
        }
    }
}

