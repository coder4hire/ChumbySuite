#ifndef CMP3WIDGET_H
#define CMP3WIDGET_H

#include <cwidgetbase.h>
#include "MP3PlayerCore.h"

namespace Ui {
    class CMP3Widget;
}

class CMP3Widget : public CWidgetBase
{
    Q_OBJECT

public:
    explicit CMP3Widget(QWidget *parent=0);
    virtual ~CMP3Widget();

    void StartAlarmPlayout();
    void StopPlayout();

private slots:
    void on_btnPlay_clicked();
    void on_btnAdd_clicked();
    void on_btnDel_clicked();

    void on_btnClr_clicked();

    void on_btnShuffle_clicked();

    void on_btnNext_clicked();

    void on_btnPrev_clicked();

    void OnSongChanged(QModelIndex newIndex);

    void on_btnPause_pressed();

    void on_btnStop_clicked();

private:
    Ui::CMP3Widget *ui;
    CMP3PlayerCore playerCore;
};

#endif // CMP3WIDGET_H
