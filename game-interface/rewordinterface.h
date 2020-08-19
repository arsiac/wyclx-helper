#ifndef REWORDINTERFACE_H
#define REWORDINTERFACE_H

#include "gameinterface.h"
#include "rewordinstance.h"

class RewordInterface : public GameInterface
{
private:
    RewordInstance **rewordInstances;
public:
    RewordInterface();
    ~RewordInterface();
    RewordInstance **getRewordInstances() const;
    gc::Point getPoint(QString key);
    FeaturePoint getFeaturePoint(QString key);
};

#endif // REWORDINTERFACE_H
