//
// Created by nono on 02/04/23.
//

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include "RulesWindow.h"

RulesWindow::RulesWindow(QWidget *parent, std::unordered_map<const QImage *, Rule *> *rules) {
    setWindowTitle("Rules");
    auto *scrollArea = new QScrollArea(this);
    auto *rulesScrollWidget = new QWidget(scrollArea);
    scrollArea->setWidget(rulesScrollWidget);

    auto *rulesScrollLayout = new QVBoxLayout(rulesScrollWidget);
    rulesScrollLayout->setAlignment(Qt::AlignTop);

    for (const auto &rulePair: *rules) {
        auto *ruleWidget = new QWidget(rulesScrollWidget);
        auto *ruleLayout = new QVBoxLayout(ruleWidget);
        ruleLayout->setAlignment(Qt::AlignTop);
        ruleWidget->setLayout(ruleLayout);

        auto *keyImg = new QLabel(ruleWidget);
        keyImg->setPixmap(QPixmap::fromImage(*rulePair.first));
        ruleLayout->addWidget(keyImg);

        // for each direction, add the corresponding images
        for (int i = 0; i < 4; i++) {
            auto dir = static_cast<Direction>(i);
            // create new line for each direction
            auto *dirWidget = new QWidget(ruleWidget);
            auto *dirLayout = new QHBoxLayout(dirWidget);
            dirLayout->setAlignment(Qt::AlignLeft);

            // add the direction text to the line (UP, RIGHT, DOWN, LEFT)
            QLabel * dirLabel;
            switch (dir) {
                case UP:
                    dirLabel =  new QLabel("UP : ", dirWidget);
                    break;
                case RIGHT:
                    dirLabel =  new QLabel("RIGHT : ", dirWidget);
                    break;
                case DOWN:
                    dirLabel =  new QLabel("DOWN : ", dirWidget);
                    break;
                default:
                    dirLabel =  new QLabel("LEFT : ", dirWidget);
                    break;
            }
            // set fixed width for the label
            dirLabel->setFixedWidth(50);
            dirLayout->addWidget(dirLabel);

            for (const auto &img: *rulePair.second->getImgInDir(dir)) {
                auto *imgWidget = new QLabel(ruleWidget);
                imgWidget->setPixmap(QPixmap::fromImage(*img));
                dirLayout->addWidget(imgWidget);
            }
            ruleLayout->addWidget(dirWidget);
        }
        rulesScrollLayout->addWidget(ruleWidget);
    }

    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);
    show();
}

RulesWindow::RulesWindow(std::unordered_map<const QImage *, Rule *> *rules) {
    RulesWindow(nullptr, rules);
}
