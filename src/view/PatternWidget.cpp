//
// Created by nono on 13/03/23.
//

#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>
#include <QScrollArea>
#include <QMainWindow>
#include "PatternWidget.h"
#include "../model/Generator.h"

#include "QDebug"

PatternWidget::PatternWidget(QWidget *parent) : QWidget(parent) {

//    setStyleSheet("background-color: green");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMaximumWidth(300);

    auto *layout = new QVBoxLayout(this);
    animationCheckBox = new QCheckBox("Show animation", this);
    animationCheckBox->setDisabled(true);
    openBtn = new QPushButton("Import file", this);
    wInput = new QSpinBox(this);
    wInput->setMinimum(2);
    wInput->setMaximum(100);

    hInput = new QSpinBox(this);
    hInput->setMinimum(2);
    hInput->setMaximum(100);

    wInput->setMaximumWidth(60);
    hInput->setMaximumWidth(60);

    // add a layout to display images selected in a grid inside a scroll area
    auto * inputPreviewScrollArea = new QScrollArea(this);
    auto * widget = new QWidget;
    inputPreviewScrollArea->setWidget(widget);
    inputImgPreviewLayout = new QGridLayout(widget);

    inputPreviewScrollArea->setWidgetResizable(true);
    inputPreviewScrollArea->setLayout(inputImgPreviewLayout);
    inputPreviewScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    generateBtn = new QPushButton("Generate", this);
    colorRuleRadioBtn = new QRadioButton("Règle par couleur", this);
    colorRuleRadioBtn->setChecked(true);
    customRuleRadioBtn = new QRadioButton("Règles personalisées", this);
    customRuleRadioBtn->setDisabled(true);

    auto *wHorizontalLayout = new QHBoxLayout();

    wHorizontalLayout->addWidget(new QLabel("Largeur output"));
    wHorizontalLayout->addWidget(wInput);

    auto * hHorizontalLayout = new QHBoxLayout();

    hHorizontalLayout->addWidget(new QLabel("Hauteur output"));
    hHorizontalLayout->addWidget(hInput);

    layout->addWidget(openBtn);
    layout->addLayout(wHorizontalLayout);
    layout->addLayout(hHorizontalLayout);
    layout->addWidget(colorRuleRadioBtn);
    layout->addWidget(customRuleRadioBtn);
    layout->addWidget(animationCheckBox);
    layout->addWidget(inputPreviewScrollArea);
    layout->addWidget(generateBtn);

    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);

    // Connect the button's clicked() signal to a slot function
    connect(openBtn, &QPushButton::clicked, this, &PatternWidget::openImages);
    connect(generateBtn, &QPushButton::clicked, this, &PatternWidget::generateImg);
}

void PatternWidget::openImages() {
    // Open a file dialog to select an image file. By defaults open the tilesets folder
    auto fileNames = QFileDialog::getOpenFileNames(this, "Select one or more images to open", "../tilesets", "Images (*.png *.jpg *.bmp)");

    //checks if there is at least two files
    if (fileNames.size() < 2) {
        QMessageBox::warning(this, "Erreur", "Vous devez sélectionner au moins deux images !");
        return;
    }
    // loop through all the selected files, add them to the list and check if they all have the same dimensions
    auto img0 = new QImage(fileNames[0]);

    srcImgs.push_back(img0);

    int d = srcImgs[0]->width();

    for (int i = 1; i < fileNames.size(); i++) {
        auto img = new QImage(fileNames[i]);

        if (img->height() != d || img->width() != d) {
            // toutes les images n'ont pas les mêmes dimensions
            QMessageBox::warning(this, "Erreur", "Les images doivent avoir les mêmes dimensions !");
            return;
        }
        srcImgs.push_back(img);
    }

    // display the images in the preview
    for (int i = 0; i < srcImgs.size(); i++) {
        auto *imgPreview = new InputImgPreview(this);
        imgPreview->setPixmap(fileNames[i]);
        inputImgPreviewLayout->addWidget(imgPreview, i / 5, i % 5);
    }
}

void PatternWidget::generateImg() {
    auto generator = Generator(&srcImgs, wInput->value(), hInput->value());

    generator.createRotations();
    generator.createRulesByColor();
    generator.generate();

    auto out = generator.getOutputImg();
    auto w = new QMainWindow();
    auto imgPreview = new QLabel(w);
    imgPreview->setPixmap(QPixmap::fromImage(out));
    imgPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    w->setCentralWidget(imgPreview);
    w->show();
}
