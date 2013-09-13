#include "MP3ListModel.h"
#include <QFileInfo>
#include <QSize>

CMP3ListModel::CMP3ListModel(QObject *parent) :
    QAbstractListModel(parent),
    pipeToBtplay("/tmp/.btplay-cmdin"),
    pipeFromBtplay("/tmp/.btplay-cmdout")
{
    list.append("BBB/AAA_1");
    list.append("BBB/AAA_2");

    if(!pipeToBtplay.open(QIODevice::WriteOnly))
    {
        list.append("Can't connect to btplay");
    }
    else if(!pipeToBtplay.open(QIODevice::ReadOnly))
    {
        pipeToBtplay.close();
        list.append("Can't connect to btplay");
    }

    cmdNum=0;
}

CMP3ListModel::~CMP3ListModel()
{
    pipeToBtplay.close();
    pipeFromBtplay.close();
}

int CMP3ListModel::rowCount(const QModelIndex &index ) const
{
    int i=list.count();
    return i;
}

int CMP3ListModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant CMP3ListModel::data(const QModelIndex &index, int role) const
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

bool CMP3ListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count);
    for(int i=0;i<count;i++)
    {
        list.insert(row,"");
    }
    endInsertRows();
    return true;
}

bool CMP3ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row+count<=list.count())
    {
        beginRemoveRows(parent,row,row+count);
        for(int i=0;i<count;i++)
        {
            list.removeAt(row);
        }
        endRemoveRows();
        return true;
    }
    return false;
}

bool CMP3ListModel::SendCmd(char* cmd)
{
    char cmdbuf[128];
    sprintf(cmdbuf,"[%d]%s",cmdNum++,cmd);
    if(pipeToBtplay.isOpen())
    {
        pipeToBtplay.write(cmdbuf);
        return true;
    }
    return false;
}
