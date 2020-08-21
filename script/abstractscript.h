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
    QThread *runningThread;

public slots:
    virtual void run() = 0;

public:
    void setDm(Dm::dmsoft *value);
    void setWc(gc::WindowControl *value);
    bool getScriptState() const;
    void start();
    void stop();

    void setRunningThread(QThread *value);

signals:
    void normal(const QString msg);
    void error(const QString msg);
    void changeScriptState(bool state);
};

#endif // ABSTRACTSCRIPT_H
