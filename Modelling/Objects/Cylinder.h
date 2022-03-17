#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "Modelling/Animation.h"
#include "Modelling/TG/TranslateTG.h"
#include "glm/gtx/constants.hpp"

class Cylinder : public Object
{
public:
    Cylinder() {};
    Cylinder(vec3 c, float r, float h, float data);
    Cylinder(float data);
    virtual ~Cylinder() {}

    virtual bool closestHit(Ray &raig, HitInfo &info) const override;
    virtual bool hasHit(const Ray &raig) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

private:
    vec3 center;
    float radius;
    float height;
};

#endif
