//
// Created by nono on 02/04/23.
//

#ifndef WFC_IMAGE_GENERATOR_GRID_H
#define WFC_IMAGE_GENERATOR_GRID_H


#include <vector>
#include <QImage>
#include <random>

class Grid {

private:
    std::vector<std::vector<std::vector<QImage *>>> m_data;
    int m_height;
    int m_width;


public:
    Grid(int height, int width, const std::vector<const QImage *> *images);

    Grid();

    std::pair<int, int> collapseRandomTile();

    void collapse(int row, int col);

    void collapse(std::pair<int, int> coords);

    bool imgToKeep(int row, int col, std::vector<const QImage *> *toKeep);

    bool imgToKeep(std::pair<int, int> coords, std::vector<const QImage *> *toKeep);

    [[nodiscard]] const std::vector<QImage *> &getPossibleImages(int row, int col) const;

    [[nodiscard]] const std::vector<QImage *> &getPossibleImages(std::pair<int, int> coords) const;

    void removeImage(int row, int col, const QImage *img);

    [[nodiscard]] std::pair<int, int> getMinEntropyPos() const;

    bool isFullyCollapsed();

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getWidth() const;

    QImage getOutputImage();

};

#endif //WFC_IMAGE_GENERATOR_GRID_H
