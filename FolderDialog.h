#ifndef CFOLDERDIALOG_H
#define CFOLDERDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QAbstractButton>

namespace Ui {
    class CFolderDialog;
}

class CFolderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CFolderDialog(QWidget *parent = 0);
    ~CFolderDialog();
    virtual void showEvent(QShowEvent *);
    QString SelectedPath;    

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CFolderDialog *ui;

    QFileSystemModel *model;
};

#endif // CFOLDERDIALOG_H
