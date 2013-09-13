#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QString>
#include <QImage>
#include <QColor>

class CClockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CClockWidget(QWidget *parent = 0);
    ~CClockWidget();
    void paintEvent(QPaintEvent *);

    void timerEvent(QTimerEvent * event);
    QColor ShadeColor;
    QColor TextColor;

    QFont TimeFont;

signals:

public slots:

protected:
    int clockTimer;
    QString strTime;
    QString strDate;
    QImage* pBackbufferImage;

    void DrawBackbuffer();
    void CreateShade(QImage *pSrcImage, QImage* pShadeImage,QRect rect,int* shadeMatrix,int radius);
    void FillShadeMatrix(int* shadeMatrix,int radius);
    void showEvent(QShowEvent *);

    int shadeMatrix8[(8*2+1)*(8*2+1)];
    int shadeMatrix4[(4*2+1)*(4*2+1)];

};

#endif // CLOCKWIDGET_H
