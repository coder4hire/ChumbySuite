#include "CMainWindowWidget.h"
#include "ui_CMainWindowWidget.h"
#include <WidgetSelector.h>
#include <QTime>
#include <QDate>
#include <QPaintEvent>
#include <QPainter>
#include <QDir>
#include <QPaintEngine>
#include <QGraphicsEffect>

#include "ConfigMainWindow.h"
#include "Settings.h"
#include "Log.h"

CMainWindowWidget::CMainWindowWidget(QWidget *parent):
    CWidgetBase(parent),
    ui(new Ui::CMainWindowWidget)
{
    setObjectName("Main Screen");

    ui->setupUi(this);

    setAttribute(Qt::WA_OpaquePaintEvent);
    LoadAndResizePixmap("./default.jpg");
    pConfigWidget = new CConfigMainWindow();

    slideShowTimer=0;

    ui->clockWidget->TimeFont.setFamily("Sans Serif");
    ui->clockWidget->TimeFont.setPixelSize(60);
    ui->clockWidget->TimeFont.setItalic(true);
    ui->clockWidget->TimeFont.setBold(true);
}

CMainWindowWidget::~CMainWindowWidget()
{
    delete pConfigWidget;
    if(slideShowTimer)
    {
        killTimer(slideShowTimer);
    }
    delete ui;
}

void CMainWindowWidget::Initialize(CWidgetSelector *pSelector, QSettings *pSettings)
{
    CWidgetBase::Initialize(pSelector,pSettings);
    StartStopSlideShow();
}

void CMainWindowWidget::StartStopSlideShow()
{
    if(pSettings->value("MainWnd/SlideShowEnabled").toBool())
    {
        if(!slideShowTimer)
        {
            slideShowTimer=startTimer(pSettings->value("MainWnd/Delay").toInt()*60000);
        }
        QTimerEvent ev(slideShowTimer);
        timerEvent(&ev);
    }
    else if(slideShowTimer)
    {
        killTimer(slideShowTimer);
        slideShowTimer=0;
    }
}

void CMainWindowWidget::showEvent(QShowEvent *)
{
}

void CMainWindowWidget::timerEvent(QTimerEvent * event)
{
    if(event->timerId() == slideShowTimer)
    {
        QString folder = pSettings->value("MainWnd/PicturesFolder").toString();
        QDir dir(folder);
        QStringList filesList = dir.entryList(QDir::Readable | QDir::Files,QDir::Name);

        int i = filesList.indexOf(slideFileName);

        if(filesList.count()==0)
        {
            LoadAndResizePixmap("./default.jpg");
        }
        else
        {
            if(pSettings->value("MainWnd/Randomize").toBool())
            {
                //-F- Random pictures
                int randIndex = i;
                while(randIndex==i || randIndex>=filesList.count())
                {
                    randIndex = (int)(((double)rand()/RAND_MAX)*filesList.count());
                }
                i=randIndex;
            }
            else
            {
                //-F- Sequential order of pictures
                i++;
                if(i<0 || i>=filesList.count())
                {
                    i=0;
                }
            }

            slideFileName = filesList[i];
            LoadAndResizePixmap(dir.path()+"/"+slideFileName);
        }

        if(isVisible())
        {
            update();
        }
    }

}

void CMainWindowWidget::on_btnWidgetSelect_clicked()
{
    pSelector->ShowSelectionScreen();
}

void CMainWindowWidget::LoadAndResizePixmap(QString fileName)
{
    QPixmap pixmapOriginal;
    if(pixmapOriginal.load(fileName))
    {
        QPalette p = palette();
        backPixmap = pixmapOriginal.scaled(size());
    }
    else
    {
        CLog::Log("Can't load background image file: %s",fileName.toLatin1().data());
    }

}

void CMainWindowWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!backPixmap.isNull())
    {
        painter.drawPixmap(event->rect(),backPixmap,event->rect());
    }
}

void CMainWindowWidget::OnSettingsChanged()
{
    StartStopSlideShow();
}
