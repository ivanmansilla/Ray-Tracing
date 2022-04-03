#include "Transparent.h"

Transparent::Transparent() {}

Transparent::Transparent(const vec3& color): Material() {
    Ks = color;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k): Material(a, d, s, k) {
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o) : Material(a, d, s, k, o) {
}

Transparent::~Transparent() {}

vec3 Transparent::getAttenuation(const Ray &r_in, const HitInfo &rec) const {
    vec3 i= normalize(r_in.getDirection());
    vec3 i_inv= normalize(r_in.getDirection())*-FLT_EPSILON;
    vec3 n = normalize(rec.normal);
    float ni_over_nt=dot(i,n) > 0 ? nut/1.0:1.0/nut;
    n=dot(i_inv,n)<0?(n*-FLT_EPSILON):n;
    vec3 t= glm::refract(i,n,ni_over_nt);

    if(length(t)<FLT_EPSILON){
        return this->Ks;
    }else{
        return vec3(1,1,1)-this->Ks;
    }

}

bool Transparent::getOneScatteredRay(const Ray &r_in, const HitInfo &rec, Ray &r_out) const {
    vec3 i= normalize(r_in.getDirection());
    vec3 i_inv= normalize(r_in.getDirection())*-FLT_EPSILON;
    vec3 n = normalize(rec.normal);
    float ni_over_nt=dot(i,n) > 0 ? nut/1.0:1.0/nut;
    n=dot(i_inv,n)<0?(n*-FLT_EPSILON):n;
    vec3 t= glm::refract(i,n,ni_over_nt);

    if(length(t)<FLT_EPSILON){
        r_out = Ray(rec.p, glm::reflect(i,n));
    }else{
        r_out = Ray(rec.p, t);
    }
   return true;
}

bool Transparent::getMultipleScatteredRays(const Ray &r_in, const HitInfo &rec, std::vector<Ray> &r_out) const {
    return true;
}
