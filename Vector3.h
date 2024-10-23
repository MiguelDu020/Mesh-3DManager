/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
public:
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0);

    float ObtenerX() const { return x; }
    float ObtenerY() const { return y; }
    float ObtenerZ() const { return z; }

    void FijarX(float nx) { x = nx; }
    void FijarY(float ny) { y = ny; }
    void FijarZ(float nz) { z = nz; }

    float DistanciaA(const Vector3& v) const;

    bool Comparar(const Vector3& v, int dimension) const {
        if (dimension == 0) return x < v.x;
        if (dimension == 1) return y < v.y;
        return z < v.z;
    }
bool EnCaja(const Vector3& pmin, const Vector3& pmax) const {
    return x >= pmin.x && x <= pmax.x &&
           y >= pmin.y && y <= pmax.y &&
           z >= pmin.z && z <= pmax.z;
}

float ObtenerCoordenada(int dimension) const {
    if (dimension == 0) return x;
    if (dimension == 1) return y;
    return z;
}

};

#endif 
