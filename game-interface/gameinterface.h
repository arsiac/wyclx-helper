#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include<QList>
#include <QMap>
#include "window-controller/windowcontrol.h"
#include "featurepoint.h"

class GameInterface
{
protected:
    QList<GameInterface> *subInterfaceList;
    QList<FeaturePoint> *interfaceFeaturePointList;
    QMap<QString, FeaturePoint> *featurePointMap;
    QMap<QString, gc::Point> *pointMap;

public:
    GameInterface();
    ~GameInterface();
    bool check(gc::WindowControl *wc);
};
#endif // GAMEINTERFACE_H
