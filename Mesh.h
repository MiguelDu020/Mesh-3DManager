/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#ifndef MESH_H
#define MESH_H

#include "Face.h"
#include "Vector3.h"
#include <string>
#include <vector>

class Mesh {
public:
  std::string nombre;
  std::vector<Vector3> vertices;
  std::vector<Face> caras;

  Mesh(const std::string &nombre);
  bool CargarDesdeArchivo(const std::string &nombreArchivo);

  std::string ObtenerNombre() const { return nombre; }

  // Métodos para obtener y agregar vértices y caras
  const std::vector<Vector3> &ObtenerVertices() const { return vertices; }
  const std::vector<Face> &ObtenerCaras() const { return caras; }
  void AgregarVertice(const Vector3 &vertice) { vertices.push_back(vertice); }
  void AgregarCara(const Face &cara) { caras.push_back(cara); }
};

#endif // MESH_H
