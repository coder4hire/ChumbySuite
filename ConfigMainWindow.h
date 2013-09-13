#ifndef CONFIGMAINWINDOW_H
#define CONFIGMAINWINDOW_H

#include <QWidget>
#include "ConfigWidgetBase.h"

namespace Ui {
    class CConfigMainWindow;
}

class CConfigMainWindow : public CConfigWidgetBase
{
    Q_OBJECT

public:
    explicit CConfigMainWindow(QWidget *parent = 0);
    ~CConfigMainWindow();
    virtual bool Save(QSettings* pSettings);
    virtual bool Load(QSettings* pSettings);

private:
    Ui::CConfigMainWindow *ui;

private slots:
    void on_btnBrowse_clicked();
    void on_btnDelayPlus_clicked();
    void on_btnDelayMinus_clicked();
};

#endif // CONFIGMAINWINDOW_H
