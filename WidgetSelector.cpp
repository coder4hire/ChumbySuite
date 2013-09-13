#include "WidgetSelector.h"
#include "ui_WidgetSelector.h"
#include "QPushButton"
#include "QPainter"
#include "QPaintEvent"

#include "ConfigDlg.h"

#include "CMainWindowWidget.h"
#include "CMP3Widget.h"
#include "WebBrowserWidget.h"
#include "AlarmClockWidget.h"
#include "RadioWidget.h"
#include "NightWidget.h"

#include "HardwareLayer.h"

#include "QKeyEvent"
#include "Log.h"

CWidgetSelector::CWidgetSelector(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    settings("./ChumbySuite.ini",QSettings::IniFormat),
    ui(new Ui::CWidgetSelector)
{
    ui->setupUi(this);
    ui->frameSelector->hide();
    ui->fader->hide();
    ui->stackedWidget->move(0,0);
    ui->stackedWidget->resize(size());
    ui->fader->move(0,0);
    ui->fader->resize(size());

    CHardwareLayer::CreateHardwareLayer(this);
    connect(CHardwareLayer::GetInstance(),SIGNAL(OnButtonPress()),SLOT(processButtonPress()));
    connect(CHardwareLayer::GetInstance(),SIGNAL(OnButtonRelease()),SLOT(processButtonRelease()));
    connect(CHardwareLayer::GetInstance(),SIGNAL(OnRotaryMoved(int,bool)),SLOT(processRotary(int,bool)));
}

CWidgetSelector::~CWidgetSelector()
{
    CleanUpWidgetsAndButtons();
    delete CHardwareLayer::pHW;
    delete ui;
}

void CWidgetSelector::CleanUpWidgetsAndButtons()
{
    //-F- Cleaning up dynamically created items
    for(int i=0;i<ui->gridLayout->count();i++)
    {
        QWidget* pWidget = ui->gridLayout->itemAt(i)->widget();
        if(pWidget)
        {
            pWidget->deleteLater();
        }
    }

    //-F- Cleaning up widgets list
    for(int i=0;i<ui->stackedWidget->count();i++)
    {
        ui->stackedWidget->widget(i)->deleteLater();
    }
}

bool CWidgetSelector::ShowThisWidget(const QString& name)
{
    for(int i=0;i<ui->stackedWidget->count();i++)
    {
        CWidgetBase* retVal = (CWidgetBase*)ui->stackedWidget->widget(i);
        if(retVal->objectName()==name)
        {
            return ShowThisWidget(i);
        }
    }
    return false;
}

bool CWidgetSelector::ShowThisWidget(int index)
{
    if(ui->frameSelector->isVisible())
    {
        ui->fader->CrossFade(ui->frameSelector,ui->stackedWidget);
    }
    else
    {
        ui->stackedWidget->show();
    }

    if(index<ui->stackedWidget->count())
    {
        ui->stackedWidget->setCurrentIndex(index);
        return true;
    }
    return false;
}

QString CWidgetSelector::GetCurrentWidgetName()
{
    if(ui->stackedWidget->isVisible())
    {
        return ui->stackedWidget->currentWidget()->objectName();
    }
    return "";
}

CWidgetBase* CWidgetSelector::GetWidget(int i)
{
    if(i<ui->stackedWidget->count())
    {
        CWidgetBase* retVal = (CWidgetBase*)ui->stackedWidget->widget(i);
        return retVal;
    }
    return NULL;
}

CWidgetBase* CWidgetSelector::GetWidget(QString name)
{
    for(int i=0;i<ui->stackedWidget->count();i++)
    {
        CWidgetBase* retVal = (CWidgetBase*)ui->stackedWidget->widget(i);
        if(retVal->objectName()==name)
        {
            return retVal;
        }
    }
    return NULL;
}

int CWidgetSelector::GetCount()
{
    return ui->stackedWidget->count();
}

void CWidgetSelector::LoadWidgets()
{
    CleanUpWidgetsAndButtons();

    ui->stackedWidget->addWidget(new CMainWindowWidget(this));
    ui->stackedWidget->addWidget(new CMP3Widget(this));
    ui->stackedWidget->addWidget(new CRadioWidget(this));
    ui->stackedWidget->addWidget(new CAlarmClockWidget(this));
    ui->stackedWidget->addWidget(new CWebBrowserWidget(this));
    ui->stackedWidget->addWidget(new CNightWidget(this));

    for(int i=0;i<GetCount();i++)
    {
        GetWidget(i)->Initialize(this,&settings);
    }

    //-F- Dynamically creating selection screen buttons for widgets
    for(int i=0;i<ui->stackedWidget->count();i++)
    {
        QWidgetPushButton* pBtn=new QWidgetPushButton();
        pBtn->resize(48,48);
        pBtn->setIcon(GetWidget(i)->objectName());
        pBtn->Index=i;
        pBtn->pSelector=this;
        ui->gridLayout->addWidget(pBtn,i/4,i%4);
    }
}

void CWidgetSelector::ShowSelectionScreen()
{
    ui->fader->CrossFade(ui->stackedWidget,ui->frameSelector);
}

void CWidgetSelector::on_btnSettings_clicked()
{
    CConfigDlg dlg(this);
    if(dlg.exec()==QDialog::Accepted)
    {
        for(int i=0;i<GetCount();i++)
        {
            GetWidget(i)->OnSettingsChanged();
        }
    }
}

void CWidgetSelector::keyPressEvent(QKeyEvent *ev)
{
    //-F- Processing Rotary events
    switch(ev->key())
    {
    case Qt::Key_Insert:
        processRotary(1,(ev->modifiers()&Qt::ShiftModifier));
        break;
    case Qt::Key_Delete:
        processRotary(-1,(ev->modifiers()&Qt::ShiftModifier));
        break;
    case Qt::Key_PageUp:
        processRotary(5,(ev->modifiers()&Qt::ShiftModifier));
        break;
    case Qt::Key_PageDown:
        processRotary(-5,(ev->modifiers()&Qt::ShiftModifier));
        break;
    }

    if(ev->key()==Qt::Key_Shift)
    {
        processButtonPress();
    }
}

void CWidgetSelector::processRotary(int speed, bool isButtonPressed)
{
    bool isRotaryEventProcessed=false;

    for(int i=0;i<GetCount();i++)
    {
        isRotaryEventProcessed |= GetWidget(i)->OnRotaryMoved(speed,isButtonPressed);
    }

    if(!isRotaryEventProcessed)
    {
        //-F- Process default rotary event - volume control
        volumeCtrl.AdjustVolume(speed);

        CLog::Log("Rotary:%d %d",speed,isButtonPressed);
    }
}

void CWidgetSelector::processButtonPress()
{
    //-F- Processing Button Events  
    lastKeyPressTime.start();
    for(int i=0;i<GetCount();i++)
    {
        GetWidget(i)->OnButtonDown();
    }
}

void CWidgetSelector::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Shift)
    {
        processButtonRelease();
    }
}

void CWidgetSelector::processButtonRelease()
{
    bool isLongClick = lastKeyPressTime.elapsed()>1500;
    int elapsed = lastKeyReleaseTime.restart();
    bool isDoubleClick = !lastKeyReleaseTime.isNull() && elapsed<300;

    //-F- In case of double click - call widget selector screen
    if(isDoubleClick)
    {
        ShowSelectionScreen();
    }
    else
    {
        for(int i=0;i<GetCount();i++)
        {
            GetWidget(i)->OnButtonUp(isLongClick);
        }
    }
}

void QWidgetPushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,icon);
}
