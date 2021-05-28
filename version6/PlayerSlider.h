
#ifndef CWK2_PLAYERSLIDER_H
#define CWK2_PLAYERSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include "the_player.h"


class PlayerSlider : public QSlider
{
    Q_OBJECT
public:
    PlayerSlider(QWidget * parent = 0);
    void        getplayer(ThePlayer* play);
    void        setProgress(qint64);
    signals:
    void        costomSliderClicked();
    void        sigProgress(qint64);

private:
    bool        m_bPressed;
    ThePlayer   *player;


protected:
    void mousePressEvent(QMouseEvent *e);
public slots:
    void onTimerOut();

};



#endif //CWK2_PLAYERSLIDER_H
