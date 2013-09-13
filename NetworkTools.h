#ifndef NETWORKTOOLS_H
#define NETWORKTOOLS_H

#include "QString"

class CNetworkTools
{
public:
    CNetworkTools();
    bool RefreshSystemInfo(QString ifaceName="");
    static void ResetNetwork();

    QString IP;
    QString Mask;
    QString Gateway;
    QString DNS;
protected:
    static QString ExecuteSystemCommand(QString command);
    void Clear();
    QString ReadConfigAttribute(const QString& configString,QString startString,QString endString, int* startFrom=NULL);
};

#endif // NETWORKTOOLS_H
