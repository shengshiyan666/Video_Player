#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QMediaPlayer>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE

class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerControls(QWidget *parent = nullptr);
    int flag;
    QWidget window;
    qreal playbackRate() const;

    QLineEdit *edit = nullptr;
    QPushButton *search = nullptr;
    QPushButton *nextvideo = nullptr;
    QPushButton* fullScreenvideo = nullptr;
    QPushButton* resetvideo = nullptr;
    QPushButton* beforevideo = nullptr;
    QPushButton *openvideo = nullptr;
    QScrollArea *scrollarea = nullptr;
    QPushButton* volume = nullptr;
    QComboBox *m_rateBox = nullptr;
    QPushButton *start = nullptr;
    QPushButton *stop = nullptr;
    QPushButton *dark = nullptr;

    QPushButton *classify = nullptr;
    QPushButton *classify1 = nullptr;
    QPushButton *classify2 = nullptr;
    QPushButton *classify3 = nullptr;
    QPushButton *classify4 = nullptr;
    QPushButton *classify5 = nullptr;
    QPushButton *classify6 = nullptr;
    QPushButton *classify7 = nullptr;
    QPushButton *classify8 = nullptr;
    QPushButton *classify9 = nullptr;
public slots:
    void setPlaybackRate(float rate);
    void updateRate();
    void darkmethod();
    void change();
signals:
    void changeRate(qreal rate);

private:
};

#endif // PLAYERCONTROLS_H
