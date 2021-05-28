#include "videowindow.h"


videowindow::videowindow(){

}

void videowindow::showFull(){
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();
}

void videowindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
       this->setWindowFlags (Qt::SubWindow);
       this->showMaximized();  //?????
    }
}
