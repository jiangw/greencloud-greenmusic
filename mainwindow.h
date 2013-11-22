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
    ~MainWindow();

public slots:
    void SLOT_OpenMusicProc();

private:
    QMenu* m_pFileMenu;
    QAction* m_pOpenAct;
    QAction* m_pExitAct;

    CMusicView* m_pMusicView;
};

#endif // MAINWINDOW_H
