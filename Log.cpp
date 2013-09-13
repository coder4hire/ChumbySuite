#include "Log.h"
#include "QTime"
#include "stdio.h"
#include "stdarg.h"

bool CLog::IsLogEnabled=true;

void CLog::Log(const char* msg,...)
{
    if(IsLogEnabled)
    {
        QString formMsg;
        va_list ap;
        va_start(ap,msg);

        formMsg.vsprintf(msg,ap);
        formMsg=QTime::currentTime().toString("HH:mm:ss")+" "+formMsg;
        va_end(ap);
        //qDebug(("%s %s\n",QTime::currentTime().toString("HH:mm:ss").toLatin1().data(),fr);
        qDebug("%s",formMsg.toLatin1().constData());
    }
}
