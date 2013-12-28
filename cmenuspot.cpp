#include "cmenuspot.h"

CMenuSpot::CMenuSpot(CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    qreal l_dRatioWid = 0.95;
    qreal l_dRatioHgt = 0.5;
    m_iStartIconWidth = qFloor(100 * l_dRatioWid);
    m_iOpenIconWidth = qFloor(90 * l_dRatioWid);
    m_iNewPLIconWidth = qFloor(90 * l_dRatioWid);
    m_iLoadPLIconWidth = qFloor(150 * l_dRatioWid);
    m_iSavePLIconWidth = qFloor(150 * l_dRatioWid);
    m_iExitIconWidth = qFloor(80 * l_dRatioWid);
    m_iWidgetHeight = qFloor(120 * l_dRatioHgt);

    m_pStartIcon = new CSvgWidget(ICON_START,\
                                  82 * l_dRatioHgt, 172 * l_dRatioHgt,\
                                  this);
    m_pStartIcon->setToolTip("Start");
    m_pStartIcon->setPos((m_iStartIconWidth - m_pStartIcon->boundingRect().width()) / 2,\
                         -(m_pStartIcon->boundingRect().height() - m_iWidgetHeight));
    connect(m_pStartIcon, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MenuSpotSwitchProc()));

    int x = m_iStartIconWidth;
    m_pOpenIcon = new CSvgWidget(ICON_OPEN,\
                                 68 * l_dRatioHgt, 90 * l_dRatioHgt,\
                                 this);
    m_pOpenIcon->setToolTip("Open Music");
    m_pOpenIcon->setPos(x + (m_iOpenIconWidth - m_pOpenIcon->boundingRect().width()) / 2,\
                        0);
    connect(m_pOpenIcon, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_OpenMusicEmit()));

    x += m_iOpenIconWidth;
    m_pNewPLIcon = new CSvgWidget(ICON_NEWPL,\
                                  47 * l_dRatioHgt, 90 * l_dRatioHgt,\
                                  this);
    m_pNewPLIcon->setToolTip("New Playlist");
    m_pNewPLIcon->setPos(x + (m_iNewPLIconWidth - m_pNewPLIcon->boundingRect().width()) / 2,\
                         m_iWidgetHeight - m_pNewPLIcon->boundingRect().height());
    connect(m_pNewPLIcon, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_NewPLEmit()));

    x += m_iNewPLIconWidth;
    m_pLoadPLIcon = new CSvgWidget(ICON_LOADPL,\
                                   139 * l_dRatioHgt, 120 * l_dRatioHgt,\
                                   this);
    m_pLoadPLIcon->setToolTip("Load Playlist");
    m_pLoadPLIcon->setPos(x + (m_iLoadPLIconWidth - m_pLoadPLIcon->boundingRect().width()) / 2,\
                          0);
    connect(m_pLoadPLIcon, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_LoadPLEmit()));

    x += m_iLoadPLIconWidth;
    m_pSavePLIcon = new CSvgWidget(ICON_SAVEPL,\
                                   142 * l_dRatioHgt, 116 * l_dRatioHgt,\
                                   this);
    m_pSavePLIcon->setToolTip("Save Playlist");
    m_pSavePLIcon->setPos(x + (m_iSavePLIconWidth - m_pSavePLIcon->boundingRect().width()) / 2,\
                          0);
    connect(m_pSavePLIcon, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_SavePLEmit()));

    x += m_iSavePLIconWidth;
    m_pExitIcon = new CSvgWidget(ICON_EXIT,\
                                 45 * l_dRatioHgt, 111 * l_dRatioHgt,\
                                 this);
    m_pExitIcon->setToolTip("Exit");
    m_pExitIcon->setPos(x + (m_iExitIconWidth - m_pExitIcon->boundingRect().width()) / 2,\
                        (m_iWidgetHeight - m_pExitIcon->boundingRect().height()) / 2);
    connect(m_pExitIcon, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_ExitEmit()));

    m_blCollapsed = true;
    if(m_blCollapsed)
    {
        m_pOpenIcon->setVisible(false);
        m_pNewPLIcon->setVisible(false);
        m_pLoadPLIcon->setVisible(false);
        m_pSavePLIcon->setVisible(false);
        m_pExitIcon->setVisible(false);
    }

    this->InitBoundingRect();
}

int CMenuSpot::WidgetWidth()
{
    if(m_blCollapsed)
    {
        return m_iStartIconWidth;
    }
    return m_iStartIconWidth + m_iOpenIconWidth + m_iNewPLIconWidth\
            + m_iLoadPLIconWidth + m_iSavePLIconWidth + m_iExitIconWidth;
}

int CMenuSpot::WidgetHeight()
{
    return m_iWidgetHeight;
}

void CMenuSpot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    //draw FIVE lines
    int l_iInterval = this->boundingRect().height() / 4;
    int x=0, y=0;
    for(int i=0; i<5; i++)
    {
        y = i * l_iInterval;
        if(m_blCollapsed)
        {
            painter->drawLine(x, y, m_iStartIconWidth, y);
        }
        else
        {
            painter->drawLine(x, y, this->boundingRect().width(), y);
        }
    }
    if(!m_blCollapsed)
    {
        //draw section line for START icon
        painter->drawLine(m_iStartIconWidth - 2, 0,\
                          m_iStartIconWidth - 2, m_iWidgetHeight);
        painter->drawLine(m_iStartIconWidth + 2, 0,\
                          m_iStartIconWidth + 2, m_iWidgetHeight);
        //draw section line for OPEN icon
        x = m_iStartIconWidth + m_iOpenIconWidth;
        painter->drawLine(x - 2, 0,\
                          x - 2, m_iWidgetHeight);
        painter->drawLine(x + 2, 0,\
                          x + 2, m_iWidgetHeight);
        //draw paragraph line for NEWPL icon
        x += m_iNewPLIconWidth;
        painter->drawLine(x, 0,\
                          x, m_iWidgetHeight);
        //draw paragraph line for LOADPL icon
        x += m_iLoadPLIconWidth;
        painter->drawLine(x, 0,\
                          x, m_iWidgetHeight);
        //draw section line for SAVEPL icon
        x += m_iSavePLIconWidth;
        painter->drawLine(x - 2, 0,\
                          x - 2, m_iWidgetHeight);
        painter->drawLine(x + 2, 0,\
                          x + 2, m_iWidgetHeight);
    }
    //draw end line
    painter->drawLine(this->boundingRect().width() - 10, 0,\
                      this->boundingRect().width() - 10, m_iWidgetHeight);
    painter->setPen(QPen(QBrush(Qt::black), 6));
    painter->drawLine(this->boundingRect().width() - 2, 2,\
                      this->boundingRect().width() - 2, m_iWidgetHeight - 2);

    painter->restore();
}

void CMenuSpot::SLOT_MenuSpotSwitchProc()
{
    m_blCollapsed = !m_blCollapsed;
    m_pOpenIcon->setVisible(!m_pOpenIcon->isVisible());
    m_pNewPLIcon->setVisible(!m_pNewPLIcon->isVisible());
    m_pLoadPLIcon->setVisible(!m_pLoadPLIcon->isVisible());
    m_pSavePLIcon->setVisible(!m_pSavePLIcon->isVisible());
    m_pExitIcon->setVisible(!m_pExitIcon->isVisible());
    this->UpdateBoundingRect();
}

void CMenuSpot::SLOT_OpenMusicEmit()
{
    emit this->SIGNAL_OpenMusic();
}

void CMenuSpot::SLOT_NewPLEmit()
{
    emit this->SIGNAL_NewPL();
}

void CMenuSpot::SLOT_LoadPLEmit()
{
    emit this->SIGNAL_LoadPL();
}

void CMenuSpot::SLOT_SavePLEmit()
{
    emit this->SIGNAL_SavePL();
}

void CMenuSpot::SLOT_ExitEmit()
{
    emit this->SIGNAL_Exit();
}
