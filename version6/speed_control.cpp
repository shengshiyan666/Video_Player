#include "speed_control.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <QAudio>

SpeedControl::SpeedControl(QWidget *parent)
    : QWidget(parent)
{

    connect(m_rateBox, QOverload<int>::of(&QComboBox::activated), this, &SpeedControl::updateRate);

    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(m_rateBox);
    setLayout(layout);
}


void SpeedControl::updateRate()
{
    emit changeRate(playbackRate());
}
