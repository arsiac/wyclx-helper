#ifndef ABSTRACTSCRIPT_H
#define ABSTRACTSCRIPT_H

#include <QObject>
#include <QString>
#include <QThread>
#include "dm.h"
#include "window-controller/windowcontrol.h"

class AbstractScript: public QObject
{
    Q_OBJECT

protected:
    Dm::dmsoft *dm;
    gc::WindowControl *wc;
    bool scriptStart;

public slots:
    virtual void run() = 0;

public:
    void setDm(Dm::dmsoft *value);
    void setWc(gc::WindowControl *value);
    bool getScriptState() const;
    virtual void start() = 0;
    virtual void stop() = 0;

signals:
    void normal(const QString msg);
    void error(const QString msg);
};

#endif // ABSTRACTSCRIPT_H
