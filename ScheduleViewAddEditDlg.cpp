#include "ScheduleViewAddEditDlg.h"
#include "ui_ScheduleViewAddEditDlg.h"

CScheduleViewAddEditDlg::CScheduleViewAddEditDlg(CScheduleItem& item, QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::CScheduleViewAddEditDlg),
    editingItem(item)
{
    ui->setupUi(this);
    ui->edtHours->IsNumeric=true;
    ui->edtMinutes->IsNumeric=true;

    ui->cmbType->setCurrentIndex((int)editingItem.Type);
    ui->edtDescription->setText(item.Description);
    ui->edtHours->setText(item.Time.toString("hh"));
    ui->edtMinutes->setText(item.Time.toString("mm"));
    ui->chMo->setChecked(item.WeekDays &1);
    ui->chTu->setChecked(item.WeekDays &2);
    ui->chWe->setChecked(item.WeekDays &4);
    ui->chTh->setChecked(item.WeekDays &8);
    ui->chFr->setChecked(item.WeekDays &16);
    ui->chSa->setChecked(item.WeekDays &32);
    ui->chSu->setChecked(item.WeekDays &64);

    ui->chkShowMsg->setChecked(item.ShouldShowMessage);

    ui->edtHours->IsAutoDeleteEnabled=true;
    ui->edtMinutes->IsAutoDeleteEnabled=true;
}

CScheduleViewAddEditDlg::~CScheduleViewAddEditDlg()
{
    delete ui;
}

void CScheduleViewAddEditDlg::on_buttonBox_accepted()
{
    editingItem.Type = (CScheduleItem::EItemType)ui->cmbType->currentIndex();
    editingItem.Description = ui->edtDescription->text();
    editingItem.Time.setHMS(ui->edtHours->text().toInt(),ui->edtMinutes->text().toInt(),0);
    editingItem.WeekDays =
            (ui->chMo->isChecked() ? 1 : 0) |
            (ui->chTu->isChecked() ? 2 : 0) |
            (ui->chWe->isChecked() ? 4 : 0) |
            (ui->chTh->isChecked() ? 8 : 0) |
            (ui->chFr->isChecked() ? 16 : 0) |
            (ui->chSa->isChecked() ? 32 : 0) |
            (ui->chSu->isChecked() ? 64 : 0);
    editingItem.ShouldShowMessage=ui->chkShowMsg->isChecked();
}

void CScheduleViewAddEditDlg::on_btnSelectAll_clicked()
{
    ui->chMo->setChecked(true);
    ui->chTu->setChecked(true);
    ui->chWe->setChecked(true);
    ui->chTh->setChecked(true);
    ui->chFr->setChecked(true);
    ui->chSa->setChecked(true);
    ui->chSu->setChecked(true);
}

void CScheduleViewAddEditDlg::on_btnSelectNone_clicked()
{
    ui->chMo->setChecked(false);
    ui->chTu->setChecked(false);
    ui->chWe->setChecked(false);
    ui->chTh->setChecked(false);
    ui->chFr->setChecked(false);
    ui->chSa->setChecked(false);
    ui->chSu->setChecked(false);
}

void CScheduleViewAddEditDlg::on_cmbType_currentIndexChanged(int index)
{
    if(index==CScheduleItem::SILENT_MESSAGE)
    {
        ui->chkShowMsg->setChecked(true);
        ui->chkShowMsg->setEnabled(false);
    }
    else
    {
        ui->chkShowMsg->setEnabled(true);
    }
}
