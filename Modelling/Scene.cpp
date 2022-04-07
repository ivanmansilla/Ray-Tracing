#include "Scene.h"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}

// TODO: Fase ***
// Constructora a utilitzar quan s'inicialitza una escena amb un pla base o
// una esfera base
Scene::Scene(shared_ptr<Object> fp)
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
    baseObj = fp;
}

/*
** TODO: FASE 1:
** Metode que testeja la interseccio contra tots els objectes de l'escena i retorna
** la que està més aprop del punt origen del raig
** Si un objecte es intersecat pel raig, el parametre  de tipus HitInfo conte
** la informació sobre la interseccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/

bool Scene::closestHit(Ray &raig, HitInfo& info) const {
    // TODO FASE 0 i FASE 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig.

    bool hit = false;
    float tmin = INFINITY;
    HitInfo infoActual;

    for (unsigned int i = 0; i < objects.size(); i++) {
        if (objects[i]->closestHit(raig, infoActual)) {
            if (tmin > infoActual.t) {
                info = infoActual;
                tmin = infoActual.t;
                hit = true;
            }
        }
    }

    if (baseObj != nullptr && baseObj->closestHit(raig, infoActual)) {
        if (tmin > infoActual.t) {
            info = infoActual;
            tmin = infoActual.t;
            hit = true;
        }
    }
    return hit;
}

/*
** TODO: FASE 2:
** Metode que testeja la interseccio contra tots els objectes de l'escena i retorna
** true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hasHit (const Ray& raig) const {
    for (unsigned int i = 0; i < objects.size(); i++) {
        if (objects[i]->hasHit(raig)) {
           return true;
        }
    }

//    if (baseObj != nullptr && baseObj->closestHit(raig, info)) {
//        return true;
//    }

    return false;
}

// OPCIONAL:
// FASE 3: Mètode que retorna totes les interseccions que es troben al llarg del raig
//    virtual bool allHits(const Ray& r, vector<shared_ptr<HitInfo> infos) const { }



/*
** TODO: Funcio RayColor es la funcio recursiva del RayTracing.
** FASE 0 per a fer el degradat del fons
** FASE 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte
** TODO: Fase 2 de l'enunciat per incloure el shading (Blinn-Phong  i ombres)
** TODO: Fase 2 per a tractar reflexions i transparències
**
*/
vec3 Scene::RayColor(vec3 lookFrom, Ray &ray, int depth) {
    vec3 color;
    vec3 ray2;
    HitInfo h;
    ray2 = ray.getDirection();

    if (closestHit(ray, h)) {
        // color = h.mat_ptr->Kd; // Pregunta g
        // color = h.normal; // Pregunt h
        //color = shading(h, lookFrom); // Pregunta i
        // Pregunta j --> Canviar paràmetres de setUpRenderOneSphere.json
        // color = h.mat_ptr->Kd;  // Pregunta k
        // color = shading(h,lookFrom);

        if (depth == MAXDEPTH) {
            color += shading(h, lookFrom);
        } else {
            Ray sec;
            if (h.mat_ptr->getOneScatteredRay(ray, h, sec)) {
                color += shading(h, lookFrom) + h.mat_ptr->getAttenuation(ray, h) * RayColor(h.p, sec, depth+1);
            } else if (!h.mat_ptr->getOneScatteredRay(ray, h, sec)) {
                color += ((1.f - h.mat_ptr->Kt) * shading(h, lookFrom)) + h.mat_ptr->getAttenuation(ray, h) * RayColor(h.p, sec, depth+1);
            }
        }
    } else {
        color = (vec3((ray2.y + 1)*0.5)*colorTop) + (vec3(1-((ray2.y + 1)*0.5))*colorDown);
    }

    return color;
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

void Scene::setBackground(bool background) {
    backgroundInRecurvise = background;
}

void Scene::setMAXDEPTH(int depth) {
    MAXDEPTH = depth;
}

void Scene::setDownBackground(vec3 color) {
    colorDown = color;
}

void Scene::setTopBackground(vec3 color) {
    colorTop = color;
}

/*
** TODO: Funcio shading es la funcio que calcula la il.luminació en un punt.
** FASE 0: Càlcul de la il.luminació segons la distànica del punt a l'observador
** FASE 1: Càlcul de la il.luminació en un punt (Blinn-Phong i ombres)
*/
vec3 Scene::shading(HitInfo& info, vec3 lookFrom) {
    return blinnPhong(info, lookFrom);
}

vec3 Scene::blinnPhong(HitInfo &info, vec3 lookFrom) {
    vec3 color;
    vec3 point = info.p;
    vec3 normal = info.normal;
    Material* material = info.mat_ptr;
    vec3 kdOrText = material->getColorPixel(info.uv);

    color = (globalLight * material->Ka);    // Afegim l'ambient global

    for (unsigned int i = 0; i < lights.size(); i++) {
        // Part ambient
        vec3 ambient = material->Ka * lights[i]->getIa();

        // Part difusa
        vec3 L = lights[i]->vectorL(point);
        float angleD = dot(normalize(L), normalize(normal));
        vec3 difusa = kdOrText * lights[i]->getId() * glm::max(angleD, 0.f);

        // Part especular
        vec3 H = normalize(L) + normalize(lookFrom) / abs(normalize(L) + normalize(lookFrom));
        float angleS = dot(normalize(normal), normalize(H));
        vec3 especular = material->Ks * lights[i]->getIs() * glm::pow(glm::max(angleS, 0.f), material->shininess);

        // Agafem l'atenuacio
        float attenuation = lights[i]->attenuation(lookFrom);

        // Solucionar shading acne
        vec3 p = point + FLT_EPSILON * L;
        float distance = lights[i]->distanceToLight(p);

        // Raig objecte-llum
        Ray r(p, L, 0.01, distance);

        // Calcul ombra
        float ombra = calculOmbra(r);

        // Formula Blinn-Phong
        color += ambient + ((difusa + especular) * attenuation * ombra);
    }

    return color;
}

float Scene::calculOmbra(Ray raig) {
    if (hasHit(raig)) {
        return 0.0;
    } else {
        return 1.0;
    }
}

void Scene::setLights(std::vector<shared_ptr<Light>> plights) {
    lights = plights;
}

void Scene::setGlobalLight(vec3 light){
    globalLight = light;
}


/*
** TODO: Funcio RayColor es la funcio recursiva del RayTracing.
** FASE 1: Càlcul de la il.luminació en un punt (Blinn-Phong i ombres)
*/
//float Scene::computeShadow(shared_ptr<Light> light, vec3 point) {

//}

/*
 * TODO: FASE 2
 * incloure les llums a l'escena i la il.luminacio global
 */





