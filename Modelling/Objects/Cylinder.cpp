#include "Cylinder.h"
#include "Plane.h"

#include <iostream>

Cylinder::Cylinder(vec3 center, float radius, float h,vec3 axis, float data) : Object(data)
{
    this->center = center;
    this->radius = radius;
    this->height = h;
    this->axis=axis;
}
Cylinder::Cylinder(float data) : Object(data)
{
    center = vec3(0, 0, 0);
    radius = 1;
    height = 1;
    axis =vec3(0,1,0);
}

bool Cylinder::closestHit(Ray &raig, HitInfo &info) const
{
    float a,b,c;
    float x,z;
    float xo, zo;
    float t_min, t_max;
    vector<float> temporals;
    vector<vec3> normals;
    vec3 p;

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
        float temp = (-b - sqrt(discriminant))/ (2 * a);
        if ( temp > t_min && temp < t_max )
        {
            p = raig.pointAtParameter(temp);
            if (p.y >= 0 && p.y <= this->height)
            { // Llarg del cilindre
                temporals.push_back(temp);
                vec3 circumferencia = vec3(0.f, p.y, 0.f);
                vec3 normal = p - circumferencia;
                normals.push_back(normal);
            }
        }
        temp= (-b + sqrtf(discriminant)) / (2 * a);
        if (temp < t_max && temp > t_min)
        {
            p = raig.pointAtParameter(temp);
            if (p.y >= 0 && p.y <= this->height)
            { // Llarg del cilindre
                temporals.push_back(temp);
                vec3 circumferencia = vec3(0.f, p.y, 0.f);
                vec3 normal = p - circumferencia;
                normals.push_back(normal);
            }
        }

        Plane sup(vec3(0,1,0),vec3(0,this->height,0),this->data);
        if(sup.closestHit(raig,info)){
            float dist=distance(info.p,sup.point);
            if(dist<this->radius){
                temporals.push_back(info.t);
                normals.push_back(sup.normal);
            }
        }

        Plane inf(vec3(0,-1,0),vec3(0,0,0),this->data);
        if(inf.closestHit(raig,info)){
            float dist=distance(info.p,inf.point);
            if(dist<this->radius){
                temporals.push_back(info.t);
                normals.push_back(inf.normal);
            }
        }

        float min = t_max;
        int index_min=0;

        for (unsigned int i = 0; i < temporals.size(); i++) {
            if (temporals[i] < min) {
                min = temporals[i];
                index_min=i;
            }
        }
        if(min < t_min || min >t_max || temporals.size()==0)
        {
            return false;
        }

        info.t = min;
        info.p = raig.pointAtParameter(info.t);
        info.normal = normals[index_min];
        info.mat_ptr = material.get();

        return true;
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
    if (json.contains("axis") && json["axis"].isArray())
    {
        QJsonArray auxVecAxis = json["axis"].toArray();
        axis[0] = auxVecAxis[0].toDouble();
        axis[1] = auxVecAxis[1].toDouble();
        axis[2] = auxVecAxis[2].toDouble();
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

    QJsonArray auxArrayAxis;
    auxArrayAxis.append(axis[0]);
    auxArrayAxis.append(axis[1]);
    auxArrayAxis.append(axis[2]);
    json["axis"] = auxArrayAxis;

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
