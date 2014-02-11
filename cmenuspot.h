#ifndef CMENUSPOT_H
#define CMENUSPOT_H

#include "../GraphicsWidgetLib/cgraphicswidget.h"
#include "../GraphicsWidgetLib/csvgwidget.h"

#define ICON_START ":/icon/icon_start"
#define ICON_OPEN ":/icon/icon_open"
#define ICON_NEWPL ":/icon/icon_newpl"
#define ICON_LOADPL ":/icon/icon_loadpl"
#define ICON_SAVEPL ":/icon/icon_savepl"
#define ICON_EXIT ":/icon/icon_exit"

class CMenuSpot : public CGraphicsWidget
{
    Q_OBJECT

public:
    enum EPlayStat{PLAY, PAUSE, STOP};
    CMenuSpot(CGraphicsWidget* a_pParent);
    void SetPlayStat(EPlayStat a_EPlayStat);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void SLOT_MenuSpotSwitchProc();
    void SLOT_OpenMusicEmit();
    void SLOT_NewPLEmit();
    void SLOT_LoadPLEmit();
    void SLOT_SavePLEmit();
    void SLOT_ExitEmit();

signals:
    void SIGNAL_OpenMusic();
    void SIGNAL_NewPL();
    void SIGNAL_LoadPL();
    void SIGNAL_SavePL();
    void SIGNAL_Exit();

private:
    int m_iStartIconWidth;
    CSvgWidget* m_pStartIcon;
    int m_iOpenIconWidth;
    CSvgWidget* m_pOpenIcon;
    int m_iNewPLIconWidth;
    CSvgWidget* m_pNewPLIcon;
    int m_iLoadPLIconWidth;
    CSvgWidget* m_pLoadPLIcon;
    int m_iSavePLIconWidth;
    CSvgWidget* m_pSavePLIcon;
    int m_iExitIconWidth;
    CSvgWidget* m_pExitIcon;
    int m_iWidgetHeight;

    CSvgWidget* m_pPlayStat;

    bool m_blCollapsed;
};

#endif // CMENUSPOT_H
