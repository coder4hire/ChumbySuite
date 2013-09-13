#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QListWidget>
#include <QTime>
#include <QTextStream>

class QSettings;

class CScheduleItem
{
public:
    enum EItemType
    {
        DISABLED=0,
        RING,
        MUSIC,
        RADIO,
        SILENT_MESSAGE
    };

    CScheduleItem();
    CScheduleItem(EItemType type, QTime time, const QString& description, int weekDays);
    CScheduleItem(QString srcString);

    QString Serialize();
    bool IsFireTime(const QDateTime& dt) const;

    bool IsEmpty()
    {
        return WeekDays<0;
    }


    EItemType Type;
    QString Description;
    QTime Time;
    int WeekDays;
    bool ShouldShowMessage;

    bool IsFired;
    int SuspendCountdown;

    static CScheduleItem Empty;
};

Q_DECLARE_METATYPE(CScheduleItem)

class CScheduleView : public QListWidget
{
    Q_OBJECT

public:
    enum EScheduleRoles
    {
        ScheduleItemRole = Qt::UserRole
    };

public:
    explicit CScheduleView(QWidget *parent = 0);
    void addItem(const CScheduleItem& item);
    CScheduleItem GetScheduleItem(int row);
    bool SetScheduleItem(int row,const CScheduleItem& item);
    bool SetScheduleItem(QListWidgetItem* pRow ,const CScheduleItem& item);
    bool SaveList(QSettings* pSettings,const char* prefix);
    bool LoadList(QSettings* pSettings,const char* prefix);
    ~CScheduleView();

signals:

public slots:

};

#endif // SCHEDULEVIEW_H
