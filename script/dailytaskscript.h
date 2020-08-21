#ifndef DAILYTASKSCRIPT_H
#define DAILYTASKSCRIPT_H

#include "abstractscript.h"
#include "game-interface/maininterface.h"

class DailyTaskScript: public AbstractScript
{
public:
    DailyTaskScript();
    ~DailyTaskScript();

    void setFlashDelay(int value);

public slots:
    void run() override;

private:
    MainInterface *mainInterface;
    int flashDelay;
};

#endif // DAILYTASKSCRIPT_H
