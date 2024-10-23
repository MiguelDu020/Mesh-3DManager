/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#include "Face.h"
#include <algorithm>  // Para std::findF
#include <vector>


Face::Face(const std::vector<int>& vertices) : vertices(vertices) {}

const std::vector<int>& Face::ObtenerVertices() const {
    return vertices;
}


void Face::AgregarVertice(int v) {
    vertices.push_back(v);
}

bool Face::EliminarVertice(int v) {
    auto it = std::find(vertices.begin(), vertices.end(), v);
    if (it != vertices.end()) {
        vertices.erase(it);
        return true;
    }
    return false;
}


int Face::ObtenerNumeroVertices() const {
    return vertices.size();
}
