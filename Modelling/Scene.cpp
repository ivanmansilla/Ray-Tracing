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

    bool hasClosestHit = false;

    for (shared_ptr<Object> object : objects) {
        if (object->closestHit(raig, info))
            return true;
        else
            if (object->closestHit(raig, info))
                return true;

    }

    return false;
}

/*
** TODO: FASE 2:
** Metode que testeja la interseccio contra tots els objectes de l'escena i retorna
** true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hasHit (const Ray& raig) const {

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
vec3 Scene::RayColor (vec3 lookFrom, Ray &ray, int depth ) {
    vec3 color;
    vec3 ray2;
    HitInfo h;
    ray2 = ray.getDirection();

    if (closestHit(ray, h)) {
        // color = h.mat_ptr->Kd; // Pregunta g
        // color = h.normal; // Pregunt h
        color = shading(h, lookFrom); // Pregunta i (falta completar método shading)
        // Pregunta j --> Canviar paràmetres de setUpRenderOneSphere.json
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
    vec3 color;
    lookFrom = normalize(lookFrom); // Normalitzem per a que la distància euclidiana acabi donant entre 0 i 1.
    vec3 p = normalize(info.p);
    float dist = sqrt(pow(lookFrom[0]-p[0],2) + pow(lookFrom[1]-p[1],2) + pow(lookFrom[2]-p[2],2)); // Distancia euclidiana entre l'observador i el punt on intersecta normalitzats
    color = normalize(info.mat_ptr->Ka) * dist; // Multipliquem el vector del material normalitzat per la distància a la que esteim de l'objecte
    return color;
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
 * void setLights(std::vector<shared_ptr<Light>> lights) {}
 * void setGlobalLight(vec3 light);
 */




