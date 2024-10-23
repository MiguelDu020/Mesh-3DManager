/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::DistanciaA(const Vector3& other) const {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
}
