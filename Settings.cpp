#include "Settings.h"

CSettings::CSettings()
{
    lastChangeTime=0;
}

void CSettings::SetInt(const QString& key,int value)
{
    intHash[key]=value;
//    SaveData();
}

int CSettings::GetInt(const QString& key,int defValue)
{
    return intHash.value(key,defValue);
}

void CSettings::SetString(const QString& key,const QString& value)
{
    stringHash[key]=value;
//    SaveData();
}

QString CSettings::GetInt(const QString& key,const QString& defValue)
{
    return stringHash.value(key,defValue);
}
