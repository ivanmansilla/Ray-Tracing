#include <QVector>
#include <QVector3D>

#include "Mesh.h"

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

}

void Mesh::construeix_triangles() {
    // TO DO Fase 1: A implementar
    vector<vec4> vxsCara; // Vertexs reals de cada cara
    Triangle *tri;
    for(Cara cara : cares){
        vxsCara.clear();
        vxsCara.push_back(vertexs[cara.idxVertices[0]]);
        vxsCara.push_back(vertexs[cara.idxVertices[1]]);
        vxsCara.push_back(vertexs[cara.idxVertices[2]]);
        // Ara treiem l'index i convertim a vec3 per a construir el triangle
        vec3 a = vec3(vxsCara[0][1], vxsCara[0][2], vxsCara[0][3]);
        vec3 b = vec3(vxsCara[1][1], vxsCara[1][2], vxsCara[1][3]);
        vec3 c = vec3(vxsCara[2][1], vxsCara[2][2], vxsCara[2][3]);
        tri = new Triangle(a, b, c);
        // Omplim la llista de triangles amb cadascun
        triangles.push_back(*tri);
    }

}


bool Mesh::closestHit(Ray &raig, HitInfo& info) const {
    //this->construeix_triangles();
    bool hit = false;
    //float t_aux = 9999999;
    for(Triangle triangle : triangles){
        if(triangle.closestHit(raig, info)){// and info.t < t_aux){
            //t_aux = info.t;
            hit = true;
        }
    }

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



