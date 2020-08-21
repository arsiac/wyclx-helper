#include "rewordinterface.h"

RewordInterface::RewordInterface()
{
    interfaceFeaturePointList->append(FeaturePoint(80, 93, 8753603L));
    interfaceFeaturePointList->append(FeaturePoint(71, 577, 12964059L));

    // 刷新按钮
    pointMap->insert("flash", gc::Point(940, 142));
    // 接取确认按钮
    pointMap->insert("take", gc::Point(743, 464));

    rewordInstances = new RewordInstance*[3];
    rewordInstances[0] = new RewordInstance(408, 257, 14540253L, 243, 205, 318, 461, 378, 363, 42, 21);
    rewordInstances[1] = new RewordInstance(612, 257, 14540253L, 448, 205, 523, 461, 583, 363, 42, 21);
    rewordInstances[2] = new RewordInstance(817, 257, 14540253L, 652, 205, 727, 461, 787, 363, 42, 21);

}

RewordInterface::~RewordInterface()
{
    if (rewordInstances)
    {
        for (int i=0; i<3; i++)
        {
            if (rewordInstances[i])
            {
                delete rewordInstances[i];
            }
        }
        delete rewordInstances;
    }
}

RewordInstance **RewordInterface::getRewordInstances() const
{
    return rewordInstances;
}

gc::Point RewordInterface::getPoint(QString key)
{
    QMap<QString, gc::Point>::iterator piter = pointMap->find(key);
    if (piter == pointMap->end())
    {
        return gc::Point(-1, -1);
    }
    return piter.value();
}

FeaturePoint RewordInterface::getFeaturePoint(QString key)
{
    QMap<QString, FeaturePoint>::iterator fpiter = featurePointMap->find(key);
    if (fpiter == featurePointMap->end())
    {
        return FeaturePoint(-1, -1, 0L);
    }
    return fpiter.value();
}
