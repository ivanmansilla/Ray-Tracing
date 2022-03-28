#include "FittedPlane.h"

FittedPlane::FittedPlane() {

}

bool FittedPlane::closestHit(Ray &r, HitInfo &info) const {
    if(Plane::closestHit(r, info)){
        if ((info.p[0] > (pmin.x)) && (info.p[0] < (pmax.x)) && (info.p[2] < (pmax.y)) && (info.p[2] > (pmin.y))){
            info.mat_ptr = this->material.get();
            return true;
        }
    }
    return false;

}

void FittedPlane::aplicaTG(shared_ptr<TG> t)
{
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {

        // Nomes movem el punt de pas
        vec4 newp(this->point, 1.0);
        newp = t->getTG() * newp;
        this->point.x = newp.x;
        this->point.y = newp.y;
        this->point.z = newp.z;
    }else if (dynamic_pointer_cast<ScaleTG>(t)){
            vec4 cmin(pmin.x, 1.0, pmax.y, 1.0);
            vec4 cmax(pmin.x, 1.0, pmax.y, 1.0);
            cmin = t->getTG() * cmin;
            cmax = t->getTG() * cmax;
            pmin.x = cmin.x; pmin.y = cmin.z;
            pmax.x = cmax.x; pmax.y = cmax.z;
    }
}

void FittedPlane::read(const QJsonObject &json) {
    Plane::read(json);

    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = auxVec[1].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
    }
}

void FittedPlane::write(QJsonObject &json) const {
    Plane::write(json);

    QJsonArray auxArray;
    auxArray.append(pmin[0]);
    auxArray.append(pmin[1]);
    json["pmin"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(pmax[0]);
    auxArray2.append(pmax[1]);
    json["pmax"] = auxArray2;
}

void FittedPlane::print(int indentation) const {
    Plane::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "pmin:\t" << pmin[0] << ", "<< pmin[1]  << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax[0] << ", "<< pmax[1] << "\n";
}
