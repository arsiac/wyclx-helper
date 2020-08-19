#include "gameinterface.h"

GameInterface::GameInterface()
{
    subInterfaceList = new QList<GameInterface>;
    interfaceFeaturePointList = new QList<FeaturePoint>;
    featurePointMap = new QMap<QString, FeaturePoint>;
    pointMap = new QMap<QString, gc::Point>;
}

GameInterface::~GameInterface()
{
    delete subInterfaceList;
    delete interfaceFeaturePointList;
    delete featurePointMap;
    delete pointMap;
}

bool GameInterface::check(gc::WindowControl *wc)
{
    if (!wc || wc->isInvalid())
    {
        return false;
    }

    QList<FeaturePoint>::iterator fiter = interfaceFeaturePointList->begin();
    for (; fiter != interfaceFeaturePointList->end(); fiter++)
    {
        if (fiter->getColor() != wc->getPixel(fiter->getLocation().x(), fiter->getLocation().y()))
        {
            return false;
        }
    }
    return true;
}


