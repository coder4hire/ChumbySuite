#ifndef BTPLAYDRV_H
#define BTPLAYDRV_H

#include <QObject>
#include <QFile>

class CBTPlayDrv : public QObject
{
    Q_OBJECT
public:
    explicit CBTPlayDrv(QObject *parent = 0);
    ~CBTPlayDrv();
    bool SendCmd(const char* cmd);

signals:
    void OnSongFinished();

protected:
    QFile pipeToBtplay;
    QFile pipeFromBtplay;
    QFile stateFile;

    bool CheckBTConnection();
    void CloseBTConnection();

    void ProcessOutput();

    unsigned int cmdNum;
    bool isPlaying;
    void timerEvent(QTimerEvent *);

    int timerID;
};

#endif // BTPLAYDRV_H
