#ifndef FEATUREPOINT_H
#define FEATUREPOINT_H

#include <QString>
#include "window-controller/point.h"

class FeaturePoint
{
private:
    gc::Point location;
    unsigned long color;
public:
    FeaturePoint(gc::Point &p, unsigned long c);
    FeaturePoint(int x, int y, unsigned long c);
    FeaturePoint();
    gc::Point getLocation() const;
    void setLocation(const gc::Point &value);
    unsigned long getColor() const;
    void setColor(unsigned long value);
    bool isNull();

    QString toQString();
};

#endif // FEATUREPOINT_H
