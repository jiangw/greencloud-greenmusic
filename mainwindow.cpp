#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(200, 100, 600, 600);
//    this->setWindowFlags(Qt::FramelessWindowHint);

    m_pFileMenu = this->menuBar()->addMenu("&File");

    m_pOpenAct = new QAction(this);
    m_pOpenAct->setText("&Open Music");
    m_pOpenAct->setShortcut(QString("Ctrl+O"));
    connect(m_pOpenAct, SIGNAL(triggered()), \
            this, SLOT(SLOT_OpenMusicProc()));

    m_pExitAct = new QAction(this);
    m_pExitAct->setShortcut(QKeySequence::Quit);
    m_pExitAct->setText("E&xit");
    connect(m_pExitAct, SIGNAL(triggered()), \
            this, SLOT(close()));

    m_pFileMenu->addAction(m_pOpenAct);
    m_pFileMenu->addAction(m_pExitAct);

    m_pMusicView = new CMusicView(this);
    this->setCentralWidget(m_pMusicView);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::SLOT_OpenMusicProc()
{
    m_pMusicView->SLOT_LoadMusicProc();
}
