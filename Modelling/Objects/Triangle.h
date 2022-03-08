#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Plane.h"


class Triangle: public Plane {
public:
    Triangle() {};
    Triangle(vec3 a, vec3 b, vec3 c, vec3 normal);

    virtual ~Triangle() {};
    virtual bool closestHit(Ray &r, HitInfo &info) const override;
    virtual bool hasHit(const Ray &r) const override;

    virtual void read(const QJsonObject &json) override;
private:
    float getArea(vec3 p1, vec3 p2, vec3 p3) const;

    vec3 a, b, c;
};

#endif // TRIANGLE_H
