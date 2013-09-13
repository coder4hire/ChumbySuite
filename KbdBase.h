#ifndef KBDBASE_H
#define KBDBASE_H

#include <QDialog>
#include <QLineEdit>

class  CKbdBase : public QDialog
{
    Q_OBJECT
public:
    explicit CKbdBase(QWidget *parent = 0);
    virtual ~CKbdBase();
    void ShowKbd(QLineEdit* pCallerEdit,QWidget* parent=0);
    void CloseKbdDelayed();
    void CancelDelayedClosing();
    QLineEdit* GetAssociatedEdit(){return pCallerEdit;}

protected:
    QLineEdit* pCallerEdit;
    int closeTimer;
    void timerEvent(QTimerEvent *ev);
    void closeEvent(QCloseEvent *);

signals:

public slots:

};

#endif // KBDBASE_H
