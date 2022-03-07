#include "Triangle.h"

Triangle::Triangle(vec3 a, vec3 b, vec3 c, vec3 point) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->normal = normalize(cross(b-a, c-a));
    this->point = point;
}

bool Triangle::closestHit(Ray &r, HitInfo &info) const {
    if (Plane::closestHit(r, info)) {
        float u = getArea(c,a,info.p) / getArea(a,b,c);
        float v = getArea(a,b,info.p) / getArea(a,b,c);
        float w = getArea(b,c,info.p) / getArea(a,b,c);

        vec3 p = w*a + u*b + v*c;

        if (abs(u+v+w-1.0) < DBL_EPSILON) {
            info.p = p;
            info.normal = normal;
            info.mat_ptr = material.get();
            return true;
        }
    }
    return false;
}

bool Triangle::hasHit(const Ray &r) const {
    if (Plane::hasHit(r)) {
        // TODO: Comprovar si el metodo esta bien implementado
        float u = getArea(c,a,point) / getArea(a,b,c);
        float v = getArea(a,b,point) / getArea(a,b,c);
        float w = getArea(b,c,point) / getArea(a,b,c);

        if (abs(u+v+w-1.0) < DBL_EPSILON) {
            return true;
        }
    }
    return false;
}

void Triangle::read(const QJsonObject &json) {
    Plane::read(json);

    if (json.contains("a") && json["a"].isArray()) {
        QJsonArray auxVec = json["a"].toArray();
        a[0] = auxVec[0].toDouble();
        a[1] = auxVec[1].toDouble();
        a[2] = auxVec[2].toDouble();
    }
    if (json.contains("b") && json["b"].isArray()) {
        QJsonArray auxVec = json["b"].toArray();
        b[0] = auxVec[0].toDouble();
        b[1] = auxVec[1].toDouble();
        b[2] = auxVec[2].toDouble();
    }
    if (json.contains("c") && json["c"].isArray()) {
        QJsonArray auxVec = json["c"].toArray();
        c[0] = auxVec[0].toDouble();
        c[1] = auxVec[1].toDouble();
        c[2] = auxVec[2].toDouble();
    }
}

float Triangle::getArea(vec3 p1, vec3 p2, vec3 p3) const {
    vec3 area = cross(p2-p1, p3-p1) / 2.0f;
    return area.length();
}
