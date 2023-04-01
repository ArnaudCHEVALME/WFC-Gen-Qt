//
// Created by nono on 13/03/23.
//

#ifndef WFC_IMAGE_GENERATOR_INPUTIMGPREVIEW_H
#define WFC_IMAGE_GENERATOR_INPUTIMGPREVIEW_H


#include <QString>
#include <QPixmap>
#include <QWidget>
#include <QLabel>

class InputImgPreview : public QLabel {
public:
    explicit InputImgPreview(QWidget *parent = nullptr);

    void setPixmap(QString &fn);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap m_pixmap;
    // keep the file name to create a new pixmap when resizing and avoid blurry images
    QString fileName;
};


#endif //WFC_IMAGE_GENERATOR_INPUTIMGPREVIEW_H
