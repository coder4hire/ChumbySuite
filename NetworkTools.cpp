#include "NetworkTools.h"
#include "QProcess"

CNetworkTools::CNetworkTools()
{
}

void CNetworkTools::Clear()
{
    IP="";
    Mask="";
    Gateway="";
    DNS="";
}

bool CNetworkTools::RefreshSystemInfo(QString ifaceName)
{
    QString result;

    Clear();

    //-F- Getting IP address and mask
    result = ExecuteSystemCommand("ifconfig "+ifaceName);//+ " | grep \"inet addr\"");
    if(result=="")
    {
        return false;
    }

    int startFrom=0;
    IP="127.0.0.1";
    while(IP =="127.0.0.1")
    {
        IP = ReadConfigAttribute(result,"inet addr:"," ",&startFrom);
        Mask = ReadConfigAttribute(result,"Mask:","\n",&startFrom);
    }

    //-F- Reading default gateway
    result = ExecuteSystemCommand("sh -c \"route -n | grep ^0.0.0.0\"");
    if(result=="")
    {
        return false;
    }
    Gateway = result.section(QRegExp(" +"),1,1);

    //-F- Reading DNS
    result = ExecuteSystemCommand("cat /etc/resolv.conf");
    if(result=="")
    {
        return false;
    }
    DNS=ReadConfigAttribute(result,"nameserver ","\n");

    return true;
}

QString CNetworkTools::ExecuteSystemCommand(QString command)
{
    QProcess proc;
    proc.setProcessChannelMode(QProcess::MergedChannels);
    proc.start(command);
    proc.waitForFinished(10000);
    QByteArray arr = proc.readAll();
    return QString(arr);
}

QString CNetworkTools::ReadConfigAttribute(const QString& configString,QString startString,QString endString, int* startFrom)
{
    int startPos = configString.indexOf(startString, startFrom ? *startFrom : 0);
    if(startPos!=-1)
    {
        startPos+=startString.length();
        int endPos = configString.indexOf(endString,startPos);
        if(startFrom)
        {
            *startFrom=endPos!=-1 ? endPos+endString.length() : configString.length();
        }
        return endPos !=-1 ? configString.mid(startPos,endPos-startPos) : configString.mid(startPos);
    }
    return "";
}

void CNetworkTools::ResetNetwork()
{
    ExecuteSystemCommand("/usr/chumby/scripts/start_network");
}
