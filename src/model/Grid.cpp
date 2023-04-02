//
// Created by nono on 02/04/23.
//

#include <QPainter>
#include "Grid.h"


int random_int(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int random_int(int max) {
    return random_int(0, max);
}

Grid::Grid(int height, int width, const std::vector<const QImage *> *images) :
        m_data(height, std::vector<std::vector<QImage *>>(width)),
        m_height(height),
        m_width(width) {


    for (int i = 0; i < m_height; i++) {
        m_data[i] = std::vector<std::vector<QImage *>>(m_width);
        for (int j = 0; j < m_width; j++) {
            m_data[i][j] = std::vector<QImage *>();

            // add all images as possible images
            for (const QImage *img: *images) {
                m_data[i][j].push_back(const_cast<QImage *>(img));
            }
        }
    }
}

const std::vector<QImage *> &Grid::getPossibleImages(int row, int col) const {
    return m_data[row][col];
}

std::pair<int, int> Grid::getMinEntropyPos() const {
    // loop through the grid and find the position with the lowest entropy
    int minEntropy = INT_MAX;
    std::pair<int, int> minEntropyPos = std::make_pair(-1, -1);
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            if (m_data[i][j].size() < minEntropy && m_data[i][j].size() > 1) {
                minEntropy = m_data[i][j].size();
                minEntropyPos = std::make_pair(i, j);
            }
        }
    }
    return minEntropyPos;
}

std::pair<int, int> Grid::collapseRandomTile() {
    // choose random coordinates
    int row = random_int(m_height);
    int col = random_int(m_width);

    collapse(row, col);

    return std::make_pair(row, col);
}

void Grid::collapse(int row, int col) {
    // remove every image but one
    while (m_data[row][col].size() > 1) {
        int index = random_int(m_data[row][col].size());
        removeImage(row, col, m_data[row][col][index]);
    }
}

void Grid::collapse(std::pair<int, int> coords) {
    collapse(coords.first, coords.second);
}

bool Grid::imgToKeep(int row, int col, std::vector<const QImage *> *toKeep) {
    std::vector<QImage *> &possibleImages = m_data[row][col];

    // log how many images the vectors have in common
    int commonImages = 0;
    for (const QImage *img: *toKeep) {
        if (std::find(possibleImages.begin(), possibleImages.end(), img) != possibleImages.end()) {
            commonImages++;
        }
    }

    const int originalSize = possibleImages.size();

    // Remove any images from possibleImages that are not in toKeep
    possibleImages.erase(std::remove_if(possibleImages.begin(), possibleImages.end(),
                                        [toKeep](QImage *img) {
                                            return std::find(toKeep->begin(), toKeep->end(), img) == toKeep->end();
                                        }), possibleImages.end());

    // Check if anything was removed from the vector
    if (possibleImages.size() == 0) {

//        exit(1);
    }

    return (possibleImages.size() < originalSize);
}


bool Grid::imgToKeep(std::pair<int, int> coords, std::vector<const QImage *> *toKeep) {
    return imgToKeep(coords.first, coords.second, toKeep);
}

const std::vector<QImage *> &Grid::getPossibleImages(std::pair<int, int> coords) const {
    return getPossibleImages(coords.first, coords.second);
}

void Grid::removeImage(int row, int col, const QImage *img) {
    m_data[row][col].erase(std::remove(m_data[row][col].begin(), m_data[row][col].end(), img), m_data[row][col].end());
}

Grid::Grid() {
    m_height = -1;
    m_width = -1;
}

bool Grid::isFullyCollapsed() {
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            if (m_data[i][j].size() > 1)
                return false;
        }
    }
    return true;
}

QImage Grid::getOutputImage() {
    QImage output(m_width * m_data[0][0][0]->width(), m_height * m_data[0][0][0]->height(), QImage::Format_RGB32);

    QPainter painter(&output);

    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            painter.drawImage(j * m_data[i][j][0]->width(), i * m_data[i][j][0]->height(), *m_data[i][j][0]);
        }
    }

    return output;
}

int Grid::getHeight() const {
    return m_height;
}

int Grid::getWidth() const {
    return m_width;
}


