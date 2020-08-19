#ifndef REWORDINSTANCE_H
#define REWORDINSTANCE_H

#include <QString>
#include "featurepoint.h"
#include "window-controller/size.h"

class RewordInstance
{
private:
    FeaturePoint *checkPoint;
    gc::Point *instancePoint;
    gc::Point *takePoint;
    gc::Point *ocrPoint;
    gc::Size *ocrSize;

public:
    RewordInstance(FeaturePoint *cp, gc::Point *ip, gc::Point *tp, gc::Point *op, gc::Size *os);
    RewordInstance(int cpx, int cpy, unsigned long cpc, int ipx, int ipy, int tpx, int tpy, int opx, int opy, int opw, int oph);
    RewordInstance();
    ~RewordInstance();

    FeaturePoint *getCheckPoint() const;
    void setCheckPoint(FeaturePoint *value);
    gc::Point *getInstancePoint() const;
    void setInstancePoint(gc::Point *value);
    gc::Point *getTakePoint() const;
    void setTakePoint(gc::Point *value);
    gc::Point *getOcrPoint() const;
    void setOcrPoint(gc::Point *value);
    gc::Size *getOcrSize() const;
    void setOcrSize(gc::Size *value);

    QString toQString();
};

#endif // REWORDINSTANCE_H
