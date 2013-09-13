#ifndef CSCHEDULELISTDELEGATE_H
#define CSCHEDULELISTDELEGATE_H

#include <QStyledItemDelegate>

class CScheduleListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

public:
    explicit CScheduleListDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
    static const char* strDays[7];
    QImage images[4];

signals:

public slots:

};

#endif // CSCHEDULELISTDELEGATE_H
