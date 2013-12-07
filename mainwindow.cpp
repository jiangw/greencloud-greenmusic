#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(200, 100, 800, 550);
//    this->setWindowFlags(Qt::FramelessWindowHint);

    m_pMusicView = new CMusicView(this);

    m_pFileMenu = this->menuBar()->addMenu("&File");

    m_pOpenAct = new QAction(this);
    m_pOpenAct->setText("&Open Music");
    m_pOpenAct->setShortcut(QString("Ctrl+O"));
    connect(m_pOpenAct, SIGNAL(triggered()), \
            m_pMusicView, SLOT(SLOT_LoadMusicProc()));

    m_pNewPlayListAct = new QAction(this);
    m_pNewPlayListAct->setText("&New Playlist");
    m_pNewPlayListAct->setShortcut(QString("Ctrl+N"));
    connect(m_pNewPlayListAct, SIGNAL(triggered()),\
            m_pMusicView, SLOT(SLOT_NewPlayListProc()));

    m_pLoadPlayListAct = new QAction(this);
    m_pLoadPlayListAct->setText("&Load Playlist");
    m_pLoadPlayListAct->setShortcut(QString("Ctrl+L"));
    connect(m_pLoadPlayListAct, SIGNAL(triggered()),\
            m_pMusicView, SLOT(SLOT_LoadPlayListProc()));

    m_pSavePlayListAct = new QAction(this);
    m_pSavePlayListAct->setText("&Save Playlist");
    m_pSavePlayListAct->setShortcut(QString("Ctrl+S"));
    connect(m_pSavePlayListAct, SIGNAL(triggered()),\
            m_pMusicView, SLOT(SLOT_SavePlayListProc()));

    m_pExitAct = new QAction(this);
    m_pExitAct->setShortcut(QKeySequence::Quit);
    m_pExitAct->setText("E&xit");
    connect(m_pExitAct, SIGNAL(triggered()), \
            this, SLOT(close()));

    m_pFileMenu->addAction(m_pOpenAct);
    m_pFileMenu->addAction(m_pNewPlayListAct);
    m_pFileMenu->addAction(m_pLoadPlayListAct);
    m_pFileMenu->addAction(m_pSavePlayListAct);
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(m_pExitAct);

    this->setCentralWidget(m_pMusicView);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_pMusicView->SavePlayListCheck();

    event->accept();
}
