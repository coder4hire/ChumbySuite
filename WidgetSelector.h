#ifndef WIDGETSELECTOR_H
#define WIDGETSELECTOR_H

#include <QDialog>
#include <QLabel>
#include <QSettings>
#include "cwidgetbase.h"
#include "Fader.h"
#include "QTime"
#include "VolumeControlDlg.h"

namespace Ui {
    class CWidgetSelector;
}

class CWidgetSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CWidgetSelector(QWidget *parent = 0);
    ~CWidgetSelector();

    bool ShowThisWidget(const QString& name);
    bool ShowThisWidget(int index);

    int GetCount();
    QString GetCurrentWidgetName();
    CWidgetBase* GetWidget(int i);
    CWidgetBase* GetWidget(QString name);
    void LoadWidgets();
    void ShowSelectionScreen();
    QSettings* GetSettings(){return &settings;}

protected:
    void CleanUpWidgetsAndButtons();
    QSettings settings;

    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void keyReleaseEvent(QKeyEvent *ev);

    QTime lastKeyPressTime;
    QTime lastKeyReleaseTime;

    CVolumeControlDlg volumeCtrl;

public slots:
    void processRotary(int speed, bool isButtonPressed);
    void processButtonPress();
    void processButtonRelease();

private:
    Ui::CWidgetSelector *ui;

private slots:
    void on_btnSettings_clicked();
};

class QWidgetPushButton : public QLabel
{
    Q_OBJECT

public:
    QWidgetPushButton(QWidget* parent=0):QLabel(parent)
    {
    }

    int Index;
    CWidgetSelector* pSelector;

    void setIcon(const QString& text)
    {
        //this->text = text;
        icon.load(":/Resources/WidgetsIcons/"+text+".png");
//        icon.load(":/Resources/EventsIcons/bell-icon.png");
        this->setToolTip(text);
        repaint();
    }

    virtual void paintEvent(QPaintEvent *);

protected:
    QImage icon;
    void mousePressEvent(QMouseEvent *ev)
    {
        pSelector->ShowThisWidget(Index);
    }
};

#endif // WIDGETSELECTOR_H
