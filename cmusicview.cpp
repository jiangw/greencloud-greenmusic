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

    m_pPlayBtn = new CSvgWidget(":/icon/icon_play", 40, 40, NULL);
    m_pPlayBtn->setPos(-120, 10);
    m_pScene->addItem(m_pPlayBtn);
    connect(m_pPlayBtn, SIGNAL(SIGNAL_LeftButtonClicked()),\
            this, SLOT(SLOT_MusicPlayProc()));

    this->ensureVisible(-250, -250, 300, 300);
}

void CMusicView::SimpleViewCreate()
{
    /*
    m_pTitle = new QGraphicsSimpleTextItem(NULL);
    m_pTitle->setText("Welcome to use GreenMusic");
    m_pTitle->setPos(-m_pTitle->boundingRect().width() / 2, \
                     -m_pTitle->boundingRect().height() / 2 - 80);
    m_pScene->addItem(m_pTitle);

    m_pPlayBtn = new CPlayButton(NULL);
    m_pPlayBtn->setPos(-m_pPlayBtn->boundingRect().width() / 2, \
                       -m_pPlayBtn->boundingRect().height() / 2);
    m_pScene->addItem(m_pPlayBtn);

    connect(m_pPlayBtn, SIGNAL(SIGNAL_MusicPlay()), \
            this, SLOT(SLOT_MusicPlayProc()));
    connect(m_pPlayBtn, SIGNAL(SIGNAL_MusicPause()), \
            this, SLOT(SLOT_MusicPauseProc()));

    this->centerOn(0, 0);
    */
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

void CMusicView::SLOT_LoadMusicProc()
{
    QString l_strFileName = QFileDialog::getOpenFileName(this,
         "Open Music", "/home/Share/SharedMusic", "Music Files (*.mp3 *.flac *.wav)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        m_pMediaObj->enqueue(Phonon::MediaSource(l_strFileName));
        m_pMediaObj->pause();
    }
}

void CMusicView::SLOT_LoadMusicCoverProc()
{
    QString l_strFileName = QFileDialog::getOpenFileName(this,
         "Open Album Cover", "/home/Share/SharedMusic", "Image Files (*.jpg *.png)");
    if(!l_strFileName.isNull() && !l_strFileName.isEmpty())
    {
        m_pCover->SetImg(l_strFileName);
    }
}

void CMusicView::SLOT_LoadArtistPhotoProc()
{
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
    //convert unicode encoding to Chinese encoding
    /*
    QTextCodec* l_pCnCodec = QTextCodec::codecForName("GB18030");
    if(NULL != l_pCnCodec)
    {
        QByteArray l_CEncodedStr = l_pCnCodec->fromUnicode(l_qstrTitle);
        QString l_qstrTitle1(l_CEncodedStr);
        std::cout << l_qstrTitle1.toStdString() << std::endl;
    }
    */
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
