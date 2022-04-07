#ifndef MATERIALTEXTURA_H
#define MATERIALTEXTURA_H

#endif // MATERIALTEXTURA_H

#include "Material.h"
#include "Texture.h"

class MaterialTextura: public Material
{
public:
    MaterialTextura();
    MaterialTextura(const vec3& color);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);

    virtual ~MaterialTextura();
    virtual vec3 getAttenuation(const Ray& r_in, const HitInfo& rec) const override;
    virtual bool getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const override;
    virtual bool getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec, std::vector<Ray>& r_out) const override;
    virtual void read(const QJsonObject &json)override;
    virtual vec3 getColorPixel(vec2 uv) const override;
private:
    shared_ptr<Texture> textura;
    QString fitxer;
};


