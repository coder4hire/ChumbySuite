#ifndef VOLUMECONTROLDLG_H
#define VOLUMECONTROLDLG_H

#include <QDialog>

namespace Ui {
    class CVolumeControlDlg;
}

class CVolumeControlDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CVolumeControlDlg(QWidget *parent = 0);
    ~CVolumeControlDlg();

    bool AdjustVolume(int delta);

private:
    Ui::CVolumeControlDlg *ui;

protected:
    int timerID;
    int volume;

    void timerEvent(QTimerEvent *);
};

#endif // VOLUMECONTROLDLG_H
