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

    float distanceTo(const Vector3& other) const;
    // Métodos para fijar las coordenadas
    void FijarX(float nx) { x = nx; }
    void FijarY(float ny) { y = ny; }
    void FijarZ(float nz) { z = nz; }
};

#endif // VECTOR3_H
