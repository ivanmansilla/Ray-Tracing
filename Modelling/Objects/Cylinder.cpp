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

bool Cylinder::closestHit(const Ray &raig, HitInfo &info) const
{
    return false;
}

bool Cylinder::hasHit(const Ray &raig) const
{
    // copy from sphere
    //  vec3 oc = raig.getOrigin() - center;
    //  float a = dot(raig.getDirection(), raig.getDirection());
    //  float b = dot(oc, raig.getDirection());
    //  float c = dot(oc, oc) - radius * radius;
    //  float discriminant = b * b - a * c;
    //  if (discriminant > 0)
    //  {
    //      float temp = (-b - sqrt(discriminant)) / a;
    //      if (temp < raig.getTmax() && temp > raig.getTmin())
    //      {
    //          return true;
    //      }
    //      temp = (-b + sqrt(discriminant)) / a;
    //      if (temp < raig.getTmax() && temp > raig.getTmin())
    //      {
    //          return true;
    //      }
    //  }
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