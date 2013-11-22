#ifndef CPLAYBUTTON_H
#define CPLAYBUTTON_H

#include "../GraphicsWidgetLib/cgraphicswidget.h"

#include <QtCore/qmath.h>

class CPlayButton: public CGraphicsWidget
{
    Q_OBJECT

public:
    CPlayButton(CGraphicsWidget *a_pParent);
    void Enable(bool a_blEnable);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void LeftButtonClicked(QPointF a_CMousePos);

public slots:
    void SLOT_MusicStopProc();

signals:
    void SIGNAL_MusicPlay();
    void SIGNAL_MusicPause();

private:
    void IconInit();

    int m_iRadius; //play-button is a circle
    QPainterPath m_CPlayIcon;
    QPainterPath m_CPauseIcon;
    bool m_blPlay; //1: play 0: pause
    bool m_blEnabled;
};

#endif // CPLAYBUTTON_H
