#include "MP3PlayerCore.h"
#include <QSize>
#include <QFileInfo>
#include <stdlib.h>
#include "Log.h"

CMP3PlayerCore::CMP3PlayerCore(QObject *parent):
    QAbstractListModel(parent)
{
    status=STOPPED;
    orderList=NULL;
    isShuffle=false;
    connect(&btPlayer,SIGNAL(OnSongFinished()),SLOT(OnSongFinished()));
}

CMP3PlayerCore::~CMP3PlayerCore()
{
    delete[] orderList;
}

bool CMP3PlayerCore::Play(int idx)
{
//    if(idx.isValid())
//    {
        //-F- Resetting playlist
        //btPlayer.SendCmd("resetplaylist");

        currentSongIndex=idx;
        QString cmd="playnow * ";
        cmd+=GetCurrentSong();
        if(btPlayer.SendCmd(cmd.toLatin1().data()))
        {
            status=PLAYING;
        }
//    }
//    else
//    {
//        if(btPlayer.SendCmd("play"))
//        {
//            status=PLAYING;
//        }
//    }

    return false;
}

bool CMP3PlayerCore::ContinuePlayout()
{
    if(btPlayer.SendCmd("play"))
    {
        status=PLAYING;
    }
}

bool CMP3PlayerCore::Stop()
{
    btPlayer.SendCmd("stop");
    status=STOPPED;
    return false;
}

bool CMP3PlayerCore::Pause()
{
    btPlayer.SendCmd("pause");
    status=PAUSED;
    return false;
}

bool CMP3PlayerCore::Next()
{
    if(currentSongIndex<list.count()-1)
    {
        currentSongIndex++;

        if(status==PLAYING)
        {
            Play(currentSongIndex);
        }
        emit OnSongChanged(createIndex(currentSongIndex,0));

        return true;
    }
    return false;
}

bool CMP3PlayerCore::Prev()
{
    if(currentSongIndex>0)
    {
        currentSongIndex--;

        if(status==PLAYING)
        {
            Play(currentSongIndex);
        }
        emit OnSongChanged(createIndex(currentSongIndex,0));

        return true;
    }
    return false;
}

bool CMP3PlayerCore::AddFile(QString fileName)
{
    int i = rowCount();
    if(insertRow(i))
    {
        setData(index(i),fileName,Qt::UserRole);
    }

    return false;
}

bool CMP3PlayerCore::ClearPlaylist()
{
    list.clear();
    this->layoutChanged();

    return false;
}


QString CMP3PlayerCore::GetCurrentSong()
{
    return orderList ? data(createIndex(orderList[currentSongIndex],0),Qt::UserRole).toString() : "";
}

int CMP3PlayerCore::rowCount(const QModelIndex &) const
{
    return list.count();
}

int CMP3PlayerCore::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant CMP3PlayerCore::data(const QModelIndex &index, int role) const
{
    if(index.row()<list.count() && index.row()>=0)
    {
        switch(role)
        {
        case (Qt::SizeHintRole):
            return QSize(-1,18);
            break;
        case (Qt::DisplayRole):
            return QFileInfo(list[index.row()]).fileName();
        case (Qt::UserRole):
            return list[index.row()];
        default:
            break;
        }
    }
    return 0;
}

bool CMP3PlayerCore::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    if(row<list.count() && role==Qt::UserRole)
    {
        list[row]=value.toString();
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

bool CMP3PlayerCore::insertRow(int row, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row);
    list.insert(row,"");
    endInsertRows();
    UpdateOrder();
    return true;
}

bool CMP3PlayerCore::removeRow(int row, const QModelIndex &parent)
{
    if(row<=list.count())
    {
        beginRemoveRows(parent,row,row);
        list.removeAt(row);
        endRemoveRows();
        UpdateOrder();
        return true;
    }
    return false;
}

void CMP3PlayerCore::OnSongFinished()
{
    if(status==PLAYING)
    {
        if(!Next())
        {
            Stop();
        }
    }
}

void CMP3PlayerCore::SetShuffle(bool isShuffle)
{
    this->isShuffle=isShuffle;
}

void CMP3PlayerCore::UpdateOrder()
{
    int count=list.count();

    delete[] orderList;
    if(count)
    {
        orderList=new int[count];

        for(int i=0;i<count;i++)
        {
            orderList[i]=i;
        }

        if(isShuffle)
        {
            for(int i=0;i<count;i++)
            {
                int randIndex = ((double)rand()*i)/RAND_MAX;
                int m=orderList[i];
                orderList[i]=orderList[randIndex];
                orderList[randIndex]=m;
            }
        }
    }
    else
    {
        orderList=NULL;
    }
}
