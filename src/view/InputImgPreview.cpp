//
// Created by nono on 13/03/23.
//

#include "InputImgPreview.h"
#include <QResizeEvent>

InputImgPreview::InputImgPreview(QWidget *parent): QLabel(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    setStyleSheet("background-color: red");
    setAlignment(Qt::AlignCenter);
//    setScaledContents(true);
}

void InputImgPreview::setPixmap(QString &fn) {
    this->fileName = fn;
    m_pixmap = QPixmap(this->fileName);
    QLabel::setPixmap(m_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void InputImgPreview::resizeEvent(QResizeEvent *event) {
    if (!m_pixmap.isNull()) {
        m_pixmap = QPixmap(this->fileName);
        QLabel::setPixmap(m_pixmap.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    QLabel::resizeEvent(event);
}
