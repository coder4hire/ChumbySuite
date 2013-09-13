#ifndef MP3PLAYERCORE_H
#define MP3PLAYERCORE_H

#include "QStringList"
#include <QString>
#include <QAbstractListModel>
#include "BTPlayDrv.h"


class CMP3PlayerCore: public QAbstractListModel
{
public:
    enum EPlayoutStatus
    {
        STOPPED=0,
        PLAYING,
        PAUSED
    };

    Q_OBJECT
public:
    explicit CMP3PlayerCore(QObject *parent = 0);
    ~CMP3PlayerCore();

    bool Play(int idx);
    bool ContinuePlayout();
    bool Stop();
    bool Pause();
    bool Next();
    bool Prev();

    bool AddFile(QString fileName);
    bool RemoveFile(int listIndex);
    bool ClearPlaylist();
    QString GetCurrentSong();
    void SetShuffle(bool isShuffle);
    QModelIndex GetCurrentIndex(){return orderList ? createIndex(orderList[currentSongIndex],0) : QModelIndex();}

    int rowCount(const QModelIndex &index=QModelIndex()) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRow(int row,const QModelIndex &parent=QModelIndex());
    bool removeRow(int row,const QModelIndex &parent=QModelIndex());

    EPlayoutStatus GetStatus(){return status;}

protected slots:
    void OnSongFinished();

signals:
    void OnSongChanged(QModelIndex newIndex);
    void OnListChanged(QStringList& playlist);

protected:
    QStringList list;
    int* orderList;
    EPlayoutStatus status;
    CBTPlayDrv btPlayer;
    bool isShuffle;

    int currentSongIndex;

    void UpdateOrder();
};

#endif // MP3PLAYERCORE_H
