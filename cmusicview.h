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
#include <QMessageBox>

#include "../GraphicsWidgetLib/csvgwidget.h"
#include "../GraphicsWidgetLib/cimgwidget.h"
#include "../GraphicsWidgetLib/ctextwidget.h"
#include "../GraphicsWidgetLib/cwidgetlist.h"
#include "cplaylist.h"

class CMusicView : public QGraphicsView
{
    Q_OBJECT
public:
    CMusicView(QWidget* a_pParent);
    void InitPhonon();
    void OpenMusic(QString a_qstrFileName, bool a_blPlay = false);
    void AppendMusic(QString a_qstrFileName);
    void OpenPlayList();
    void SavePlayListCheck();

protected:
    void wheelEvent(QWheelEvent *event);

public slots:
    void SLOT_LoadMusicProc();
    void SLOT_LoadMusicCoverProc();
    void SLOT_LoadArtistPhotoProc();
    void SLOT_CurrSrcChangeProc();
    void SLOT_CurrStateChangeProc(Phonon::State a_ENewState,Phonon::State a_EOldState);
    void SLOT_MusicPlayProc();
    void SLOT_MusicPauseProc();
    void SLOT_MusicStopProc();
    void SLOT_MusicNextProc();
    void SLOT_MusicPrevProc();
    void SLOT_AddMusicToPlayListProc();
    void SLOT_SavePlayListProc();
    void SLOT_LoadPlayListProc();
    void SLOT_NewPlayListProc();

    void SLOT_MouseDragDropProc(QPointF a_CMouseScenePos, CGraphicsWidget* a_pWhoAmI);

private:
    void AddMusicShortcutToPlayListView(QString a_qstrCoverFile,\
                                        QString a_qstrMusicTitle,\
                                        QString a_qstrArtist);
    void RemoveMusicFromQueue(QString a_qstrMusicFileName);
    QGraphicsScene* m_pScene;
    CImgWidget* m_pCover;
    CImgWidget* m_pArtistPhoto;
    CSvgWidget* m_pPlayBtn;
    CSvgWidget* m_pPauseBtn;
    CSvgWidget* m_pStopBtn;
    CSvgWidget* m_pNextBtn;
    CSvgWidget* m_pPrevBtn;
    CSvgWidget* m_pTrash;
    CTextWidget* m_pMusicTitle;
    CTextWidget* m_pArtistName;
    CSvgWidget* m_pAddBtn;
    CWidgetList* m_pPlayListView;

    QFont m_CArtistNameFont;
    QFont m_CMusicTitleFont;

    Phonon::MediaObject* m_pMediaObj;
    Phonon::AudioOutput* m_pAudioOutput;
    Phonon::Path m_CMO2AO;

    CPlayList m_CPlayList;

    int m_iMusicShortCutSize;
};

#endif // CMUSICVIEW_H
