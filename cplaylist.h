#ifndef CPLAYLIST_H
#define CPLAYLIST_H

#include <QString>
#include <QList>
#include <QFile>
#include <QDataStream>

#include <iostream>

struct SMusic
{
    QString m_qstrMusicTitle;
    QString m_qstrArtist;
    QString m_qstrMusicFile;
    QString m_qstrCoverImgFile;
    QString m_qstrArtistPhotoFile;
};

class CPlayList
{
public:
    CPlayList();
    ~CPlayList();
    void ClearPlayList();
    QList<SMusic *>* GetPlayList()\
    {return &m_CPlayList;}
    bool IsChanged()\
    {return m_blPlaylistChanged;}
    SMusic* GetMusic(QString a_qstrMusicTitle, QString a_qstrArtistName);

    bool AddMusic(QString a_qstrMusicTitle, QString a_qstrArtist,\
                  QString a_qstrMusicFile, QString a_qstrCoverImgFile,\
                  QString a_qstrArtistPhotoFile);
    bool RemoveMusic(QString a_qstrMusicTitle, QString a_qstrArtist);
    bool RemoveMusic(int a_iMusicIdx);
    int MusicInList(QString a_qstrMusicTitle, QString a_qstrArtist);
    void SavePlayList(QString a_qstrFileName);
    void LoadPlayList(QString a_qstrFileName);

private:
    QList<SMusic *> m_CPlayList;
    bool m_blPlaylistChanged;
};

#endif // CPLAYLIST_H
