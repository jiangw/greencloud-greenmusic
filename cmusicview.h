#ifndef CMUSICVIEW_H
#define CMUSICVIEW_H

#include "gconfig.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsSimpleTextItem>
#include <Phonon/MediaObject>
#include <Phonon/MediaSource>
#include <Phonon/AudioOutput>
#include <Phonon/Path>
#include <QFileDialog>
#include <QFont>

#include "../GraphicsWidgetLib/csvgwidget.h"
#include "../GraphicsWidgetLib/cimgwidget.h"
#include "../GraphicsWidgetLib/ctextwidget.h"

class CMusicView : public QGraphicsView
{
    Q_OBJECT
public:
    CMusicView(QWidget* a_pParent);

    void SimpleViewCreate();
    void InitPhonon();

public slots:
    void SLOT_LoadMusicProc();
    void SLOT_LoadMusicCoverProc();
    void SLOT_LoadArtistPhotoProc();
    void SLOT_CurrSrcChangeProc();
    void SLOT_CurrStateChangeProc(Phonon::State a_ENewState,Phonon::State a_EOldState);
    void SLOT_MusicPlayProc();
    void SLOT_MusicPauseProc();

private:
    QGraphicsScene* m_pScene;
    CImgWidget* m_pCover;
    CImgWidget* m_pArtistPhoto;
    CSvgWidget* m_pPlayBtn;
    CTextWidget* m_pMusicTitle;
    CTextWidget* m_pArtistName;

    QFont m_CArtistNameFont;
    QFont m_CMusicTitleFont;

    Phonon::MediaObject* m_pMediaObj;
    Phonon::AudioOutput* m_pAudioOutput;
    Phonon::Path m_CMO2AO;
};

#endif // CMUSICVIEW_H
