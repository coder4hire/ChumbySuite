#include "ScheduleView.h"
#include "ScheduleListDelegate.h"
#include "QAbstractItemDelegate"
#include "QTime"
#include "QSettings"

CScheduleItem CScheduleItem::Empty(CScheduleItem::DISABLED,QTime(0,0,0),"",-1);

CScheduleItem::CScheduleItem()
{
    Type = DISABLED;
    Time.setHMS(0,0,0);
    WeekDays=0;
    IsFired=false;
    ShouldShowMessage=true;
    SuspendCountdown=0;
}

CScheduleItem::CScheduleItem(EItemType type, QTime time, const QString& description, int weekDays)
{
    Type = type;
    Time = time;
    Description = description;
    WeekDays = weekDays;
    IsFired=false;
    SuspendCountdown=0;
}

CScheduleItem::CScheduleItem(QString srcString)
{
    QStringList list = srcString.split('\x01');
    if(list.count()==5)
    {
        Type = (EItemType)list[0].toInt();
        Time= QTime::fromString(list[1],"hh:mm:ss");
        Description = list[2];
        WeekDays = list[3].toInt();
        ShouldShowMessage= (Type==SILENT_MESSAGE) ? true : (bool)list[4].toInt();
    }
    IsFired=false;
    SuspendCountdown=0;
}

QString CScheduleItem::Serialize()
{
    QString retVal;
    retVal.sprintf("%d\x01%s\x01%s\x01%d\x01%d",
        Type,Time.toString("hh:mm:ss").toLatin1().data(),Description.toLatin1().data(),WeekDays,(int)ShouldShowMessage);
    return retVal;
}

bool CScheduleItem::IsFireTime(const QDateTime& dt) const
{
    if((1<<(dt.date().dayOfWeek()-1)) & WeekDays)
    {
        return dt.time().minute()==Time.minute() && dt.time().hour()==Time.hour();
    }
    return false;
}


CScheduleView::CScheduleView(QWidget *parent) :
    QListWidget(parent)
{
    QAbstractItemDelegate* delegate = itemDelegate();
    this->setItemDelegate(new CScheduleListDelegate());
    delete delegate;
}

CScheduleView::~CScheduleView()
{
    delete itemDelegate();
}

void CScheduleView::addItem(const CScheduleItem& schedItem)
{
    QListWidgetItem* pItem = new QListWidgetItem(schedItem.Time.toString("HH:mm:ss"),this);

    if(pItem)
    {
        SetScheduleItem(pItem,schedItem);

//        QFontMetrics fm(font());
//        pItem->setSizeHint(QSize(sizeHint().width(),fm.height()*2.2));
    }
}

CScheduleItem CScheduleView::GetScheduleItem(int row)
{
    QListWidgetItem* pItem = item(row);

    if(pItem)
    {
        return pItem->data(ScheduleItemRole).value<CScheduleItem>();
    }
    else
    {
        return CScheduleItem::Empty;
    }
}

bool CScheduleView::SetScheduleItem(int row,const CScheduleItem& item)
{
    QListWidgetItem* pItem = this->item(row);
    return SetScheduleItem(pItem,item);
}

bool CScheduleView::SetScheduleItem(QListWidgetItem* pRow ,const CScheduleItem& item)
{
    if(pRow)
    {
        QVariant var;
        var.setValue(item);
        pRow->setData(CScheduleView::ScheduleItemRole,var);
        return true;
    }
    return false;
}

bool CScheduleView::SaveList(QSettings* pSettings,const char* prefix)
{
    pSettings->remove(prefix);
    pSettings->setValue(QString(prefix)+"/count",count());
    QString name;
    for(int i=0;i<count();i++)
    {
        name.sprintf("%s/Item%d",prefix,i);
        pSettings->setValue(name,
                            item(i)->data(ScheduleItemRole).value<CScheduleItem>().Serialize());
    }
    return true;
}

bool CScheduleView::LoadList(QSettings* pSettings,const char* prefix)
{
    int newCount= pSettings->value(QString(prefix)+"/count").toInt();
    QString name;
    clear();
    for(int i=0;i<newCount;i++)
    {
        name.sprintf("%s/Item%d",prefix,i);
        CScheduleItem item(pSettings->value(name).toString());
        item.IsFired=false;
        item.SuspendCountdown=0;
        addItem(item);
    }
    return true;
}
