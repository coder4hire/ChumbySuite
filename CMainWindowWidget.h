#ifndef CMAINWINDOWWIDGET_H
#define CMAINWINDOWWIDGET_H

#include <cwidgetbase.h>

namespace Ui {
    class CMainWindowWidget;
}

class CMainWindowWidget : public CWidgetBase
{
    Q_OBJECT

public:
    explicit CMainWindowWidget(QWidget *parent=0);
    virtual ~CMainWindowWidget();
    virtual void Initialize(CWidgetSelector *pSelector, QSettings *pSettings);
    virtual void OnSettingsChanged();

protected:
    void timerEvent(QTimerEvent * event);
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    int slideShowTimer;

    QPixmap backPixmap;
    void LoadAndResizePixmap(QString fileName);
    void StartStopSlideShow();
    QString slideFileName;

private:
    Ui::CMainWindowWidget *ui;

private slots:
    void on_btnWidgetSelect_clicked();
};

#endif // CMAINWINDOWWIDGET_H
