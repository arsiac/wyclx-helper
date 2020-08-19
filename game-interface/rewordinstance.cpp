#include "rewordinstance.h"

QString RewordInstance::toQString()
{
    return QString("RewordInstance{")
            .append(this->checkPoint->toQString())
            .append(", ")
            .append(this->instancePoint->toString().c_str())
            .append(", ")
            .append(this->takePoint->toString().c_str())
            .append(", ocr[")
            .append(this->ocrPoint->toString().c_str())
            .append(", ")
            .append(this->ocrSize->toString().c_str())
            .append("}");
}

FeaturePoint *RewordInstance::getCheckPoint() const
{
    return checkPoint;
}

void RewordInstance::setCheckPoint(FeaturePoint *value)
{
    checkPoint = value;
}

gc::Point *RewordInstance::getInstancePoint() const
{
    return instancePoint;
}

void RewordInstance::setInstancePoint(gc::Point *value)
{
    instancePoint = value;
}

gc::Point *RewordInstance::getTakePoint() const
{
    return takePoint;
}

void RewordInstance::setTakePoint(gc::Point *value)
{
    takePoint = value;
}

gc::Point *RewordInstance::getOcrPoint() const
{
    return ocrPoint;
}

void RewordInstance::setOcrPoint(gc::Point *value)
{
    ocrPoint = value;
}

gc::Size *RewordInstance::getOcrSize() const
{
    return ocrSize;
}

void RewordInstance::setOcrSize(gc::Size *value)
{
    ocrSize = value;
}

RewordInstance::RewordInstance(FeaturePoint *cp, gc::Point *ip, gc::Point *tp, gc::Point *op, gc::Size *os)
{
    this->checkPoint = cp;
    this->instancePoint = ip;
    this->takePoint = tp;
    this->ocrPoint = op;
    this->ocrSize = os;
}

RewordInstance::RewordInstance(int cpx, int cpy, unsigned long cpc, int ipx, int ipy, int tpx, int tpy, int opx, int opy, int opw, int oph)
{
    this->checkPoint = new FeaturePoint(cpx, cpy, cpc);
    this->instancePoint = new gc::Point(ipx, ipy);
    this->takePoint = new gc::Point(tpx, tpy);
    this->ocrPoint = new gc::Point(opx, opy);
    this->ocrSize = new gc::Size(opw, oph);
}

RewordInstance::RewordInstance(){
    this->checkPoint = NULL;
    this->instancePoint = NULL;
    this->takePoint = NULL;
    this->ocrPoint = NULL;
    this->ocrSize = NULL;
}

RewordInstance::~RewordInstance()
{
    delete this->checkPoint;
    delete this->instancePoint;
    delete this->takePoint;
    delete this->ocrPoint;
    delete this->ocrSize;
}
