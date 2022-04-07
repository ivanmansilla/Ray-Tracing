#include "MaterialTextura.h"

MaterialTextura::MaterialTextura() {}

MaterialTextura::MaterialTextura(const vec3& color): Material() {
    Kd = color;
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k): Material(a, d, s, k) {
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o) : Material(a, d, s, k, o) {
}

MaterialTextura::~MaterialTextura() {}

vec3 MaterialTextura::getAttenuation(const Ray &r_in, const HitInfo &rec) const {
    return Kd;
}

bool MaterialTextura::getOneScatteredRay(const Ray &r_in, const HitInfo &rec, Ray &r_out) const {
    return true;
}

bool MaterialTextura::getMultipleScatteredRays(const Ray &r_in, const HitInfo &rec, std::vector<Ray> &r_out) const {
    return true;
}

void MaterialTextura::read (const QJsonObject &json)
{
    if (json.contains("ka") && json["ka"].isArray()) {
        QJsonArray auxVec = json["ka"].toArray();
        Ka[0] = auxVec[0].toDouble();
        Ka[1] = auxVec[1].toDouble();
        Ka[2] = auxVec[2].toDouble();
    }
    if (json.contains("kd") && json["kd"].isArray()) {
        QJsonArray auxVec = json["kd"].toArray();
        Kd[0] = auxVec[0].toDouble();
        Kd[1] = auxVec[1].toDouble();
        Kd[2] = auxVec[2].toDouble();
    }
    if (json.contains("ks") && json["ks"].isArray()) {
        QJsonArray auxVec = json["ks"].toArray();
        Ks[0] = auxVec[0].toDouble();
        Ks[1] = auxVec[1].toDouble();
        Ks[2] = auxVec[2].toDouble();
    }
    if (json.contains("kt") && json["kt"].isArray()) {
        QJsonArray auxVec = json["kt"].toArray();
        Kt[0] = auxVec[0].toDouble();
        Kt[1] = auxVec[1].toDouble();
        Kt[2] = auxVec[2].toDouble();
    }
    if (json.contains("shininess") && json["shininess"].isDouble())
        shininess = json["shininess"].toDouble();
    if (json.contains("opacity") && json["opacity"].isDouble())
        opacity = json["opacity"].toDouble();
    if (json.contains("nut") && json["nut"].isDouble())
        nut = json["nut"].toDouble();
    if (json.contains("textureFile") && json["textureFile"].isString()){
        fitxer = json["textureFile"].toString();
        textura = make_shared<Texture>(fitxer);
    }
}

vec3 MaterialTextura::getColorPixel(vec2 uv) const {
    return textura->getColorPixel(uv);
}
