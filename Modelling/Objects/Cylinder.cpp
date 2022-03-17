#include "Cylinder.h"

#include <iostream>

Cylinder::Cylinder(vec3 center, float radius, float h, float data) : Object(data)
{
    this->center = center;
    this->radius = radius;
    this->height = h;
}
Cylinder::Cylinder(float data) : Object(data)
{
    center = vec3(0, 0, 0);
    radius = 1;
    height = 1;
}

bool Cylinder::closestHit(Ray &raig, HitInfo &info) const
{
    float a,b,c;
    float x,z;
    float xo, zo;
    float t_min, t_max;

    t_min=raig.getTmin();
    t_max=raig.getTmax();

    x=raig.getDirection().x;
    z=raig.getDirection().z;
    xo=raig.getOrigin().x - center.x;
    zo=raig.getOrigin().z - center.z;

    a = x*x + z*z;
    b = 2*(xo*x + zo*z);
    c = pow(xo, 2) + pow(zo, 2) - pow(radius,2);
    float discriminant=b*b-4*a*c;

    if(discriminant>0)
    {
        float temp = (-b - sqrtf(discriminant)) / (2 * a);
        if ( temp < t_min && temp > t_max )
        {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (vec3(info.p.x,center.y,info.p.z)-center)/radius;
            info.mat_ptr = material.get();
            return true;
        }
        temp= (-b + sqrtf(discriminant)) / (2 * a);
        if (temp < t_max && temp > t_min)
        {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();
            return true;
        }
    }

    return false;
}


bool Cylinder::hasHit(const Ray &raig) const
{
    float a,b,c;
    float x,z;
    float xo, zo;
    float t_min, t_max;

    t_min=raig.getTmin();
    t_max=raig.getTmax();

    x=raig.getDirection().x;
    z=raig.getDirection().z;
    xo=raig.getOrigin().x - center.x;
    zo=raig.getOrigin().z - center.z;

    a = x*x + z*z;
    b = 2*(xo*raig.getDirection().x + zo*raig.getDirection().z);
    c = pow(xo, 2) + pow(zo, 2) - pow(radius,2);
    float discriminant=b*b-4*a*c;

    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            return true;
        }
        temp = (-b + sqrtf(discriminant)) / (2 * a);
        if (temp < t_max && temp > t_min) {
            return true;
        }
    }
    return false;
}

void Cylinder::aplicaTG(shared_ptr<TG> t)
{
    // TODO review: copy  from sphere
    if (dynamic_pointer_cast<TranslateTG>(t))
    {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x;
        center.y = c.y;
        center.z = c.z;
    }
}

void Cylinder::read(const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("radius") && json["radius"].isDouble())
    {
        radius = json["radius"].toDouble();
    }
    if (json.contains("height") && json["height"].isDouble())
    {
        height = json["height"].toDouble();
    }
    if (json.contains("center") && json["center"].isArray())
    {
        QJsonArray auxVec = json["center"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }
}

//! [1]
void Cylinder::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(center[0]);
    auxArray.append(center[1]);
    auxArray.append(center[2]);
    json["center"] = auxArray;

    json["radius"] = radius;

    json["height"] = height;
}

void Cylinder::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "center:\t" << center[0] << ", " << center[1] << ", " << center[2] << "\n";
    QTextStream(stdout) << indent << "radius:\t" << radius << "\n";
    QTextStream(stdout) << indent << "height:\t" << height << "\n";
}
