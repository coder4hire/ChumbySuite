#ifndef RADIOWIDGET_H
#define RADIOWIDGET_H

#include <cwidgetbase.h>
#include <QWidget>

namespace Ui {
    class CRadioWidget;
}

class CRadioWidget : public CWidgetBase
{
    Q_OBJECT

public:
    explicit CRadioWidget(QWidget *parent = 0);
    ~CRadioWidget();

private:
    Ui::CRadioWidget *ui;
};

#endif // RADIOWIDGET_H
