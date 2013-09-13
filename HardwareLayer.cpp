#include "HardwareLayer.h"
#include "QTimerEvent"
#include "QMessageBox"

#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <linux/input.h>

#include "Log.h"

CHardwareLayer* CHardwareLayer::pHW=NULL;

CHardwareLayer::CHardwareLayer(QWidget* pWidgetSelector) :
        QThread(0)
{
    this->pWidgetSelector=pWidgetSelector;
    timerKeyJoy=0;
    lastVolume=-1;
    pMixer=NULL;

    fdKey = open("/dev/input/by-id/soc-noserial-event-kbd",O_RDONLY);
    if(fdKey<=0)
    {
        CLog::Log("Can't open Keyboard device\n");
    }
    fdJoy = open("/dev/input/by-id/soc-noserial-event-joystick",O_RDONLY);
    if(fdJoy<=0)
    {
        CLog::Log("Can't open Joystick device\n");
    }

    if(fdJoy && fdKey)
    {
        timerKeyJoy = startTimer(100);
    }

    isButtonDown=false;

    //-F- Starting process
    start();
}

CHardwareLayer::~CHardwareLayer()
{
    close(fdKey);
    close(fdJoy);
    killTimer(timerKeyJoy);
    exit();

    delete pMixer;
}

void CHardwareLayer::CreateHardwareLayer(QWidget* pWidgetSelector)
{
    if(!pHW)
    {
        pHW = new CHardwareLayer(pWidgetSelector);
    }
}


void CHardwareLayer::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId()==timerKeyJoy)
    {
        struct input_event ev;
        //-F- Button check
        pollfd pollStruct = {fdKey,POLLIN,0};

        while(poll(&pollStruct,1,0))
        {
            if(read (fdKey, &ev, sizeof(ev))==sizeof(ev))
            {
                if(ev.value)
                {
                    OnButtonPress();
                    isButtonDown=true;
                }
                else
                {
                    OnButtonRelease();
                    isButtonDown=false;
                }
            }
        }

        //-F- Joystick check
        pollStruct.fd=fdJoy;

        while(poll(&pollStruct,1,0))
        {
            struct input_event ev;
            if(read (fdJoy, &ev, sizeof(ev))==sizeof(ev))
            {
                emit OnRotaryMoved(ev.value,isButtonDown);
            }
        }
    }
}

void CHardwareLayer::SetVolume(int volume)
{
    lastVolume=volume;
    if(!pMixer)
    {
        pMixer=new QProcess(this);
        //-F- Connecting amixer signals
        connect(pMixer,SIGNAL(finished(int)),SLOT(OnMixerFinished(int)));
    }

    if(pMixer->state()==QProcess::NotRunning)
    {
        lastVolume=-1;
        QString str;
        str.setNum(volume);
        pMixer->start("amixer", QStringList() << "sset"<<"DAC"<<str);
    }
}

void CHardwareLayer::OnMixerFinished(int)
{
    if(lastVolume>=0)
    {
        QString str;
        str.setNum(lastVolume);
        pMixer->start("amixer", QStringList() << "sset"<<"DAC"<<str);
    }
}

void CHardwareLayer::SetBrightness(unsigned int brightness)
{
    if(brightness>100)
    {
        return;
    }

    FILE* fdLight = fopen("/sys/devices/platform/stmp3xxx-bl/backlight/stmp3xxx-bl/brightness","wb");
    if(fdLight<=0)
    {
        CLog::Log("Can't open backlight device\n");
    }
    else
    {
        fprintf(fdLight,"%u\n",brightness);
        fclose(fdLight);
    }
}
