#include "BTPlayDrv.h"
#include "Log.h"
#include "time.h"
#include <poll.h>

CBTPlayDrv::CBTPlayDrv(QObject *parent) :
    QObject(parent),
    pipeToBtplay("/tmp/.btplay-cmdin"),
    pipeFromBtplay("/tmp/.btplay-cmdout"),
    stateFile("/var/run/btplay.state")
{
    cmdNum=1;
    isPlaying=false;
    timerID=0;
}

CBTPlayDrv::~CBTPlayDrv()
{
    CloseBTConnection();
}

bool CBTPlayDrv::CheckBTConnection()
{
    bool retVal=true;
    if(!pipeToBtplay.isOpen())
    {
       retVal&=pipeToBtplay.open(QIODevice::WriteOnly);
    }
    if(!pipeFromBtplay.isOpen())
    {
        retVal&=pipeFromBtplay.open(QIODevice::ReadOnly);
    }

    if(!retVal)
    {
        CLog::Log("Problem with pipes");
    }
    return retVal;
}

void CBTPlayDrv::CloseBTConnection()
{
    if(pipeToBtplay.isOpen())
    {
        pipeToBtplay.close();
    }
    if(pipeFromBtplay.isOpen())
    {
        pipeFromBtplay.close();
    }

    if(timerID)
    {
        killTimer(timerID);
        timerID=0;
    }
    if(stateFile.isOpen())
    {
        stateFile.close();
    }
}


bool CBTPlayDrv::SendCmd(const char* cmd)
{
    char cmdbuf[256];
    sprintf(cmdbuf,"[%d]%s\n",cmdNum++,cmd);
    if(CheckBTConnection())
    {
        CLog::Log("Cmd: %s",cmdbuf);
        pipeToBtplay.write(cmdbuf);
        pipeToBtplay.flush();
        if((strstr(cmdbuf,"play") || strstr(cmdbuf,"resume")) && !timerID)
        {
            isPlaying=false;
            timerID=startTimer(1000);
        }
        return true;
    }
    return false;
}

void CBTPlayDrv::timerEvent(QTimerEvent *)
{
    //-F- Reading BTPlay output
    ProcessOutput();

    //-F- Checking for BTPlay state
    char data='1';
    for(int retries=0;retries<5;retries++)
    {
        if(!stateFile.isOpen())
        {
            stateFile.open(QIODevice::ReadOnly);
        }

        if(!stateFile.seek(0) || stateFile.read(&data,1)!=1)
        {
            stateFile.close();
        }
        else
        {
            break;
        }
        usleep(20000);
    }

    if(isPlaying==true && data=='1')
    {
        //-F- If playout has been stopped - kill timer
        isPlaying=false;
        killTimer(timerID);
        timerID=0;
        CLog::Log("Song is finished");
        emit OnSongFinished();
    }
    isPlaying = data=='1';
}

void CBTPlayDrv::ProcessOutput()
{
    pollfd pollStruct = {pipeFromBtplay.handle(),POLLIN,0};

    char data[256];
    if(CheckBTConnection())
    {
        while(poll(&pollStruct,1,0))
        {
            pipeFromBtplay.readLine(data,255);
            CLog::Log("Resp: %s",data);
        }
    }
}
