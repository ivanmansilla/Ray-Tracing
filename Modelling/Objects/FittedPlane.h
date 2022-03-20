#ifndef FITTEDPLANE_H
#define FITTEDPLANE_H

#include "Modelling/Objects/Plane.h"


class FittedPlane: public Plane
{
public:
    FittedPlane();
    virtual ~FittedPlane() {};
    virtual bool closestHit(Ray &r, HitInfo &info) const override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec2 pmin, pmax;
};

#endif // FITTEDPLANE_H
