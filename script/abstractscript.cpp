#include "abstractscript.h"

void AbstractScript::setRunningThread(QThread *value)
{
    runningThread = value;
}

void AbstractScript::setDm(Dm::dmsoft *value)
{
    dm = value;
}

void AbstractScript::setWc(gc::WindowControl *value)
{
    wc = value;
}

bool AbstractScript::getScriptState() const
{
    return scriptStart;
}


void AbstractScript::start()
{
    this->scriptStart = true;
    this->runningThread->start();
    changeScriptState(true);
}

void AbstractScript::stop()
{
    this->scriptStart = false;
    this->runningThread->quit();
    changeScriptState(false);
}

