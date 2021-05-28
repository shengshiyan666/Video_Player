/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for no reason
 *
 * 2811 cw2 November 2019 by twak
 */

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
#include <QComboBox>
#include <QTextEdit>
#include <QtCore/QDirIterator>
#include <QLabel>
#include <QStyle>
#include <QScrollArea>
#include <QSlider>
#include "the_player.h"
#include "the_button.h"
#include "PlayerSlider.h"
#include "buttom_label.h"
#include "videowindow.h"
#include "playercontrols.h"

using namespace std;

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>(); // container list for all the information
    //int a =0;

    QDirIterator it(QString::fromStdString(loc), QDir::Files);

    while (it.hasNext()) { // for all files
		QString f = it.next();

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4"))  { // mac/linux
#endif

        if (!f.contains(".png")) { // if it isn't an image
            QString thumb = f.left( f .length() - 3) +"png";
            if (QFile(thumb).exists()) { // but a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read();
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite));
                        QUrl* url = new QUrl(QUrl::fromLocalFile(f)); //URL convert the file location to a generic url
						out.push_back(TheButtonInfo(url, ico)); // add to the output list
						//++;

					}
					else
						qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb ;
            }
            else
				qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb;
        }
            }
        //printf("%d",a);

    }

    return out;
}
void setButton1(ThePlayer *player,QPushButton*b_pase,QPushButton*b_start,QPushButton*reset,QPushButton*darkmethod,PlayerControls *control);
void setButton2(ThePlayer *player,QPushButton*nextV,QPushButton*beforeV);
void setSlider(ThePlayer *player,PlayerSlider *slider);
void setButton3(TheButton *button,ThePlayer *player,buttomlabel *lab1);
void setClassify(QPushButton *classify,QPushButton *classify1,QWidget *video1);
void setLayout(QVBoxLayout *layout,QPushButton *classify,QPushButton *classify1,QWidget *video1);
int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR;
    // collect all the videos in the folder
    vector<TheButtonInfo> videos = getInfoIn("..\\videos");
    if (videos.size() == 0) {
        qDebug() << "no videos found";exit(-1);
    }
    PlayerControls *control = new PlayerControls();
    // the widget that will show the video
    videowindow *videoWidget = new videowindow;
	//videoWidget -> setBaseSize(600, 300);
    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;player->setVideoOutput(videoWidget);
    //float persentage;
    //persentage = player->position()/player->duration();
    QObject::connect(control, &PlayerControls::changeRate, player, &QMediaPlayer::setPlaybackRate);
    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    std::vector<TheButton*> buttons;

    // the buttons are arranged horizontally
    QVBoxLayout *layout = new QVBoxLayout();buttonWidget->setLayout(layout);
    QVBoxLayout *layout1 = new QVBoxLayout();QVBoxLayout *layout2 = new QVBoxLayout();
    QVBoxLayout *layout3 = new QVBoxLayout();QVBoxLayout *layout4 = new QVBoxLayout();
    QVBoxLayout *layout5 = new QVBoxLayout();buttomlabel *lab1 = new buttomlabel();
    QWidget *video1 = new QWidget();QWidget *video2 = new QWidget();
    QWidget *video3 = new QWidget();QWidget *video4 = new QWidget();
    QWidget *video5 = new QWidget();

    video1->setLayout(layout1);video2->setLayout(layout2);
    video3->setLayout(layout3);video4->setLayout(layout4);
    video5->setLayout(layout5);

    setLayout(layout,control->classify,control->classify1,video1);setLayout(layout,control->classify2,control->classify3,video2);

    setLayout(layout,control->classify4,control->classify5,video3);setLayout(layout,control->classify8,control->classify9,video5);
    setLayout(layout,control->classify6,control->classify7,video4);
   // TheButton::connect(this,SIGNAL(released()),lab1,SLOT(setText(QString*) ) );
    // create the four buttons
    for ( int i = 0; i < 6; i++ ) {
        TheButton *button = new TheButton(buttonWidget);setButton3(button,player,lab1);
        buttons.push_back(button);
        if(i == 0)layout1->addWidget(button);
        if(i == 1)layout2->addWidget(button);
        if(i == 2)layout3->addWidget(button);
        if(i == 3 or i == 4)layout4->addWidget(button);
        if(i == 5)layout5->addWidget(button);button->init(&videos.at(i));
    }
    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);
    player->write(player->infos->at(0).url->toString(QUrl::FullyDecoded).toStdString());
    //scrollarea
   // QLabel* lewy = new QLabel();
    QScrollArea* scroll = control->scrollarea;scroll->setMinimumWidth(190);
   // QWidget* area = new QWidget();
    buttonWidget->setGeometry(0, 0,160,1000);

        setClassify(control->classify,control->classify1,video1);
        setClassify(control->classify2,control->classify3,video2);
        setClassify(control->classify4,control->classify5,video3);
        setClassify(control->classify6,control->classify7,video4);
        setClassify(control->classify8,control->classify9,video5);

    scroll->setWidget(buttonWidget);

    control->window;control->window.setWindowTitle("tomeo");QVBoxLayout *top = new QVBoxLayout();
    //window.setLayout(top);
    PlayerSlider *slider = new PlayerSlider();slider->setOrientation(Qt::Horizontal);
    PlayerSlider *slider_volume = new PlayerSlider();slider_volume->setOrientation(Qt::Horizontal);
    //slider_volume->setRange(0,50);
    QTimer *SlideTimer = new QTimer(player);
    SlideTimer->setInterval(1000); SlideTimer->start();slider->getplayer(player);
    player->getslider(slider,slider_volume);player->gertimer(SlideTimer);
    //QTimer::connect(SlideTimer, SIGNAL(timeout()), slider, SLOT(onTimerOut()))；
    QTimer::connect(SlideTimer, SIGNAL(timeout()), slider, SLOT(onTimerOut()));
    setSlider(player,slider);
    //PlayerSlider::connect(slider_volume,SIGNAL(sliderPressed()),player,SLOT(slider_clicked2()));
    PlayerSlider::connect(slider_volume,SIGNAL(sliderMoved(int)),player,SLOT(slider_clicked2()));

    setButton1(player,control->stop,control->start,control->resetvideo,control->dark,control);
    setButton2(player,control->nextvideo,control->beforevideo);
    QLabel* time = new QLabel("TIME");time->setStyleSheet(" color : green;");
    //time->setTextFormat();
    QHBoxLayout* searchlayout = new QHBoxLayout();
    QWidget* search = new QWidget ();
    searchlayout->addWidget(control->edit);
    searchlayout->addWidget(control->search);
    search->setLayout(searchlayout);

    QVBoxLayout *controlbar1 =new QVBoxLayout();QHBoxLayout *controlbar =new QHBoxLayout();
    QHBoxLayout *controlbar2 =new QHBoxLayout();QHBoxLayout *controlbar3 =new QHBoxLayout();
    controlbar3->addWidget(control->resetvideo);controlbar2->addWidget(time);
    controlbar2->addWidget(slider);
    controlbar3->addWidget(control->beforevideo);
    controlbar3->addWidget(control->start);controlbar3->addWidget(control->stop);
    controlbar3->addWidget(control->nextvideo);
    controlbar3->addWidget(control->openvideo);
    controlbar3->addWidget(control->volume);
    controlbar3->addWidget(slider_volume);controlbar3->addWidget(control->m_rateBox);
    controlbar3->addWidget(control->dark);
    controlbar1->addLayout(controlbar2);controlbar1->addLayout(controlbar);
    controlbar1->addLayout(controlbar3);
    QPushButton *openButton = control->openvideo;
    openButton->setText("🖿 Open");
    controlbar2->addWidget(control->fullScreenvideo);
    QPushButton::connect(openButton, SIGNAL(clicked()), player, SLOT(open()));
    //top->addWidget(slider);
    //top->addWidget(scroll);
    //top->setStretchFactor(videoWidget, 3);
    // add the video and the buttons to the top level widget
    top->addWidget(lab1);top->addWidget(videoWidget);top->addLayout(controlbar1);
    //top->setStretchFactor(scroll);
    QHBoxLayout *all = new QHBoxLayout();all->addLayout(top);QVBoxLayout *right = new QVBoxLayout();
    //QPushButton *search = new QPushButton();
    //search->setText("search");
    //right->addWidget(search);
//    right->addWidget(search);
    right->addWidget(scroll);
    all->addLayout(right);all->setStretchFactor(videoWidget, 3);
    //all->addWidget(scroll);
    control->window.setLayout(all);control->window.setMinimumSize(800, 680);control->window.setGeometry(40, 40, 800, 680);
    //videoWidget->setWindowFlags(Qt::Window);
    QPushButton::connect(control->fullScreenvideo,SIGNAL(clicked()),videoWidget,SLOT(showFull()));

    //videoWidget->setWindowFlags(Qt::Window);
    //videoWidget->showFullScreen();
    // showtime!
    control->window.show();return app.exec();
    // wait for the app to terminate
}

void setButton1(ThePlayer *player,QPushButton*b_pase,QPushButton*b_start,QPushButton*reset,QPushButton *darkmethod,PlayerControls *control){
    QPushButton::connect(b_pase,SIGNAL(clicked()),player,SLOT(pause()));
    QPushButton::connect(b_start,SIGNAL(clicked()),player,SLOT(play()));
    QPushButton::connect(reset,SIGNAL(clicked()),player,SLOT(reset()));
    QPushButton::connect(darkmethod,SIGNAL(clicked()),control,SLOT(darkmethod()));
    QPushButton::connect(darkmethod,SIGNAL(clicked()),control,SLOT(change()));
}
void setButton2(ThePlayer *player,QPushButton*nextV,QPushButton*beforeV){
    QPushButton::connect(nextV,SIGNAL(clicked()),player,SLOT(next()));
    QPushButton::connect(beforeV,SIGNAL(clicked()),player,SLOT(before()));
}
void setSlider(ThePlayer *player,PlayerSlider *slider){
    PlayerSlider::connect(slider,SIGNAL(sliderMoved(int)),player,SLOT(progress_moved()));
    PlayerSlider::connect(slider,SIGNAL(sliderReleased()),player,SLOT(progress_released()));
    PlayerSlider::connect(slider,SIGNAL(sliderPressed()),player,SLOT(slider_clicked()));
}
void setButton3(TheButton *button,ThePlayer *player,buttomlabel *lab1){
    button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
    button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (history()));
    button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), lab1, SLOT (setbutText(TheButtonInfo*)));
    button->setMaximumWidth(210);button->setMaximumHeight(140);

}
void setClassify(QPushButton *classify,QPushButton *classify1,QWidget *video1){
    video1->hide();
    classify1->hide();
    QPushButton::connect(classify,SIGNAL(clicked()),video1,SLOT(show()));
    QPushButton::connect(classify,SIGNAL(clicked()),classify1,SLOT(show()));
    QPushButton::connect(classify,SIGNAL(clicked()),classify,SLOT(hide()));

    QPushButton::connect(classify1,SIGNAL(clicked()),video1,SLOT(hide()));
    QPushButton::connect(classify1,SIGNAL(clicked()),classify1,SLOT(hide()));
    QPushButton::connect(classify1,SIGNAL(clicked()),classify,SLOT(show()));
}
void setLayout(QVBoxLayout *layout,QPushButton *classify,QPushButton *classify1,QWidget *video1){
    layout->addWidget(classify);
    layout->addWidget(classify1);
    layout->addWidget(video1);
}


