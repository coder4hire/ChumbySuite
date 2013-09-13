#include "AlarmMessageDlg.h"
#include "ui_AlarmMessageDlg.h"
#include <QDesktopWidget>

CAlarmMessageDlg::CAlarmMessageDlg(QWidget *parent) :
   QDialog(parent,Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint),
    ui(new Ui::CAlarmMessageDlg)
{
    ui->setupUi(this);
    move((QApplication::desktop()->width()-this->width())/2,
        (QApplication::desktop()->height()-this->height())/2);
}

CAlarmMessageDlg::~CAlarmMessageDlg()
{
    delete ui;
}

void CAlarmMessageDlg::ShowMessage(const QString& msg)
{
    ui->lblText->setText(msg);
    showNormal();
}
