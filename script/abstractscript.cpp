#include "abstractscript.h"

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
}

void AbstractScript::stop()
{
    this->scriptStart = false;
}

