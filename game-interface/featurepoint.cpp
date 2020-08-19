#include "featurepoint.h"


FeaturePoint::FeaturePoint(gc::Point &p, unsigned long c)
{
    this->location = p;
    this->color = c;
}

FeaturePoint::FeaturePoint(int x, int y, unsigned long c)
{
    this->location = gc::Point(x, y);
    this->color = c;
}

FeaturePoint::FeaturePoint()
{
    this->location = gc::Point(0, 0);
    this->color = 0L;
}

unsigned long FeaturePoint::getColor() const
{
    return color;
}

void FeaturePoint::setColor(unsigned long value)
{
    color = value;
}

bool FeaturePoint::isNull()
{
    return location.x() < 0 || location.y() < 0;
}

QString FeaturePoint::toQString()
{
    return QString("FeaturePoint {")
            .append(this->location.toString().c_str())
            .append(", ")
            .append(QString::number(this->color))
            .append("}");
}

gc::Point FeaturePoint::getLocation() const
{
    return location;
}

void FeaturePoint::setLocation(const gc::Point &value)
{
    location = value;
}

