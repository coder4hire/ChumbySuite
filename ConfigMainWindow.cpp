#include "ConfigMainWindow.h"
#include "ui_ConfigMainWindow.h"
#include <QMessageBox>

#include "FolderDialog.h"

CConfigMainWindow::CConfigMainWindow(QWidget *parent):
    CConfigWidgetBase(parent),
    ui(new Ui::CConfigMainWindow)
{
    ui->setupUi(this);
}

CConfigMainWindow::~CConfigMainWindow()
{
    delete ui;
}

bool CConfigMainWindow::Save(QSettings* pSettings)
{
    pSettings->setValue("MainWnd/SlideShowEnabled",ui->chkSlideShow->isChecked());
    pSettings->setValue("MainWnd/PicturesFolder",ui->editPicturesFolder->text());
    pSettings->setValue("MainWnd/Delay",ui->editDelay->text().toInt());
    pSettings->setValue("MainWnd/Randomize",ui->chkRandom->isChecked());
    pSettings->setValue("MainWnd/WeatherEnabled",ui->chkWeather->isChecked());
    pSettings->setValue("MainWnd/Location",ui->editLocation->text());
    return true;
}

bool CConfigMainWindow::Load(QSettings* pSettings)
{
    ui->chkSlideShow->setChecked(pSettings->value("MainWnd/SlideShowEnabled",false).toBool());
    ui->editPicturesFolder->setText(pSettings->value("MainWnd/PicturesFolder","").toString());
    ui->editDelay->setText(pSettings->value("MainWnd/Delay",20).toString());
    ui->chkRandom->setChecked(pSettings->value("MainWnd/Randomize",false).toBool());
    ui->chkWeather->setChecked(pSettings->value("MainWnd/WeatherEnabled",true).toBool());
    ui->editLocation->setText(pSettings->value("MainWnd/Location","").toString());
    return true;
}

void CConfigMainWindow::on_btnDelayMinus_clicked()
{
    int val = ui->editDelay->text().toInt();
    val--;
    if(val<0)
    {
        val=0;
    }
    ui->editDelay->setText(QString::number(val));
}

void CConfigMainWindow::on_btnDelayPlus_clicked()
{
    int val = ui->editDelay->text().toInt();
    val++;
    if(val>1500)
    {
        val=1500;
    }
    ui->editDelay->setText(QString::number(val));
}

void CConfigMainWindow::on_btnBrowse_clicked()
{
    CFolderDialog dlg;
    dlg.SelectedPath = ui->editPicturesFolder->text();
    if(dlg.exec()==QDialog::Accepted)
    {
        ui->editPicturesFolder->setText(dlg.SelectedPath);
    }
//    QString str = QFileDialog::getExistingDirectory(this);
//    if(str!="")
//    {
//        ui->editPicturesFolder->setText(str);
//    }
}
