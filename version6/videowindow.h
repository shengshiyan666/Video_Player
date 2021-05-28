#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QImageReader>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QLabel>
#include <QScrollArea>
#include <QSlider>
#include <QMouseEvent>

class videowindow : public QVideoWidget
{
     Q_OBJECT
public:
    videowindow();
public slots:
    void showFull();
    void keyPressEvent(QKeyEvent *event);
};

#endif // VIDEOWINDOW_H
