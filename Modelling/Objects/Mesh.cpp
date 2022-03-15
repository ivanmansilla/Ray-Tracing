#include <QVector>
#include <QVector3D>

#include "Mesh.h"

Mesh::Mesh(): Object()
{

}
Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
}

Mesh::Mesh(const QString &fileName, float data): Object(data)
{
    nom = fileName;
    load(fileName);

}

Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();
    if (triangles.size() > 0) triangles.clear();


}

void Mesh::construeix_triangles() {
    // TO DO Fase 1: A implementar
    vector<vec4> vxsCara; // Vertexs reals de cada cara

    vector<vec4> vertexss = vertexs;
    for(Cara cara : cares){
        vxsCara.clear();
        vxsCara.push_back(vertexs[cara.idxVertices[0]]);
        vxsCara.push_back(vertexs[cara.idxVertices[1]]);
        vxsCara.push_back(vertexs[cara.idxVertices[2]]);

        // Ara treiem l'index i convertim a vec3 per a construir el triangle
        vec3 a = vxsCara[0].swizzle(X, Y, Z);
        vec3 b = vxsCara[1].swizzle(X, Y, Z);
        vec3 c = vxsCara[2].swizzle(X, Y, Z);

        Triangle *tri = new Triangle(a, b, c);

        // Omplim la llista de triangles amb cadascun
        triangles.push_back(*tri);
        delete tri; // Per memoria
    }

}


bool Mesh::closestHit(Ray &raig, HitInfo& info) const {

    // Metode funcional, cridant construeix_triangles() al load

    bool hit = false;
    HitInfo infoAux;
    float t_aux = 9999999;
    vector<Triangle> triangless = triangles;
    for(Triangle triangle : triangles){
        if(triangle.closestHit(raig, infoAux)  && infoAux.t < t_aux){
            t_aux = infoAux.t;
            info.t = infoAux.t;
            info.normal  = infoAux.normal;
            info.p = infoAux.p;
            info.mat_ptr = material.get();
            hit = true;

        }
    }


    // Metode sense construir triangles, falta corregir
    /*
    bool hit = false;
    vector<vec4> vxsCara;
    HitInfo infoAux; // Ens servirà per guardar info temporalment
    float t_aux = 99999; // Sera per comprovar que és el hit més proper

    for (Cara cara : cares){
        vxsCara.clear();
        vxsCara.push_back(vertexs[cara.idxVertices[0]]);
        vxsCara.push_back(vertexs[cara.idxVertices[1]]);
        vxsCara.push_back(vertexs[cara.idxVertices[2]]);

        // Ara treiem l'index i convertim a vec3 per a construir el triangle
        vec3 a = vxsCara[0].swizzle(X, Y, Z);
        vec3 b = vxsCara[1].swizzle(X, Y, Z);
        vec3 c = vxsCara[2].swizzle(X, Y, Z);
        cara.normal = cross(a-b, a-c);

        // Comprovam si intersecta amb el pla de la cara (si raig i normal son ortogonals)
        if(abs(dot(raig.getDirection(), cara.normal))<DBL_EPSILON){
            hit = false;
        }
        // Posarem else's ja que no tendria sentit posar return, ja que hem de mirar més d'una cara
        else{

            // Calculem la D
            float d = -cara.normal[0]*a[0] - cara.normal[1]*a[1] - cara.normal[2]*a[2];

            // Imposem que la recta p+tv compleixi l'eq del pla i aillem la t
            vec3 rp = raig.getOrigin();
            vec3 vp = raig.getDirection();
            float temp =  -cara.normal[0]*rp[0] - cara.normal[1]*rp[1] - cara.normal[2]*rp[2] - d;
            temp/= cara.normal[0]*vp[0] + cara.normal[1]*vp[1] + cara.normal[2]*vp[2];

            // Retornem false si no estem en el rang demanat
            if (temp > raig.getTmax() || temp < raig.getTmin()) {
                hit = false;
            }
            else{
                // Omplim info auxiliar
                infoAux.t = temp;
                infoAux.p = raig.pointAtParameter(infoAux.t);
                infoAux.normal = cara.normal;

                // Ara comprovem que el punt és dins del triangle

                float area = cara.normal.length()/2; // Area del triangle
                vec3 perp; // Vector perpendicular al pla

                vec3 edge1 = c - b;
                vec3 bp = infoAux.p - b;
                perp = cross(edge1, bp);
                float u = (perp.length() / 2)/area;
                if(dot(cara.normal, perp) < 0) hit = false;
                else{

                    vec3 edge2 = a - c;
                    vec3 cp = infoAux.p - c;
                    perp = cross(edge2, cp);
                    float v = (perp.length() / 2)/area;
                    if(dot(cara.normal, perp) < 0) hit = false;
                    else{
                        vec3 edge3 = b - a;
                        vec3 ap = infoAux.p - a;
                        perp = cross(edge3, ap);
                        float w = (perp.length() / 2)/area;
                        if(dot(cara.normal, perp) < 0) hit = false;
                        // Si ha passat totes les condicions hi ha interseccio amb la cara (triangle)
                        else{
                            // Finalment comprovem que és el hit més proper
                            if (infoAux.t < t_aux){
                                // Actualitzem la info
                                t_aux = infoAux.t;
                                info.t = infoAux.t;
                                info.normal  = infoAux.normal;
                                info.p = infoAux.p;
                                info.mat_ptr = material.get();
                                hit = true;
                            }
                        }

                    }

                }
            }


        }
    }
    */

    return hit;



}



bool Mesh::hasHit(const Ray& raig) const {
    // TO DO Fase 1: A implementar
    return false;

}

void Mesh::aplicaTG(shared_ptr<TG> t) {
    // TO DO: Fase 1
}

void Mesh::load (QString fileName) {
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Cara *cara = new Cara();

                        // get points from v array
                        cara->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        cares.push_back(*cara);
                    }
                }
            }
            file.close();
            // Crida per si volem construir els triangles i fer el seu closestHit (hauriem de canviar el mètode)
            construeix_triangles();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}


//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}



