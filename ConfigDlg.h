#ifndef CONFIGDLG_H
#define CONFIGDLG_H

#include <QDialog>

#define STATIC_PAGES_NUM 3

namespace Ui {
    class CConfigDlg;
}

class CWidgetSelector;
class QAbstractButton;

class CConfigDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CConfigDlg(CWidgetSelector* pSelector,QWidget *parent = 0);
    ~CConfigDlg();

private:
    Ui::CConfigDlg *ui;

protected:
    CWidgetSelector* pSelector;
    void showEvent(QShowEvent *);
    bool SaveGeneralData();
    bool LoadGeneralData();
    QString ReadConfigAttribute(const QString& configString,QString name);
    void SetNetworkSettings();

private slots:
    void on_chkDHCP_clicked();
    void on_buttonBox_accepted();
    void on_chkUseNTP_clicked(bool checked);
};

#endif // CONFIGDLG_H
