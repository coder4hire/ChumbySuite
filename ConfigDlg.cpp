#include "ConfigDlg.h"
#include "ui_ConfigDlg.h"
#include "WidgetSelector.h"
#include "ConfigWidgetBase.h"
#include "NetworkTools.h"

#include "QAbstractButton"
#include "QTextStream"
#include "QFile"

CConfigDlg::CConfigDlg(CWidgetSelector* pSelector,QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::CConfigDlg)
{
    this->pSelector = pSelector;
    ui->setupUi(this);
    for(int i=0;i<pSelector->GetCount();i++)
    {
        CConfigWidgetBase* pConfigWidget = pSelector->GetWidget(i)->GetConfigWidget();
        if(pConfigWidget)
        {
            ui->tabWidget->addTab(pConfigWidget,pSelector->GetWidget(i)->objectName());
        }
    }

    ui->editIP->IsNumeric=true;
    ui->editMask->IsNumeric=true;
    ui->editGate->IsNumeric=true;
    ui->editDNS->IsNumeric=true;
}

CConfigDlg::~CConfigDlg()
{
    for(int i=STATIC_PAGES_NUM;i<ui->tabWidget->count();i++)
    {
        QWidget* pW= ui->tabWidget->widget(STATIC_PAGES_NUM);
        ui->tabWidget->removeTab(STATIC_PAGES_NUM);
        pW->setParent(0);
    }
    delete ui;
}

void CConfigDlg::showEvent(QShowEvent *)
{
    LoadGeneralData();
    for(int i=STATIC_PAGES_NUM;i<ui->tabWidget->count();i++)
    {
        ((CConfigWidgetBase*)ui->tabWidget->widget(i))->Load(pSelector->GetSettings());
    }
    ui->editNTPServer->setEnabled(ui->chkUseNTP->checkState()==Qt::Checked);
}

bool CConfigDlg::SaveGeneralData()
{
    pSelector->GetSettings()->setValue("Network/Mode",ui->cmbMode->currentIndex());
    pSelector->GetSettings()->setValue("Time/UseNTP",ui->chkUseNTP->checkState()==Qt::Checked);
    pSelector->GetSettings()->setValue("Time/NTPServer",ui->editNTPServer->text());
    SetNetworkSettings();
    return true;
}

void CConfigDlg::SetNetworkSettings()
{
    this->setCursor(Qt::WaitCursor);

//    QFile::copy("/psp/network_config","/psp/network_config.bkp");
    {
        QFile file("/psp/network_config");
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream<<"<configuration encryption=\""<<ui->cmbEnc->currentText()<<"\" ";
            stream<<"username=\"\" ";
            stream<<"key=\""<<ui->editKey->text()<<"\" ";
            stream<<"hwaddr=\"22:33:44:55:66:77\" ";
            stream<<"auth=\""<<ui->cmbAuth->currentText()<<"\" ";
            stream<<"type=\"wlan\" ";
            stream<<"ssid=\""<<ui->editSSID->text()<<"\" ";
            stream<<"encoding=\"ascii\" ";
            stream<<"allocation=\""<< (ui->chkDHCP->isChecked() ? "dhcp" : "static") <<"\" ";

            if(!ui->chkDHCP->isChecked())
            {
                stream<<"ip=\""<<ui->editIP->text()<<"\" ";
                stream<<"netmask=\""<<ui->editMask->text()<<"\" ";
                stream<<"gateway=\""<<ui->editGate->text()<<"\" ";
                stream<<"nameserver1=\""<<ui->editDNS->text()<<"\" ";
            }
            stream<<"/>";
            file.close();
        }
    }
    CNetworkTools::ResetNetwork();
    this->setCursor(Qt::ArrowCursor);
}

bool CConfigDlg::LoadGeneralData()
{
    QFile file("/psp/network_config");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString line = stream.readLine();

        ui->editSSID->setText(ReadConfigAttribute(line,"ssid"));
        ui->editKey->setText(ReadConfigAttribute(line,"key"));
        int authIndex = ui->cmbAuth->findText(ReadConfigAttribute(line,"auth"));
        ui->cmbAuth->setCurrentIndex(authIndex!=-1 ? authIndex : 0);
        int encIndex = ui->cmbEnc->findText(ReadConfigAttribute(line,"encryption"));
        ui->cmbEnc->setCurrentIndex(encIndex!=-1 ? encIndex : 0);

        // TODO: This is temporary solution, have to be read from system
        ui->chkDHCP->setChecked(ReadConfigAttribute(line,"allocation")=="static");
    }

    int mode = pSelector->GetSettings()->value("Network/Mode").toInt();
    ui->cmbMode->setCurrentIndex(mode);

    CNetworkTools tools;
    tools.RefreshSystemInfo();
    ui->editIP->setText(tools.IP);
    ui->editMask->setText(tools.Mask);
    ui->editGate->setText(tools.Gateway);
    ui->editDNS->setText(tools.DNS);

    ui->chkUseNTP->setChecked(pSelector->GetSettings()->value("Time/UseNTP",false).toBool());
    ui->editNTPServer->setText(pSelector->GetSettings()->value("Time/NTPServer","").toString());


    return true;
}

QString CConfigDlg::ReadConfigAttribute(const QString& configString,QString name)
{
    name +="=\"";
    int startPos = configString.indexOf(name);
    if(startPos!=-1)
    {
        startPos+=name.length();
        int endPos = configString.indexOf('\"',startPos);
        return endPos !=-1 ? configString.mid(startPos,endPos-startPos) : configString.mid(startPos);
    }
    return "";
}

void CConfigDlg::on_buttonBox_accepted()
{
    SaveGeneralData();
    for(int i=STATIC_PAGES_NUM;i<ui->tabWidget->count();i++)
    {
        ((CConfigWidgetBase*)ui->tabWidget->widget(i))->Save(pSelector->GetSettings());
    }
}

void CConfigDlg::on_chkDHCP_clicked()
{
    bool isDHCP = ui->chkDHCP->isChecked();
    ui->editIP->setEnabled(!isDHCP);
    ui->editMask->setEnabled(!isDHCP);
    ui->editDNS->setEnabled(!isDHCP);
    ui->editGate->setEnabled(!isDHCP);
}

void CConfigDlg::on_chkUseNTP_clicked(bool checked)
{
    ui->editNTPServer->setEnabled(checked);
}
