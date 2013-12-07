#include "cplaylist.h"

CPlayList::CPlayList()
{
    m_blPlaylistChanged = false;
}

CPlayList::~CPlayList()
{
    this->ClearPlayList();
}

void CPlayList::ClearPlayList()
{
    for(int i=0; i<m_CPlayList.length(); i++)
    {
        delete m_CPlayList[i];
    }
    m_CPlayList.clear();
}

SMusic* CPlayList::GetMusic(QString a_qstrMusicTitle, QString a_qstrArtistName)
{
    int l_iMusicIdx = this->MusicInList(a_qstrMusicTitle, a_qstrArtistName);
    if(-1 == l_iMusicIdx)
    {
        return NULL;
    }
    else
    {
        return m_CPlayList[l_iMusicIdx];
    }
}

bool CPlayList::AddMusic(QString a_qstrMusicTitle, QString a_qstrArtist,\
                         QString a_qstrMusicFile, QString a_qstrCoverImgFile,\
                         QString a_qstrArtistPhotoFile)
{
    if(this->MusicInList(a_qstrMusicTitle, a_qstrArtist) == -1)
    {
        SMusic* l_pNewMusic = new SMusic;
        l_pNewMusic->m_qstrMusicTitle = a_qstrMusicTitle;
        l_pNewMusic->m_qstrArtist = a_qstrArtist;
        l_pNewMusic->m_qstrMusicFile = a_qstrMusicFile;
        l_pNewMusic->m_qstrCoverImgFile = a_qstrCoverImgFile;
        l_pNewMusic->m_qstrArtistPhotoFile = a_qstrArtistPhotoFile;
        m_CPlayList.append(l_pNewMusic);
        m_blPlaylistChanged = true;
        return true;
    }
    else
    {
        std::cout << "The song is already in playlist." << std::endl;
        return false;
    }
}

bool CPlayList::RemoveMusic(QString a_qstrMusicTitle, QString a_qstrArtist)
{
    int l_iMusicIdx = this->MusicInList(a_qstrMusicTitle, a_qstrArtist);
    return this->RemoveMusic(l_iMusicIdx);
}

bool CPlayList::RemoveMusic(int a_iMusicIdx)
{
    if(-1 != a_iMusicIdx)
    {
        SMusic* l_pDelMusic = m_CPlayList.at(a_iMusicIdx);
        m_CPlayList.removeAt(a_iMusicIdx);
        delete l_pDelMusic;

        m_blPlaylistChanged = true;

        return true;
    }
    else
    {
        return false;
    }
}

int CPlayList::MusicInList(QString a_qstrMusicTitle, QString a_qstrArtist)
{
    int l_iMusicIdx = -1;
    for(int i=0; i<m_CPlayList.length(); i++)
    {
        if(m_CPlayList[i]->m_qstrMusicTitle == a_qstrMusicTitle\
                && m_CPlayList[i]->m_qstrArtist == a_qstrArtist)
        {
            l_iMusicIdx = i;
            break;
        }
    }
    return l_iMusicIdx;
}

void CPlayList::SavePlayList(QString a_qstrFileName)
{
    QFile l_CFile(a_qstrFileName);
    if(!l_CFile.open(QIODevice::WriteOnly))
    {
        std::cout << "Cannot open file." << std::endl;
        return;
    }
    QDataStream l_COut(&l_CFile);
    l_COut << m_CPlayList.length();
    for(int i=0; i<m_CPlayList.length(); i++)
    {
        l_COut << m_CPlayList[i]->m_qstrMusicTitle\
               << m_CPlayList[i]->m_qstrArtist\
               << m_CPlayList[i]->m_qstrMusicFile\
               << m_CPlayList[i]->m_qstrCoverImgFile\
               << m_CPlayList[i]->m_qstrArtistPhotoFile;
    }

    l_CFile.close();

    m_blPlaylistChanged = false;
}

void CPlayList::LoadPlayList(QString a_qstrFileName)
{
    QFile l_CFile(a_qstrFileName);
    if(!l_CFile.open(QIODevice::ReadOnly))
    {
        std::cout << "Cannot open file." << std::endl;
        return;
    }

    this->ClearPlayList();

    QDataStream l_CIn(&l_CFile);
    int l_iPlayListLen;
    l_CIn >> l_iPlayListLen;
    for(int i=0; i<l_iPlayListLen; i++)
    {
        SMusic* l_pNewMusic = new SMusic;
        l_CIn >> l_pNewMusic->m_qstrMusicTitle\
              >> l_pNewMusic->m_qstrArtist\
              >> l_pNewMusic->m_qstrMusicFile\
              >> l_pNewMusic->m_qstrCoverImgFile\
              >> l_pNewMusic->m_qstrArtistPhotoFile;
        m_CPlayList.append(l_pNewMusic);
    }

    l_CFile.close();

    m_blPlaylistChanged = false;
}
