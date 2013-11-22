#include "cplaybutton.h"

CPlayButton::CPlayButton(CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iRadius = 25;
    m_blPlay = false;
    m_blEnabled = false;
    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());

    this->IconInit();
}

void CPlayButton::Enable(bool a_blEnable)
{
    m_blEnabled = a_blEnable;
}

int CPlayButton::WidgetWidth()
{
    return m_iRadius * 2;
}

int CPlayButton::WidgetHeight()
{
    return m_iRadius * 2;
}

void CPlayButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(QPen(QBrush(Qt::black), 4));
    painter->drawEllipse(this->boundingRect());

    painter->setPen(QPen());
    if(!m_blPlay)
    {
        painter->fillPath(m_CPlayIcon, QBrush(Qt::darkGreen));
    }
    else
    {
        painter->fillPath(m_CPauseIcon, QBrush(Qt::darkGray));
    }

    painter->setBrush(QBrush(Qt::black));

    painter->restore();
}

void CPlayButton::IconInit()
{
    qreal x1 = m_iRadius / 2;
    qreal y1 = x1;
    qreal x2 = (1 + qSqrt(2) / 2) * m_iRadius;
    qreal y2 = m_iRadius;
    qreal x3 = x1;
    qreal y3 = 3 * m_iRadius / 2;
    m_CPlayIcon.moveTo(x1, y1);
    m_CPlayIcon.lineTo(x2, y2);
    m_CPlayIcon.lineTo(x3, y3);
    m_CPlayIcon.closeSubpath();

    m_CPauseIcon.addRect(m_iRadius / 2, m_iRadius / 2, m_iRadius / 4, m_iRadius);
    m_CPauseIcon.addRect(m_iRadius + m_iRadius / 4, m_iRadius / 2, m_iRadius / 4, m_iRadius);
}

void CPlayButton::LeftButtonClicked(QPointF a_CMousePos)
{
    Q_UNUSED(a_CMousePos);
    if(!m_blEnabled)
    {
        return;
    }

    m_blPlay = !m_blPlay;
    if(m_blPlay)
    {
        emit this->SIGNAL_MusicPlay();
    }
    else
    {
        emit this->SIGNAL_MusicPause();
    }
    update(this->boundingRect());
}

void CPlayButton::SLOT_MusicStopProc()
{
    if(!m_blEnabled)
    {
        return;
    }

    m_blPlay = false;
    update(this->boundingRect());
}
