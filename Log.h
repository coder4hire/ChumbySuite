#ifndef CLOG_H
#define CLOG_H

class CLog
{
public:
    static bool IsLogEnabled;
    static void Log(const char* msg,...);
};

#endif // CLOG_H
