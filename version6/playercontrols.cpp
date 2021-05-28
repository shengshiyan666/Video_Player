#include "playercontrols.h"
#include <iostream>
#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <QAudio>
#include <QString>
PlayerControls::PlayerControls(QWidget *parent)
    : QWidget(parent)
{
    flag = 0;

    edit = new QLineEdit(this);
    search = new QPushButton(this);
    start = new QPushButton(this);
    stop = new QPushButton(this);
    dark = new QPushButton(this);
    nextvideo = new QPushButton(this);
    fullScreenvideo = new QPushButton(this);
    resetvideo = new QPushButton(this);
    beforevideo = new QPushButton(this);
    openvideo = new QPushButton(this);
    scrollarea = new QScrollArea(this);
    volume = new QPushButton(this);

    search->setText("Search");
    volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    start->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    stop->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    nextvideo->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    beforevideo->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    resetvideo->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    openvideo->setText("OPEN");

    dark->setText("☽");
    dark->setStyleSheet("font-size:19px");
    dark->setFixedSize(45,30);
    fullScreenvideo->setText("FullScreen");

    m_rateBox = new QComboBox(this);
    m_rateBox->addItem("0.5x", QVariant(0.5));
    m_rateBox->addItem("1.0x", QVariant(1.0));
    m_rateBox->addItem("2.0x", QVariant(2.0));
    m_rateBox->setCurrentIndex(1);

    connect(m_rateBox, QOverload<int>::of(&QComboBox::activated), this, &PlayerControls::updateRate);

    classify = new QPushButton(this);classify->setText("Cycling");
    classify1 = new QPushButton(this);classify1->setText("Cycling");
    classify2 = new QPushButton(this);classify2->setText("Cooking");
    classify3 = new QPushButton(this);classify3->setText("Cooking");
    classify4 = new QPushButton(this);classify4->setText("Camping");
    classify5 = new QPushButton(this);classify5->setText("Camping");
    classify6 = new QPushButton(this);classify6->setText("Others");
    classify7 = new QPushButton(this);classify7->setText("Others");
    classify8 = new QPushButton(this);classify8->setText("Animals");
    classify9 = new QPushButton(this);classify9->setText("Animals");
}


qreal PlayerControls::playbackRate() const
{
    return m_rateBox->itemData(m_rateBox->currentIndex()).toDouble();

}

void PlayerControls::setPlaybackRate(float rate)
{
    for (int i = 0; i < m_rateBox->count(); ++i) {
        if (qFuzzyCompare(rate, float(m_rateBox->itemData(i).toDouble()))) {
            m_rateBox->setCurrentIndex(i);
            return;
        }
    }

    m_rateBox->addItem(QString("%1x").arg(rate), QVariant(rate));
    m_rateBox->setCurrentIndex(m_rateBox->count() - 1);
}

void PlayerControls::updateRate()
{
    emit changeRate(playbackRate());
}

void PlayerControls::darkmethod(){
    flag = flag + 1;
    if(flag%2 == 0){
        window.setStyleSheet("background-color:#f0f0f0");
        start->setStyleSheet("background-color:#e1e1e1");
        edit->setStyleSheet("background-color:#e1e1e1");
        search->setStyleSheet("background-color:#e1e1e1");
        stop->setStyleSheet("background-color:#e1e1e1");
        nextvideo->setStyleSheet("background-color:#e1e1e1");
        beforevideo->setStyleSheet("background-color:#e1e1e1");
        resetvideo->setStyleSheet("background-color:#e1e1e1");
        fullScreenvideo->setStyleSheet("background-color:#e1e1e1;");
        openvideo->setStyleSheet("background-color:#e1e1e1;");
        scrollarea->setStyleSheet("background-color:#e1e1e1");
        m_rateBox->setStyleSheet("background-color:#e1e1e1");
        dark->setStyleSheet("background-color:#e1e1e1;" "font-size:19px");
        classify->setStyleSheet("color:black;" "font-weight:normal;");
        classify1->setStyleSheet("color:black;" "font-weight:normal;");
        classify2->setStyleSheet("color:black;" "font-weight:normal;");
        classify3->setStyleSheet("color:black;" "font-weight:normal;");
        classify4->setStyleSheet("color:black;" "font-weight:normal;");
        classify5->setStyleSheet("color:black;" "font-weight:normal;");
        classify6->setStyleSheet("color:black;" "font-weight:normal;");
        classify7->setStyleSheet("color:black;" "font-weight:normal;");
        classify8->setStyleSheet("color:black;" "font-weight:normal;");
        classify9->setStyleSheet("color:black;" "font-weight:normal;");
    }else{
        window.setStyleSheet("background-color:black");
        start->setStyleSheet("background-color:#b9b5b5");
        edit->setStyleSheet("background-color:#b9b5b5");
        search->setStyleSheet("background-color:#b9b5b5");
        stop->setStyleSheet("background-color:#b9b5b5");
        m_rateBox->setStyleSheet("background-color:#b9b5b5");
        dark->setStyleSheet("background-color:#b9b5b5;" "font-size:19px");
        nextvideo->setStyleSheet("background-color:#b9b5b5");
        beforevideo->setStyleSheet("background-color:#b9b5b5");
        resetvideo->setStyleSheet("background-color:#b9b5b5");
        fullScreenvideo->setStyleSheet("background-color:#b9b5b5");
        openvideo->setStyleSheet("background-color:#b9b5b5");
        scrollarea->setStyleSheet("background-color:black");
        classify->setStyleSheet("color:white;" "font-weight:bold;" "border:2px solid #000000;");
        classify1->setStyleSheet("color:white;" "font-weight:bold;");
        classify2->setStyleSheet("color:white;" "font-weight:bold;");
        classify3->setStyleSheet("color:white;" "font-weight:bold;");
        classify4->setStyleSheet("color:white;" "font-weight:bold;");
        classify5->setStyleSheet("color:white;" "font-weight:bold;");
        classify6->setStyleSheet("color:white;" "font-weight:bold;");
        classify7->setStyleSheet("color:white;" "font-weight:bold;");
        classify8->setStyleSheet("color:white;" "font-weight:bold;");
        classify9->setStyleSheet("color:white;" "font-weight:bold;");
    }
}

void PlayerControls::change(){
    QString str = dark->text();
    //std::cout<<"string = "<<str.toStdString()<<std::endl;
    if(dark->text().toStdString().compare("☽")==0){
        dark->setText("☀");
    }else{
        dark->setText("☽");
    }
}

