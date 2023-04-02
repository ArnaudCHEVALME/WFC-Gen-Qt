//
// Created by nono on 13/03/23.
//

#ifndef WFC_IMAGE_GENERATOR_PATTERNWIDGET_H
#define WFC_IMAGE_GENERATOR_PATTERNWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include "InputImgPreview.h"

class PatternWidget : public QWidget {
private:
    QPushButton *openBtn;
    std::vector<const QImage *> srcImgs;
    QGridLayout * inputImgPreviewLayout;
    QSpinBox *wInput;
    QSpinBox *hInput;
    QPushButton *generateBtn;
    QCheckBox *animationCheckBox;
    QRadioButton * colorRuleRadioBtn;
    QRadioButton * customRuleRadioBtn;
public:
    explicit PatternWidget(QWidget *parent = nullptr);

private slots:

    void openImages();

    void generateImg();
};


#endif //WFC_IMAGE_GENERATOR_PATTERNWIDGET_H
