#ifndef FADER_H
#define FADER_H

#include <QDialog>

class CFader : public QWidget
{
    Q_OBJECT

    enum FADE_MODE
    {
        FADE_OUT,
        FADE_IN,
        FADE_CROSS
    };

public:
    explicit CFader(QWidget *parent);
    void FadeOut(QWidget* fadingOutWidget);
    void FadeIn(QWidget* fadingInWidget);
    void CrossFade(QWidget* fadingOutWidget,QWidget* fadingInWidget);

    QColor fadeColor;
    int Speed;

signals:
    void FadingDone();

public slots:

protected:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
    int alpha;
    int delta;
    FADE_MODE mode;

    QWidget* outWidget;
    QWidget* inWidget;

    int timerID;
};

#endif // FADER_H
