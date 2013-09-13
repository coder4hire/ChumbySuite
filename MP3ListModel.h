#ifndef MP3LISTMODEL_H
#define MP3LISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QFile>

class CMP3ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CMP3ListModel(QObject *parent = 0);
    ~CMP3ListModel();
    int rowCount(const QModelIndex &index) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

signals:

public slots:

protected:
    QStringList list;
    QFile pipeFromBtplay;
    QFile pipeToBtplay;

    bool SendCmd(char* cmd);
    unsigned int cmdNum;
};

#endif // MP3LISTMODEL_H
