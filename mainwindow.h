#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

#include "gconfig.h"
#include "cmusicview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent* event);

private:
    QMenu* m_pFileMenu;
    QAction* m_pOpenAct;
    QAction* m_pNewPlayListAct;
    QAction* m_pLoadPlayListAct;
    QAction* m_pSavePlayListAct;
    QAction* m_pExitAct;

    CMusicView* m_pMusicView;
};

#endif // MAINWINDOW_H
