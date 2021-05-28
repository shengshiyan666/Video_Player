#include <iostream>
#include "the_player.h"
#include <PlayerSlider.h>
#include "playercontrols.h"
// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i){
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}


void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    //printf("receive signal\n");
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            // play some other video
            // setMedia( *infos -> at (rand() % infos->size() ).url);
            //printf("AA\n");

            play(); // starting playing again
    }
}


void ThePlayer::slider_clicked(){

   this->setPosition(cur_slider->value()*this->duration()/100);
}

void ThePlayer::slider_clicked2(){
    this->setVolume(vol_slider->value());
    //printf("%d\n",vol_slider->value());
}

void ThePlayer::progress_moved(){
    TM->stop();
    this->setPosition(cur_slider->value()*this->duration()/100);
    //printf("dKMKMKM");
}


void ThePlayer::progress_released(){
    TM->start();
}

void ThePlayer::getslider(PlayerSlider* slid1,PlayerSlider* slid2){
    cur_slider=slid1;
    vol_slider=slid2;
};

void ThePlayer::gertimer(QTimer* TIM){
    TM=TIM;
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
}

void ThePlayer::reset(){
    this->setPosition(0);
    this->pause();
}

void ThePlayer::next(){
    for(int i = 0;i < (int)this->infos->size();i++){
        if(this->media() == *this->infos->at(i).url){
            if(i < (int)this->infos->size()-1){
                this->setMedia(*this->infos->at(i+1).url);
                break;
            }
            else if(i == (int)this->infos->size()-1){
                this->setMedia(*this->infos->at(0).url);
                break;
            }
        }

    }
}

void ThePlayer::before(){
    for(int i = 0;i < (int)this->infos->size();i++){
       if(this->media() == *this->infos->at(i).url){
            if(i > 0){
                printf("%d",i);
                this->setMedia(*this->infos->at(i-1).url);
                printf("%d",i-1);
                break;
            }
            else if(i == 0){
                printf("%d",i);
                this->setMedia(*this->infos->at((int)this->infos->size()-1).url);
                printf("%d",(int)this->infos->size()-1);
                break;
            }
        }
    }
}

void ThePlayer::open()
{
    QWidget* window = new QWidget;
    QFileDialog fileDialog(window);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    QStringList supportedMimeTypes = this->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty()) {
        supportedMimeTypes.append("audio/x-m3u"); // MP3 playlists
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    }
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted){

        this->setMedia(fileDialog.selectedUrls()[0]);
        write(this->media().canonicalUrl().toString(QUrl::FullyDecoded).toStdString());
    }
}
void ThePlayer::history(){
    write(this->media().canonicalUrl().toString(QUrl::FullyDecoded).toStdString());
}

void ThePlayer::write(const std::string str){
    std::ofstream	OsWrite("D://history.txt",std::ofstream::app);
    OsWrite<<str;
    OsWrite<<std::endl;
    OsWrite.close();

}
