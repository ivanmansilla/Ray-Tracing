#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Plane.h"
#include "Modelling/TG/TranslateTG.h"
#include "Modelling/TG/ScaleTG.h"


class Triangle: public Plane {
public:
    Triangle() {};
    Triangle(vec3 a, vec3 b, vec3 c);
    Triangle(vec3 a, vec3 b, vec3 c, float size);
    virtual ~Triangle() {};
    virtual bool closestHit(Ray &r, HitInfo &info) const override;
    virtual bool hasHit(const Ray &r) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read(const QJsonObject &json) override;
private:
    float getArea(vec3 p1, vec3 p2, vec3 p3) const;
    // Punts del triangle
    vec3 a, b, c;

    float size;
};

#endif // TRIANGLE_H
