#include "cmusicview.h"

CMusicView::CMusicView(QWidget *a_pParent)
    :QGraphicsView(a_pParent)
{
    m_pScene = new QGraphicsScene(a_pParent);
    m_pScene->setBackgroundBrush(Qt::lightGray);
    m_pScene->setSceneRect(-250, -250, 500, 500);
    this->setScene(m_pScene);

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    InitPhonon();

    m_CArtistNameFont.setFamily("STKaiti");
    m_CArtistNameFont.setPointSize(13);

    m_CMusicTitleFont.setFamily("STXinwei");
    m_CMusicTitleFont.setPointSize(18);

    m_pMusicTitle = new CTextWidget(false, NULL);
    m_pMusicTitle->SetText("Double click to open music");
    m_pMusicTitle->setPos(-200, -230);
    m_pScene->addItem(m_pMusicTitle);
    connect(m_pMusicTitle, SIGNAL(SIGNAL_MouseDoubleClicked()),\
            this, SLOT(SLOT_LoadMusicProc()));

    m_pCover = new CImgWidget(200, 200, NULL);
    m_pScene->addItem(m_pCover);
    m_pCover->setPos(-200, -200);
    connect(m_pCover, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_LoadMusicCoverProc()));

    m_pArtistPhoto = new CImgWidget(80, 80, NULL);
    m_pScene->addItem(m_pArtistPhoto);
    m_pArtistPhoto->setPos(10, -200);
    connect(m_pArtistPhoto, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_LoadArtistPhotoProc()));

    m_pArtistName = new CTextWidget(true, NULL);
    m_pArtistName->SetFont(m_CArtistNameFont);
    m_pArtistName->setVisible(false);
    m_pArtistName->SetWidgetOutline(false);
    m_pArtistName->setPos(10, -120);
    m_pScene->addItem(m_pArtistName);

    int l_iSize = 30;
    int l_iInterval = 30;
    int l_iY = 20;

    m_pPrevBtn = new CSvgWidget(":/icon/icon_prev", l_iSize * 1.5, l_iSize, NULL);
    m_pPrevBtn->setPos(m_pCover->pos().x(), l_iY);
    m_pScene->addItem(m_pPrevBtn);
    connect(m_pPrevBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicPrevProc()));

    m_pStopBtn = new CSvgWidget(":/icon/icon_stop", l_iSize, l_iSize, NULL);
    m_pStopBtn->setPos(m_pPrevBtn->pos().x() + m_pPrevBtn->boundingRect().width() + l_iInterval,\
                       l_iY);
    m_pScene->addItem(m_pStopBtn);
    connect(m_pStopBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicStopProc()));

    m_pPlayBtn = new CSvgWidget(":/icon/icon_play", l_iSize, l_iSize, NULL);
    m_pPlayBtn->setPos(m_pStopBtn->pos().x() + l_iSize + l_iInterval, l_iY);
    m_pScene->addItem(m_pPlayBtn);
    connect(m_pPlayBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicPlayProc()));

    m_pPauseBtn = new CSvgWidget(":/icon/icon_pause", l_iSize, l_iSize, NULL);
    m_pPauseBtn->setPos(m_pPlayBtn->pos().x() + l_iSize + l_iInterval, l_iY);
    m_pScene->addItem(m_pPauseBtn);
    connect(m_pPauseBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicPauseProc()));

    m_pNextBtn = new CSvgWidget(":/icon/icon_next", l_iSize * 1.5, l_iSize, NULL);
    m_pNextBtn->setPos(m_pPauseBtn->pos().x() + l_iSize + l_iInterval, l_iY);
    m_pScene->addItem(m_pNextBtn);
    connect(m_pNextBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicNextProc()));

    m_pAddBtn = new CSvgWidget(":/icon/icon_add", 25, 25, NULL);
    m_pAddBtn->setPos(3, -25);
    m_pAddBtn->setToolTip("Add music to playlist");
    m_pScene->addItem(m_pAddBtn);
    connect(m_pAddBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_AddMusicToPlayListProc()));

    m_pPlayListView = new CWidgetList(NULL);
    CTextWidget* l_pPlayListTitle = new CTextWidget(false, NULL);
    l_pPlayListTitle->SetWidgetOutline(false);
    l_pPlayListTitle->SetText("Play List");
    m_pPlayListView->SetHeaderWidget(l_pPlayListTitle);
    m_pPlayListView->SetListOrientation(CWidgetList::VERTICAL);
    m_pPlayListView->SetWidgetOutline(false);
    m_pPlayListView->setPos(m_pArtistPhoto->pos().x() + m_pArtistPhoto->boundingRect().width()\
                            + 50,\
                            m_pMusicTitle->pos().y());
    m_pScene->addItem(m_pPlayListView);

    this->centerOn(0, -100);
}

void CMusicView::InitPhonon()
{
    m_pMediaObj = new Phonon::MediaObject(this);
    m_pAudioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    m_CMO2AO = Phonon::createPath(m_pMediaObj, m_pAudioOutput);

    connect(m_pMediaObj, SIGNAL(currentSourceChanged(Phonon::MediaSource)), \
            this, SLOT(SLOT_CurrSrcChangeProc()));
    connect(m_pMediaObj, SIGNAL(stateChanged(Phonon::State,Phonon::State)), \
            this, SLOT(SLOT_CurrStateChangeProc(Phonon::State,Phonon::State)));
}

void CMusicView::OpenMusic(QString a_qstrFileName, bool a_blPlay)
{
    m_pCover->ClearImg();
    m_pArtistPhoto->ClearImg();

    m_pMediaObj->setCurrentSource(Phonon::MediaSource(a_qstrFileName));
    if(a_blPlay)
    {
        m_pMediaObj->play();
    }
    else
    {
        m_pMediaObj->pause();
    }
}

void CMusicView::AppendMusic(QString a_qstrFileName)
{
    m_pMediaObj->enqueue(Phonon::MediaSource(a_qstrFileName));
}

void CMusicView::OpenPlayList()
{
    QList<SMusic *>* l_pPlayList = m_CPlayList.GetPlayList();
    m_pPlayListView->ClearList();
    m_pMediaObj->clearQueue();

    for(int i=0; i<l_pPlayList->length(); i++)
    {
        SMusic* l_pMusic = l_pPlayList->at(i);
        if(0 == i) //load the first song to play
        {
            this->OpenMusic(l_pMusic->m_qstrMusicFile);
            m_pCover->SetImg(l_pMusic->m_qstrCoverImgFile);
            m_pArtistPhoto->SetImg(l_pMusic->m_qstrArtistPhotoFile);
        }
        else //add other songs to queue
        {
            this->AppendMusic(l_pMusic->m_qstrMusicFile);
        }
        this->AddMusicShortcutToPlayListView(l_pMusic->m_qstrCoverImgFile,\
                                             l_pMusic->m_qstrMusicTitle,\
                                             l_pMusic->m_qstrArtist);
    }
}

void CMusicView::SLOT_LoadMusicProc()
{
    QString l_strFileName = QFileDialog::getOpenFileName(this,
         "Open Music", "/home/Share/SharedMusic", "Music Files (*.mp3 *.flac *.wav)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        this->OpenMusic(l_strFileName);
    }
}

void CMusicView::SLOT_LoadMusicCoverProc()
{
    if(m_pMediaObj->currentSource().type() == Phonon::MediaSource::Invalid\
            || m_pMediaObj->currentSource().type() == Phonon::MediaSource::Empty)
    {
        return;
    }

    QString l_strFileName = QFileDialog::getOpenFileName(this,
         "Open Album Cover", "/home/Share/SharedMusic", "Image Files (*.jpg *.png)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        m_pCover->SetImg(l_strFileName);
    }
}

void CMusicView::SLOT_LoadArtistPhotoProc()
{
    if(m_pMediaObj->currentSource().type() == Phonon::MediaSource::Invalid\
            || m_pMediaObj->currentSource().type() == Phonon::MediaSource::Empty)
    {
        return;
    }

    QString l_strFileName = QFileDialog::getOpenFileName(this,
         "Open Artist Photo", "/home/Share/SharedMusic", "Image Files (*.jpg *.png)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        m_pArtistPhoto->SetImg(l_strFileName);
    }
}

void CMusicView::SLOT_CurrSrcChangeProc()
{
    QString l_qstrTitle = m_pMediaObj->metaData("TITLE")[0];
    m_pMusicTitle->SetText(l_qstrTitle);
    m_pMusicTitle->SetFont(m_CMusicTitleFont);
    m_pMusicTitle->SetWidgetOutline(false);

    QString l_qstrArtist = m_pMediaObj->metaData("ARTIST")[0];
    m_pArtistName->SetText(l_qstrArtist);
    m_pArtistName->setVisible(true);

    //update cover and artist photo
    SMusic* l_pMusic = m_CPlayList.GetMusic(l_qstrTitle, l_qstrArtist);
    if(NULL != l_pMusic)
    {
        m_pCover->SetImg(l_pMusic->m_qstrCoverImgFile);
        m_pArtistPhoto->SetImg(l_pMusic->m_qstrArtistPhotoFile);
    }
}

void CMusicView::SLOT_CurrStateChangeProc(Phonon::State a_ENewState, \
                                          Phonon::State /*a_EOldState*/)
{
    if(Phonon::StoppedState == a_ENewState)
    {
    }
}

void CMusicView::SLOT_MusicPlayProc()
{
    m_pMediaObj->play();
}

void CMusicView::SLOT_MusicPauseProc()
{
    m_pMediaObj->pause();
}

void CMusicView::SLOT_MusicStopProc()
{
    m_pMediaObj->stop();
}

void CMusicView::SLOT_MusicPrevProc()
{
}

void CMusicView::SLOT_MusicNextProc()
{
}

void CMusicView::SLOT_AddMusicToPlayListProc()
{
    if(m_pMediaObj->currentSource().type() != Phonon::MediaSource::Empty\
            && m_pMediaObj->currentSource().type() != Phonon::MediaSource::Invalid)
    {
        if(m_CPlayList.AddMusic(m_pMusicTitle->GetText(), m_pArtistName->GetText(),\
                             m_pMediaObj->currentSource().fileName(),\
                             m_pCover->GetFileName(), m_pArtistPhoto->GetFileName()))
        {
            this->AddMusicShortcutToPlayListView(m_pCover->GetFileName(),\
                                                 m_pMusicTitle->GetText(),\
                                                 m_pArtistName->GetText());
        }
    }
}

void CMusicView::SLOT_SavePlayListProc()
{
    QString l_strFileName = QFileDialog::getSaveFileName(this,
         "Save Play List", "/home/Share/SharedMusic", "Playlist Files (*.pl)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        m_CPlayList.SavePlayList(l_strFileName);
    }
}

void CMusicView::SLOT_LoadPlayListProc()
{
    QString l_strFileName = QFileDialog::getOpenFileName(this,
         "Load Play List", "/home/Share/SharedMusic", "Playlist Files (*.pl)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        m_CPlayList.LoadPlayList(l_strFileName);
        this->OpenPlayList();
    }
}

void CMusicView::AddMusicShortcutToPlayListView(QString a_qstrCoverFile,\
                                                QString a_qstrMusicTitle,\
                                                QString a_qstrArtist)
{
    CImgWidget* l_pNewMusicShortCut = new CImgWidget(40, 40, NULL);
    l_pNewMusicShortCut->SetImg(a_qstrCoverFile);
    l_pNewMusicShortCut->setToolTip(\
                QString("%1 - %2").arg(a_qstrMusicTitle).arg(a_qstrArtist));
    m_pPlayListView->AddWidget(l_pNewMusicShortCut);
}
