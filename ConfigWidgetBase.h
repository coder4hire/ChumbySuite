#ifndef CONFIGWIDGETBASE_H
#define CONFIGWIDGETBASE_H

#include <QWidget>
#include <QSettings>

class CConfigWidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit CConfigWidgetBase(QWidget *parent = 0);
    virtual bool Save(QSettings* pSettings)=0;
    virtual bool Load(QSettings* pSettings)=0;
signals:

public slots:

protected:
    QSettings* pSettings;
};

#endif // CONFIGWIDGETBASE_H
