#ifndef HARDWARELAYER_H
#define HARDWARELAYER_H

#include <QThread>
#include <QProcess>

class CHardwareLayer : public QThread
{
    Q_OBJECT
    friend class CWidgetSelector;
public:
    static CHardwareLayer* GetInstance(){return pHW;}
    ~CHardwareLayer();
    virtual void timerEvent(QTimerEvent *ev);
    void SetVolume(int volume);
    void SetBrightness(unsigned int brightness);

signals:
    void OnButtonPress();
    void OnButtonRelease();
    void OnRotaryMoved(int speed, bool isButtonDown);

protected slots:
    void OnMixerFinished(int);

protected:
    CHardwareLayer(QWidget* pWidgetSelector);
    static void CreateHardwareLayer(QWidget* pWidgetSelector);
    static CHardwareLayer* pHW;

    int fdKey;
    int fdJoy;
    int timerKeyJoy;
    bool isButtonDown;
    QWidget* pWidgetSelector;

    int lastVolume;
    QProcess* pMixer;

    virtual void run(){exec();}

};

#endif // HARDWARELAYER_H
