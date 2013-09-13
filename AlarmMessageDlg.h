#ifndef ALARMMESSAGEDLG_H
#define ALARMMESSAGEDLG_H

#include <QDialog>

namespace Ui {
    class CAlarmMessageDlg;
}

class CAlarmMessageDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAlarmMessageDlg(QWidget *parent = 0);
    ~CAlarmMessageDlg();

    void ShowMessage(const QString& msg);
private:
    Ui::CAlarmMessageDlg *ui;
};

#endif // ALARMMESSAGEDLG_H
