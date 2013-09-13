#include "ClockWidget.h"
#include <QPainter>
#include <QGraphicsBlurEffect>
#include <QGraphicsTextItem>
#include <QTime>
#include <math.h>

CClockWidget::CClockWidget(QWidget *parent) :
    QWidget(parent)
{
    strDate = QDate::currentDate().toString("ddd, dd MMMM ");
    strTime = QTime::currentTime().toString("hh:mm");
    clockTimer = startTimer(1000);
    ShadeColor=0xFFFFFF;

    pBackbufferImage=NULL;
    TimeFont = font();
    TimeFont.setPixelSize(56);

    FillShadeMatrix(shadeMatrix8,8);
    FillShadeMatrix(shadeMatrix4,4);
}

void CClockWidget::FillShadeMatrix(int* shadeMatrix,int radius)
{
    //-F- Filling in coeffs
    double maxRad = sqrt(radius*radius+radius*radius);
    double norm = 0;
    int lineSize = radius*2+1;
    for(int y=-radius;y<=radius;y++)
    {
        for(int x=-radius;x<=radius;x++)
        {
            double rad = sqrt(x*x+y*y);
            if(rad)
            {
                shadeMatrix[x+radius+(y+radius)*lineSize] = (int)(((1-rad/maxRad)*0.9+0.1)*65536);
                norm+= shadeMatrix[x+radius+(y+radius)*lineSize];
            }
            else
            {
                shadeMatrix[x+radius+(y+radius)*lineSize] =0;
            }
        }
    }
    norm = 65536*2/norm;
    for(int y=-radius;y<=radius;y++)
    {
        for(int x=-radius;x<=radius;x++)
        {
            shadeMatrix[x+radius+(y+radius)*lineSize]*=norm;
        }
    }
}

CClockWidget::~CClockWidget()
{
    killTimer(clockTimer);
    delete pBackbufferImage;
}

void CClockWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawImage(0,0,*pBackbufferImage);
}

void CClockWidget::DrawBackbuffer()
{
    if(!pBackbufferImage)
    {
        pBackbufferImage = new QImage(size(),QImage::Format_ARGB32);
    }
    pBackbufferImage->fill(0xFFFFFF);

    QImage textImage(pBackbufferImage->size(),pBackbufferImage->format());
    textImage.fill(0);
    QPainter textPainter(&textImage);

    QFontMetrics fm(font());
    int fontHeight = fm.height();
    textPainter.setPen(TextColor);

    textPainter.setFont(TimeFont);
    textPainter.drawText(0,0,width(),height(),Qt::AlignHCenter|Qt::AlignTop,strTime);

    QFontMetrics fm2(TimeFont);
    CreateShade(&textImage,pBackbufferImage,QRect(0,0,width(),fm2.size(Qt::TextSingleLine,strTime).height()+8),shadeMatrix8,8);

    QFont fnt = font();
    fnt.setBold(true);
    textPainter.setFont(fnt);
    textPainter.drawText(0,height()-fontHeight-4,width()-4,fontHeight,Qt::AlignRight,strDate);
    CreateShade(&textImage,pBackbufferImage,QRect(0,height()-fontHeight-4,width(),fontHeight+4),shadeMatrix4,4);

    QPainter bbPainter(pBackbufferImage);
    bbPainter.drawImage(0,0,textImage);

    update();
}

void CClockWidget::CreateShade(QImage *pSrcImage, QImage* pShadeImage,QRect rect,int* shadeMatrix,int radius)
{
    int lineSize = radius*2+1;
    unsigned int shadeTransparentColor = ShadeColor.rgb() &0xFFFFFF;
    for(int y=rect.top();y<rect.bottom();y++)
    {
        for(int x=rect.left();x<rect.right();x++)
        {
            int topDX = x>=pShadeImage->width()-radius ? pShadeImage->width()-x-1 : radius;
            int topDY = y>=pShadeImage->height()-radius ? pShadeImage->height()-y-1 : radius;
            int startDX = x<radius ? -x : -radius;
            int startDY = y<radius ? -y : -radius;

            int alpha=0;
            for(int dy=startDY;dy<=topDY;dy++)
            {
                const uchar* pixelData = pSrcImage->scanLine(y+dy);
                for(int dx=startDX;dx<=topDX;dx++)
                {
                    if(pixelData[4*(x+dx)]<0x40)
                    {
                        alpha+=shadeMatrix[dx+radius+(dy+radius)*lineSize]*pixelData[4*(x+dx)+3];
                    }
                }
            }
            alpha/=65536;
            if(alpha>255)
            {
                alpha=255;
            }

            if(alpha)
            {
                pShadeImage->setPixel(x,y,alpha<<24|shadeTransparentColor);
            }
        }
    }
}

void CClockWidget::timerEvent(QTimerEvent * event)
{
    if(event->timerId() == clockTimer)
    {
        QString strCurDate = QDate::currentDate().toString("dddd,dd MMMM ");
        if(strDate != strCurDate)
        {
            strDate = strCurDate;
        }

        QTime time = QTime::currentTime();
        if(strTime != time.toString("hh:mm"))
        {
            strTime = time.toString("hh:mm");
            DrawBackbuffer();
        }
   }
}

void CClockWidget::showEvent(QShowEvent *)
{
    DrawBackbuffer();
}
