#include "VolumeControlDlg.h"
#include "ui_VolumeControlDlg.h"
#include <QProcess>
#include <QDesktopWidget>
#include "HardwareLayer.h"

CVolumeControlDlg::CVolumeControlDlg(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint),
    ui(new Ui::CVolumeControlDlg)
{
    ui->setupUi(this);
    timerID=0;
    volume=192;
    move((QApplication::desktop()->width()-this->width())/2,
        (QApplication::desktop()->height()-this->height())/2);
}

CVolumeControlDlg::~CVolumeControlDlg()
{
    if(timerID)
    {
        killTimer(timerID);
    }

    delete ui;
}

bool CVolumeControlDlg::AdjustVolume(int delta)
{
    volume+=delta;
    if(volume<128)
    {
        volume=128;
    }

    if(volume>255)
    {
        volume=255;
    }

    ui->progressVolume->setValue(volume-128);

    //-F- Showing dialog
    show();
    if(timerID)
    {
        killTimer(timerID);
    }
    timerID=startTimer(1000);

    //-F- Sending message to amixer
    CHardwareLayer::GetInstance()->SetVolume(volume);
    return true;
}

void CVolumeControlDlg::timerEvent(QTimerEvent *)
{
    hide();
    killTimer(timerID);
}
