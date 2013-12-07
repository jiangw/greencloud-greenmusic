#include "cmusicview.h"

CMusicView::CMusicView(QWidget *a_pParent)
    :QGraphicsView(a_pParent)
{
    m_iMusicShortCutSize = 60;

    m_pScene = new QGraphicsScene(a_pParent);
    m_pScene->setBackgroundBrush(QBrush(QPixmap(QString(":/img/sceneback"))));
    m_pScene->setSceneRect(-500, -500, 1000, 1000);
    this->setScene(m_pScene);

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    InitPhonon();

    m_CArtistNameFont.setFamily("STKaiti");
    m_CArtistNameFont.setPointSize(13);

    m_CMusicTitleFont.setFamily("STXinwei");
    m_CMusicTitleFont.setPointSize(18);

    m_pMusicTitle = new CTextWidget(false, NULL);
    m_pMusicTitle->SetEditable(true);
    m_pMusicTitle->SetWidgetOutline(false);
    m_pMusicTitle->SetFont(m_CMusicTitleFont);
    m_pMusicTitle->setVisible(false);
    m_pMusicTitle->setPos(-200, -230);
    m_pScene->addItem(m_pMusicTitle);

    m_pCover = new CImgWidget(300, 300, NULL);
    m_pScene->addItem(m_pCover);
    m_pCover->setPos(-200, -200);
    m_pCover->MouseDragSwitch(false);
    connect(m_pCover, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_LoadMusicCoverProc()));

    m_pArtistPhoto = new CImgWidget(120, 120, NULL);
    m_pArtistPhoto->MouseDragSwitch(false);
    m_pScene->addItem(m_pArtistPhoto);
    m_pArtistPhoto->setPos(m_pCover->pos().x() + m_pCover->boundingRect().width() + 10,\
                           -200);
    connect(m_pArtistPhoto, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_LoadArtistPhotoProc()));

    m_pArtistName = new CTextWidget(true, NULL);
    m_pArtistName->SetFont(m_CArtistNameFont);
    m_pArtistName->setVisible(false);
    m_pArtistName->SetWidgetOutline(false);
    m_pArtistName->setPos(m_pArtistPhoto->pos().x(),\
                          m_pArtistPhoto->pos().y() + m_pArtistPhoto->boundingRect().height());
    m_pScene->addItem(m_pArtistName);

    int l_iSize = 30;
    int l_iInterval = 30;
    int l_iY = 20;

    m_pPrevBtn = new CSvgWidget(":/icon/icon_prev", l_iSize * 1.5, l_iSize, NULL);
    m_pPrevBtn->setPos(m_pCover->pos().x(),\
                       m_pCover->pos().y() + m_pCover->boundingRect().height() + l_iY);
    m_pScene->addItem(m_pPrevBtn);
    connect(m_pPrevBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicPrevProc()));

    m_pStopBtn = new CSvgWidget(":/icon/icon_stop", l_iSize, l_iSize, NULL);
    m_pStopBtn->setPos(m_pPrevBtn->pos().x() + m_pPrevBtn->boundingRect().width() + l_iInterval,\
                       m_pPrevBtn->pos().y());
    m_pScene->addItem(m_pStopBtn);
    connect(m_pStopBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicStopProc()));

    m_pPlayBtn = new CSvgWidget(":/icon/icon_play", l_iSize, l_iSize, NULL);
    m_pPlayBtn->setPos(m_pStopBtn->pos().x() + l_iSize + l_iInterval, m_pPrevBtn->pos().y());
    m_pScene->addItem(m_pPlayBtn);
    connect(m_pPlayBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicPlayProc()));

    m_pPauseBtn = new CSvgWidget(":/icon/icon_pause", l_iSize, l_iSize, NULL);
    m_pPauseBtn->setPos(m_pPlayBtn->pos().x() + l_iSize + l_iInterval, m_pPrevBtn->pos().y());
    m_pScene->addItem(m_pPauseBtn);
    connect(m_pPauseBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicPauseProc()));

    m_pNextBtn = new CSvgWidget(":/icon/icon_next", l_iSize * 1.5, l_iSize, NULL);
    m_pNextBtn->setPos(m_pPauseBtn->pos().x() + l_iSize + l_iInterval, m_pPrevBtn->pos().y());
    m_pScene->addItem(m_pNextBtn);
    connect(m_pNextBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicNextProc()));

    m_pAddBtn = new CSvgWidget(":/icon/icon_add", 25, 25, NULL);
    m_pAddBtn->setPos(m_pCover->pos().x() + m_pCover->boundingRect().width() + 3,\
                      m_pCover->pos().y() + m_pCover->boundingRect().height() - 25);
    m_pAddBtn->setToolTip("Add song to playlist");
    m_pScene->addItem(m_pAddBtn);
    connect(m_pAddBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_AddMusicToPlayListProc()));

    m_pPlayListView = new CWidgetList(NULL);
    CTextWidget* l_pPlayListTitle = new CTextWidget(false, NULL);
    l_pPlayListTitle->SetWidgetOutline(false);
    l_pPlayListTitle->SetText("Play List");
    l_pPlayListTitle->SetFont(QFont("URW Chancery L"));
    l_pPlayListTitle->SetFontSize(14);
    m_pPlayListView->SetHeaderWidget(l_pPlayListTitle);
    m_pPlayListView->SetListOrientation(CWidgetList::VERTICAL);
    m_pPlayListView->SetWidgetOutline(false);
    m_pPlayListView->SetPageLength(5);
    m_pPlayListView->setPos(m_pArtistPhoto->pos().x() + m_pArtistPhoto->boundingRect().width()\
                            + 50,\
                            m_pMusicTitle->pos().y());
    m_pScene->addItem(m_pPlayListView);

    m_pTrash = new CSvgWidget(":/icon/icon_trash", 80, 90, NULL);
    m_pTrash->setPos(m_pPlayListView->pos().x() + m_pPlayListView->boundingRect().width() + 20,\
                     m_pPlayBtn->y() + m_pPlayBtn->boundingRect().height() + 10);
    m_pTrash->setToolTip("Remove song from playlist");
    m_pScene->addItem(m_pTrash);

    this->centerOn(m_pAddBtn->pos().x() + 50, m_pAddBtn->pos().y() - 80);
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
    m_pMediaObj->clearQueue();

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
    m_pPlayListView->ResetWidget();
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
    m_pPlayListView->SetPagePos(1);
}

void CMusicView::SavePlayListCheck()
{
    if(m_CPlayList.IsChanged())
    {
        QMessageBox l_CMsgBox(this->parentWidget());
        l_CMsgBox.setText("The playlist has been modified.");
        l_CMsgBox.setInformativeText("Do you want to save it?");
        l_CMsgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        l_CMsgBox.setDefaultButton(QMessageBox::Save);
        l_CMsgBox.setModal(true);
        l_CMsgBox.setIcon(QMessageBox::Warning);
        int l_iOption = l_CMsgBox.exec();
        if(QMessageBox::Save == l_iOption)
        {
            this->SLOT_SavePlayListProc();
        }
    }
}

void CMusicView::wheelEvent(QWheelEvent *event)
{
    if(!m_pPlayListView->contains(m_pPlayListView->mapFromScene(\
                                      this->mapToScene(event->pos()))))
    {
        event->ignore();
    }
    else
    {
        QGraphicsView::wheelEvent(event);
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
    QString l_qstrArtist = m_pMediaObj->metaData("ARTIST")[0];
    QString l_qstrTitle = m_pMediaObj->metaData("TITLE")[0];
    SMusic* l_pMusic = m_CPlayList.GetMusic(l_qstrTitle, l_qstrArtist);

    m_pMusicTitle->SetText(l_qstrTitle);
    m_pMusicTitle->setVisible(true);
    m_pArtistName->SetText(l_qstrArtist);
    m_pArtistName->setVisible(true);

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
    if(!m_pMediaObj->queue().isEmpty())
    {
        Phonon::State l_EPrevState = m_pMediaObj->state();
        m_pMediaObj->setCurrentSource(m_pMediaObj->queue().at(0));
        if(l_EPrevState == Phonon::PlayingState)
        {
            m_pMediaObj->play();
        }
        else
        {
            m_pMediaObj->pause();
        }
    }
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
    this->SavePlayListCheck();

    QString l_strFileName = QFileDialog::getOpenFileName(this,
         "Load Play List", "/home/Share/SharedMusic", "Playlist Files (*.pl)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        m_CPlayList.LoadPlayList(l_strFileName);
        this->OpenPlayList();
    }
}

void CMusicView::SLOT_NewPlayListProc()
{
    this->SavePlayListCheck();

    m_pMediaObj->clearQueue();
    m_pPlayListView->ResetWidget();
    m_CPlayList.ClearPlayList();
}

void CMusicView::SLOT_MouseDragDropProc(QPointF a_CMouseScenePos, CGraphicsWidget *a_pWhoAmI)
{
    if("CImgWidget" == a_pWhoAmI->WidgetClassName())
    {
        if(m_pCover->contains(m_pCover->mapFromScene(a_CMouseScenePos)))
        {//open the song from playlist
            int l_iMusicIdx = m_pPlayListView->IndexOf(a_pWhoAmI);
            if(-1 != l_iMusicIdx)
            {
                QList<SMusic *>* l_CQueue = m_CPlayList.GetPlayList();
                SMusic* l_pMusic = l_CQueue->at(l_iMusicIdx);
                this->OpenMusic(l_pMusic->m_qstrMusicFile, true);
                m_pMusicTitle->SetText(l_pMusic->m_qstrMusicTitle);
                m_pArtistName->SetText(l_pMusic->m_qstrArtist);
                m_pCover->SetImg(l_pMusic->m_qstrCoverImgFile);
                m_pArtistPhoto->SetImg(l_pMusic->m_qstrArtistPhotoFile);

                //update play queue
                for(int i=l_iMusicIdx+1; i<l_CQueue->length(); i++)
                {
                    this->AppendMusic((l_CQueue->at(i))->m_qstrMusicFile);
                }
            }
        }
        else if(m_pTrash->contains(m_pTrash->mapFromScene(a_CMouseScenePos)))
        {//remove the song from playlist
            int l_iMusicIdx = m_pPlayListView->IndexOf(a_pWhoAmI);
            if(-1 != l_iMusicIdx)
            {
                SMusic* l_pMusic = m_CPlayList.GetPlayList()->at(l_iMusicIdx);
                QMessageBox l_CMsgBox(this->parentWidget());
                l_CMsgBox.setInformativeText(QString("%1 - %2").arg(l_pMusic->m_qstrMusicTitle)\
                                  .arg(l_pMusic->m_qstrArtist));
                l_CMsgBox.setText("Remove the song from playlist?");
                l_CMsgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                l_CMsgBox.setDefaultButton(QMessageBox::Yes);
                l_CMsgBox.setModal(true);
                l_CMsgBox.setIcon(QMessageBox::Warning);
                int l_iOption = l_CMsgBox.exec();
                if(QMessageBox::Yes == l_iOption)
                {
                    this->RemoveMusicFromQueue(m_CPlayList.GetPlayList()->at(l_iMusicIdx)->m_qstrMusicFile);
                    if(m_CPlayList.RemoveMusic(l_iMusicIdx))
                    {
                        m_pPlayListView->RemoveWidget(a_pWhoAmI);
                    }
                }
            }
        }
    }
}

void CMusicView::AddMusicShortcutToPlayListView(QString a_qstrCoverFile,\
                                                QString a_qstrMusicTitle,\
                                                QString a_qstrArtist)
{
    CImgWidget* l_pNewMusicShortCut = new CImgWidget(m_iMusicShortCutSize, m_iMusicShortCutSize,\
                                                     NULL);
    if(a_qstrCoverFile.isNull() || a_qstrCoverFile.isEmpty())
    {
        l_pNewMusicShortCut->SetImg(":/img/defaultcover");
    }
    else
    {
        l_pNewMusicShortCut->SetImg(a_qstrCoverFile);
    }
    l_pNewMusicShortCut->setToolTip(\
                QString("%1 - %2").arg(a_qstrMusicTitle).arg(a_qstrArtist));
    m_pPlayListView->AddWidget(l_pNewMusicShortCut);
    connect(l_pNewMusicShortCut, SIGNAL(SIGNAL_MouseDragRelease(QPointF,CGraphicsWidget*)),\
            this, SLOT(SLOT_MouseDragDropProc(QPointF,CGraphicsWidget*)));
}

void CMusicView::RemoveMusicFromQueue(QString a_qstrMusicFileName)
{
    QList<Phonon::MediaSource> l_CQueue = m_pMediaObj->queue();
    for(int i=0; i<l_CQueue.length(); i++)
    {
        if(l_CQueue[i].fileName() == a_qstrMusicFileName)
        {
            l_CQueue.removeAt(i);
            m_pMediaObj->setQueue(l_CQueue);
            break;
        }
    }
}
