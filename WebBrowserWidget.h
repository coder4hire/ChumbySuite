#ifndef WEBBROWSERWIDGET_H
#define WEBBROWSERWIDGET_H

#include <QWidget>
#include"cwidgetbase.h"

namespace Ui {
    class CWebBrowserWidget;
}

class CWebBrowserWidget : public CWidgetBase
{
    Q_OBJECT

public:
    explicit CWebBrowserWidget(QWidget *parent = 0);
    ~CWebBrowserWidget();

private:
    Ui::CWebBrowserWidget *ui;

private slots:
    void on_btnClose_clicked();
    void on_btnGo_clicked();
};

#endif // WEBBROWSERWIDGET_H
