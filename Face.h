/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#ifndef FACE_H
#define FACE_H

#include <vector>

class Face {
private:
    std::vector<int> vertices;  

public:
    Face(const std::vector<int>& vertices);

    const std::vector<int>& ObtenerVertices() const;


    void AgregarVertice(int v);

    bool EliminarVertice(int v);

    int ObtenerNumeroVertices() const;
};

#endif // FACE_H
