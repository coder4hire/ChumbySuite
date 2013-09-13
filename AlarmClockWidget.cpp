#include "AlarmClockWidget.h"
#include "ui_AlarmClockWidget.h"
#include "ScheduleViewAddEditDlg.h"
#include "WidgetSelector.h"
#include "QTime"
#include "CMP3Widget.h"

CAlarmClockWidget::CAlarmClockWidget(QWidget *parent) :
    CWidgetBase(parent),
    ui(new Ui::CAlarmClockWidget)
{
    ui->setupUi(this);
    ui->btnDelete->setEnabled(false);
    ui->btnEdit->setEnabled(false);

    ui->scheduleList->setSortingEnabled(true);
    timerID=startTimer(1000);

    isModified=false;

    pMP3Player=NULL;
    suspendMinutes=1;
}

CAlarmClockWidget::~CAlarmClockWidget()
{
    delete ui;
}

void CAlarmClockWidget::on_btnAdd_clicked()
{
    CScheduleItem newItem;
    CScheduleViewAddEditDlg dlg(newItem);
    if(dlg.exec()==QDialog::Accepted)
    {
        ui->scheduleList->addItem(newItem);
        isModified=true;
    }
}

void CAlarmClockWidget::on_btnEdit_clicked()
{
    QModelIndex index = ui->scheduleList->currentIndex();
    if(index.isValid())
    {
        CScheduleItem item = ui->scheduleList->GetScheduleItem(index.row());
        CScheduleViewAddEditDlg dlg(item);
        if(dlg.exec()==QDialog::Accepted)
        {
            ui->scheduleList->SetScheduleItem(index.row(),item);
            this->repaint();
            isModified=true;
        }
    }
}

void CAlarmClockWidget::on_btnDelete_clicked()
{
    QModelIndex index = ui->scheduleList->currentIndex();
    if(index.isValid())
    {
        delete ui->scheduleList->takeItem(index.row());
        isModified=true;
    }
}

void CAlarmClockWidget::on_scheduleList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
    int count = ui->scheduleList->count();
    ui->btnDelete->setEnabled(current!=NULL && count);
    ui->btnEdit->setEnabled(current!=NULL && count);
}

void CAlarmClockWidget::on_scheduleList_itemSelectionChanged()
{
    bool isValid = ui->scheduleList->currentIndex().isValid();
    ui->btnDelete->setEnabled(isValid);
    ui->btnEdit->setEnabled(isValid);
}

void CAlarmClockWidget::Initialize(CWidgetSelector *pSelector, QSettings *pSettings)
{
    CWidgetBase::Initialize(pSelector,pSettings);
    ui->scheduleList->LoadList(pSelector->GetSettings(),"ScheduleList");
}

void CAlarmClockWidget::showEvent(QShowEvent *)
{
    isModified=false;
}

void CAlarmClockWidget::hideEvent(QHideEvent *)
{
    if(isModified)
    {
        ui->scheduleList->SaveList(pSelector->GetSettings(),"ScheduleList");
    }
}

void CAlarmClockWidget::timerEvent(QTimerEvent *)
{
    const QDateTime dateTime=QDateTime::currentDateTime();

    for(int i=0;i<ui->scheduleList->count();i++)
    {
        const CScheduleItem& item=ui->scheduleList->GetScheduleItem(i);

        if(item.SuspendCountdown>0)
        {
            CScheduleItem newItem = item;
            newItem.SuspendCountdown--;
            if(newItem.SuspendCountdown<=0)
            {
                newItem.SuspendCountdown=0;
                newItem.IsFired=true;
                ProcessAlarmEvent(item);
            }

            ui->scheduleList->SetScheduleItem(i,newItem);
        }

        if(item.IsFireTime(dateTime) && !item.IsFired)
        {
            ProcessAlarmEvent(item);

            //-F- Marking item as fired
            CScheduleItem newItem = item;
            newItem.IsFired=true;

            ui->scheduleList->SetScheduleItem(i,newItem);
        }
    }
    killTimer(timerID);
    timerID=startTimer((60-QTime::currentTime().second())*1000);
}

void CAlarmClockWidget::ProcessAlarmEvent(const CScheduleItem& item)
{
    // If we're in Night mode, go to Main Page
    QString str = pSelector->GetCurrentWidgetName();
    if(pSelector->GetCurrentWidgetName()=="CNightWidget")
    {
        pSelector->ShowThisWidget("Main Screen");
    }

    // Showing message
    if(item.ShouldShowMessage)
    {
        msgDlg.ShowMessage(item.Description);
    }

    switch(item.Type)
    {
    case CScheduleItem::MUSIC:
        if(!pMP3Player)
        {
            pMP3Player=(CMP3Widget*)pSelector->GetWidget("MP3 Player");
        }
        pMP3Player->StartAlarmPlayout();
        break;
    case CScheduleItem::RING:
        break;
    case CScheduleItem::RADIO:
        break;
    case CScheduleItem::SILENT_MESSAGE:
        break;
    }

}

bool CAlarmClockWidget::OnButtonUp(bool isLongClick)
{
    for(int i=0;i<ui->scheduleList->count();i++)
    {
        const CScheduleItem& item=ui->scheduleList->GetScheduleItem(i);
        if(item.IsFired || (isLongClick && item.SuspendCountdown>0))
        {
            //-F- Marking item as not fired
            CScheduleItem newItem = item;
            if(isLongClick)
            {
                newItem.SuspendCountdown=0;
            }
            else
            {
                if(item.SuspendCountdown<=0)
                {
                    newItem.SuspendCountdown=suspendMinutes;
                }
            }

            newItem.IsFired=false;
            ui->scheduleList->SetScheduleItem(i,newItem);

            ProcessClearEvent(newItem);
        }
    }
    msgDlg.close();
    return false;
}

void CAlarmClockWidget::ProcessClearEvent(const CScheduleItem& item)
{
    switch(item.Type)
    {
    case CScheduleItem::MUSIC:
        if(pMP3Player)
        {
            pMP3Player->StopPlayout();
        }
        break;
    case CScheduleItem::RING:
        break;
    case CScheduleItem::RADIO:
        break;
    case CScheduleItem::SILENT_MESSAGE:
        break;
    }
}
