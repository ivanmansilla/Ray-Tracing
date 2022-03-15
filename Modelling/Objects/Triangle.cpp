#include "Triangle.h"

Triangle::Triangle(vec3 _a, vec3 _b, vec3 _c): Plane()
{
   a = _a;
   b = _b;
   c = _c;
   normal = cross(a-b, a-c);
   point = a;
}

bool Triangle::closestHit(Ray &r, HitInfo &info) const {
    /*if (Plane::closestHit(r, info)) {
        float u = getArea(c,a,info.p) / getArea(a,b,c);
        float v = getArea(a,b,info.p) / getArea(a,b,c);
        float w = getArea(b,c,info.p) / getArea(a,b,c);



        if (abs(u+v+w-1.0) < DBL_EPSILON) { // Siempre da u, v y w = 1 por separado, error aqui


            return true;
        }
        vec3 p = w*a + u*b + v*c;
        info.p = p;
        info.normal = normal;
        info.mat_ptr = material.get();
    }
    return false;
    */

   // return Plane::closestHit(r, info); // Comprovació si funciona intersecció amb el pla
    if (Plane::closestHit(r, info)){
        vec3 ab = b - a;
        vec3 ac = c - a;
        vec3 n = cross(ab, ac);
        float area = n.length()/2; // Area del triangle
        vec3 perp; // Vector perpendicular al pla

        vec3 edge1 = c - b;
        vec3 bp = info.p - b;
        perp = cross(edge1, bp);
        float u = (perp.length() / 2)/area;
        if(dot(n, perp) < 0) return false;

        vec3 edge2 = a - c;
        vec3 cp = info.p - c;
        perp = cross(edge2, cp);
        float v = (perp.length() / 2)/area;
        if(dot(n, perp) < 0) return false;

        vec3 edge3 = b - a;
        vec3 ap = info.p - a;
        perp = cross(edge3, ap);
        float w = (perp.length() / 2)/area;
        if(dot(n, perp) < 0) return false;

    return true;
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
    normal = cross(a-b, a-c);
    point = a;
}

float Triangle::getArea(vec3 p1, vec3 p2, vec3 p3) const {
    /*vec3 p1p2 = p2 - p1;
    vec3 p1p3 = p3 - p1;
    vec3 area = cross(p1p2, p1p3);
    float a = area[0];
    float a1= area[1];
    float a2 = area[2];
    float areaT = area.length()/2;

    return areaT;
    */
}

