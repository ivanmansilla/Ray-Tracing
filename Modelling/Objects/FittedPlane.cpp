#include "FittedPlane.h"

FittedPlane::FittedPlane() {

}

bool FittedPlane::closestHit(Ray &r, HitInfo &info) const {
    return Plane::closestHit(r, info);
}

void FittedPlane::read(const QJsonObject &json) {
    Plane::read(json);

    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = auxVec[1].toDouble();
        pmin[2] = auxVec[2].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
        pmax[2] = auxVec[2].toDouble();
    }
}

void FittedPlane::write(QJsonObject &json) const {
    Plane::write(json);

    QJsonArray auxArray;
    auxArray.append(pmin[0]);
    auxArray.append(pmin[1]);
    auxArray.append(pmin[2]);
    json["pmin"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(pmax[0]);
    auxArray2.append(pmax[1]);
    auxArray2.append(pmax[2]);
    json["pmax"] = auxArray2;
}

void FittedPlane::print(int indentation) const {
    Plane::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "pmin:\t" << pmin[0] << ", "<< pmin[1] << ", "<< pmin[2] << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax[0] << ", "<< pmax[1] << ", "<< pmax[2] << "\n";
}
