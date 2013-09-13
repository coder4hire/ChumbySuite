#ifndef ALARMCLOCKWIDGET_H
#define ALARMCLOCKWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QListWidgetItem>
#include "AlarmMessageDlg.h"
#include "cwidgetbase.h"

namespace Ui {
    class CAlarmClockWidget;
}

class CMP3Widget;
class CScheduleItem;

class CAlarmClockWidget : public CWidgetBase
{
    Q_OBJECT

public:
    explicit CAlarmClockWidget(QWidget *parent = 0);
    ~CAlarmClockWidget();

protected:
    virtual void Initialize(CWidgetSelector *pSelector, QSettings *pSettings);
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    bool isModified;
    int timerID;
    void timerEvent(QTimerEvent *);
    void ProcessAlarmEvent(const CScheduleItem& item);
    void ProcessClearEvent(const CScheduleItem& item);
    virtual bool OnButtonUp(bool isLongClick);

    CMP3Widget * pMP3Player;
    CAlarmMessageDlg msgDlg;
    int suspendMinutes;

private slots:
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_scheduleList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *);
    void on_scheduleList_itemSelectionChanged();

private:
    Ui::CAlarmClockWidget *ui;
};

#endif // ALARMCLOCKWIDGET_H
