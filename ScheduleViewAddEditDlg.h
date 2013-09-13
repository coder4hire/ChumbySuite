#ifndef SCHEDULEVIEWADDEDITDLG_H
#define SCHEDULEVIEWADDEDITDLG_H

#include <QDialog>
#include "ScheduleView.h"

namespace Ui {
    class CScheduleViewAddEditDlg;
}

class CScheduleViewAddEditDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CScheduleViewAddEditDlg(CScheduleItem& item,QWidget *parent = 0);
    ~CScheduleViewAddEditDlg();

private slots:
    void on_btnSelectNone_clicked();
    void on_btnSelectAll_clicked();
    void on_buttonBox_accepted();

    void on_cmbType_currentIndexChanged(int index);

private:
    Ui::CScheduleViewAddEditDlg *ui;
    CScheduleItem& editingItem;
};

#endif // SCHEDULEVIEWADDEDITDLG_H
