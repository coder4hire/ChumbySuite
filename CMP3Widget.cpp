#include "CMP3Widget.h"
#include "ui_CMP3Widget.h"
#include <QFileDialog>

CMP3Widget::CMP3Widget(QWidget *parent):
    CWidgetBase(parent),
    ui(new Ui::CMP3Widget)
{
    setObjectName("MP3 Player");

    ui->setupUi(this);
    ui->listView->setModel(&playerCore);

    ui->btnStop->hide();

    connect(&playerCore,SIGNAL(OnSongChanged(QModelIndex)),SLOT(OnSongChanged(QModelIndex)));
}

CMP3Widget::~CMP3Widget()
{
    delete ui;
}

void CMP3Widget::on_btnDel_clicked()
{
    playerCore.removeRow(ui->listView->currentIndex().row());
}

void CMP3Widget::on_btnClr_clicked()
{
    playerCore.ClearPlaylist();
}

void CMP3Widget::on_btnAdd_clicked()
{
    QFileDialog dlg(
            this,
            tr("Open Document"),
            tr("/mnt/usb"),
            tr("MP3 files(*.mp3);;All files (*.*)"));

    QString strFileName;
    dlg.resize(320,220);
    dlg.exec();
    if(dlg.selectedFiles().size()>0)
    {
        playerCore.AddFile(dlg.selectedFiles().at(0));
    }
}

void CMP3Widget::on_btnPlay_clicked()
{
    if(playerCore.GetStatus()==CMP3PlayerCore::PAUSED)
    {
        playerCore.ContinuePlayout();
    }
    else
    {
        playerCore.Play(ui->listView->currentIndex().row());
    }
    ui->btnStop->show();
    ui->btnPlay->hide();
}

void CMP3Widget::on_btnPause_pressed()
{
    if(playerCore.GetStatus()==CMP3PlayerCore::PLAYING)
    {
        playerCore.Pause();
    }
    else if(playerCore.GetStatus()==CMP3PlayerCore::PAUSED)
    {
        playerCore.ContinuePlayout();
    }
}

void CMP3Widget::on_btnStop_clicked()
{
    playerCore.Stop();
    ui->btnStop->hide();
    ui->btnPlay->show();
}

void CMP3Widget::on_btnNext_clicked()
{
    playerCore.Next();
}

void CMP3Widget::on_btnPrev_clicked()
{
    playerCore.Prev();
}

void CMP3Widget::on_btnShuffle_clicked()
{
    playerCore.SetShuffle(ui->btnShuffle->isChecked());
}


void CMP3Widget::OnSongChanged(QModelIndex index)
{
    ui->listView->setCurrentIndex(index);
}

void CMP3Widget::StartAlarmPlayout()
{
    playerCore.Play(0);
}

void CMP3Widget::StopPlayout()
{
    playerCore.Stop();
}
