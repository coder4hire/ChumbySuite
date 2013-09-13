#ifndef SETTINGS_H
#define SETTINGS_H

#include "QHash"

class CSettings
{
public:
    CSettings();
    void SetInt(const QString& key,int value);
    int GetInt(const QString& key,int defValue);
    void SetString(const QString& key,const QString& value);
    QString GetInt(const QString& key,const QString& defValue);

protected:
    QHash<QString,int> intHash;
    QHash<QString,QString> stringHash;
    time_t lastChangeTime;
};

#endif // SETTINGS_H
