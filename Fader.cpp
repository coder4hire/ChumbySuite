#include "Fader.h"
#include "QTimerEvent"
#include "QPainter"

CFader::CFader(QWidget *parent) :
    QWidget(parent)
{
    //setAttribute( Qt::WA_DeleteOnClose);
    timerID = -1;
    delta=0;
    mode = FADE_OUT;
    Speed = 24;
}

void CFader::FadeOut(QWidget* fadingOutWidget)
{
    this->outWidget = fadingOutWidget;
    alpha = 0;
    delta = Speed;
    mode = FADE_OUT;
    show();
    timerID = startTimer(30);
}

void CFader::FadeIn(QWidget* fadingInWidget)
{
    this->inWidget = fadingInWidget;
    show();
    inWidget->show();
    mode = FADE_IN;
    delta = -Speed;
    timerID = startTimer(30);
}

void CFader::CrossFade(QWidget* fadingOutWidget,QWidget* fadingInWidget)
{
    this->outWidget = fadingOutWidget;
    this->inWidget = fadingInWidget;
    mode = FADE_CROSS;
    delta = Speed;
    show();
    timerID = startTimer(30);
}


void CFader::timerEvent(QTimerEvent *event)
{
    if(event->timerId() ==timerID)
    {
        update();
        alpha += delta;

        switch(mode)
        {
        case FADE_OUT:
            if (alpha > 255)
            {
                alpha=255;
                killTimer(timerID);
                FadingDone();
                outWidget->hide();
                close();
            }
            break;
        case FADE_IN:
            if (alpha <0)
            {
                alpha=0;
                killTimer(timerID);
                FadingDone();
                close();
            }
            break;
        case FADE_CROSS:
            if (alpha > 255)
            {
                alpha=255;
                delta = -Speed;
                outWidget->hide();
                inWidget->show();
            }
            else if (alpha <0)
            {
                alpha=0;
                killTimer(timerID);
                FadingDone();
                close();
            }

            break;
        }
    }
}

void CFader::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor semiTransparentColor = fadeColor;
    semiTransparentColor.setAlpha(alpha);
    painter.fillRect(rect(), semiTransparentColor);
}
