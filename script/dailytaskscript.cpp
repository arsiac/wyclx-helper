#include "dailytaskscript.h"

DailyTaskScript::DailyTaskScript()
{
    mainInterface = new MainInterface;
    runningThread = nullptr;

}

DailyTaskScript::~DailyTaskScript()
{
    delete mainInterface;
}

void DailyTaskScript::run()
{
    normal("--运行数据由 `端游模式` 采集--");

}

void DailyTaskScript::setFlashDelay(int value)
{
    flashDelay = value;
}

