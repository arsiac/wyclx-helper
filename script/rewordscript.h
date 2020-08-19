#ifndef REWORDSCRIPT_H
#define REWORDSCRIPT_H
#include "abstractscript.h"
#include "instance.h"
#include "game-interface/rewordinterface.h"
#include <iostream>

class RewordScript: public AbstractScript
{
    Q_OBJECT
private:
    int delay;
    int popupDelay;
    Instance **instances;
    int instanceTotal;
    QString fontLibrary;
    RewordInterface *rewordInterface;

public slots:
    void run() override;

public:
    RewordScript();
    ~RewordScript();
    void setInstances(Instance **value, int length);
    void setDelay(int value);
    QString getFontLibrary() const;
    void setFontLibrary(const QString &value);
    void setPopupDelay(int value);
    void start() override;
    void stop() override;
    int getDelay() const;
    int getPopupDelay() const;

signals:
    void scanResult(const QString &name, int number, int expect);
    void setUiState(bool state);
};

#endif // REWORDSCRIPT_H
