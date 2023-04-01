//
// Created by nono on 13/03/23.
//

#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <iostream>
#include <QMessageBox>
#include <QScrollArea>
#include "PatternWidget.h"

PatternWidget::PatternWidget(QWidget *parent) : QWidget(parent) {

//    setStyleSheet("background-color: green");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMaximumWidth(300);

    auto *layout = new QVBoxLayout(this);
    animationCheckBox = new QCheckBox("Show animation", this);
    openBtn = new QPushButton("Import file", this);
    nInput = new QSpinBox(this);
    nInput->setMinimum(2);
    nInput->setMaximum(5);
    nInput->setMaximumWidth(40);

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

    auto *horizontalLayout = new QHBoxLayout();

    horizontalLayout->addWidget(new QLabel("Taille des patterns"));
    horizontalLayout->addWidget(nInput);

    layout->addWidget(openBtn);
    layout->addLayout(horizontalLayout);
    layout->addWidget(colorRuleRadioBtn);
    layout->addWidget(customRuleRadioBtn);
    layout->addWidget(animationCheckBox);
    layout->addWidget(inputPreviewScrollArea);
    layout->addWidget(generateBtn);

    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);

    // Connect the button's clicked() signal to a slot function
    connect(openBtn, &QPushButton::clicked, this, &PatternWidget::openImages);
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
    auto img0 = QImage(fileNames[0]);
    srcImgs.push_back(img0);

    int w = srcImgs[0].width();
    int h = srcImgs[0].height();

    for (int i = 1; i < fileNames.size(); i++) {
        auto img = QImage(fileNames[i]);
        if (img.height() != h || img.width() != w) {
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
        inputImgPreviewLayout->addWidget(imgPreview, i / 3, i % 3);
    }

}
