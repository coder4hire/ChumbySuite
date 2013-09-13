#include "ScheduleListDelegate.h"
#include "ScheduleView.h"
#include <QPainter>
#include <QTime>

const char* CScheduleListDelegate::strDays[7]={"Mo","Tu","We","Th","Fr","Sa","Su"};

CScheduleListDelegate::CScheduleListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    images[0].load(":/Resources/EventsIcons/bell-icon.png");
    images[1].load(":/Resources/EventsIcons/music-icon.png");
    images[2].load(":/Resources/EventsIcons/radio-icon.png");
    images[3].load(":/Resources/EventsIcons/notes-icon.png");
}

void CScheduleListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QLinearGradient grad(option.rect.topLeft(),option.rect.bottomLeft());
    grad.setColorAt(0,QColor(0,192,255,16));
    grad.setColorAt(0.5,QColor(0,192,255,192));
    grad.setColorAt(1,QColor(0,192,255,16));
    QBrush brush(grad);

    if(option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect.adjusted(0,0,-1,-1),brush);
    }

    const CScheduleItem& item = index.data(CScheduleView::ScheduleItemRole).value<CScheduleItem>();

    //-F- Drawing Item
    QFont bigFont = painter->font();
    bigFont.setPixelSize(bigFont.pixelSize()*2);
    bigFont.setBold(true);

    int delta = option.rect.height()/2.2;

    QString strWeekDays;
    if((item.WeekDays&0x7F)==0x7F)
    {
        strWeekDays="Every Day";
    }
    else if((item.WeekDays&0x1F)==0x1F)
    {
        strWeekDays="Every Working Day";
    }
    else
    {
        for(int i=0;i<7;i++)
        {
            strWeekDays+= (item.WeekDays&(1<<i) ? strDays[i] : "");
            strWeekDays+= " ";
        }
    }

    painter->drawText(option.rect.left()+130,option.rect.top()+(int)(delta*0.9),strWeekDays);
    painter->drawText(option.rect.left()+130,option.rect.top()+(int)(delta*1.9),item.Description);

    painter->setFont(bigFont);
    QRect rect= option.rect;
    rect.setRight(130);
    rect.setLeft(40);
    painter->drawText(rect,Qt::AlignVCenter | Qt::AlignLeft ,item.Time.toString("HH:mm"));

    //-F- Painting Icon
    if(item.Type>CScheduleItem::DISABLED)
    {
        painter->drawImage(5,(rect.height()-images[(int)item.Type-1].height())/2+rect.top(),images[(int)item.Type-1]);
    }

    painter->restore();
}
