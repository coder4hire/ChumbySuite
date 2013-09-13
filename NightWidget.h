#ifndef NIGHTWIDGET_H
#define NIGHTWIDGET_H

#include "cwidgetbase.h"

namespace Ui {
    class CNightWidget;
}

class CNightWidget : public CWidgetBase
{
    Q_OBJECT

public:
    explicit CNightWidget(QWidget *parent = 0);
    ~CNightWidget();
protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void OnSettingsChanged();
private:
    Ui::CNightWidget *ui;
};

#endif // NIGHTWIDGET_H
