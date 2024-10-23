/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#ifndef MESH_H
#define MESH_H
#include "KDTree.h"
#include "Face.h"
#include "Vector3.h"
#include <string>
#include <vector>   

class Mesh {
private:
  KDTree arbolKD;
public:
    std::string nombre;
    std::vector<Vector3> vertices;
    std::vector<Face> caras;

    Mesh(const std::string& nombre);

    bool CargarDesdeArchivo(const std::string& nombreArchivo);

    std::string ObtenerNombre() const {
        return nombre; 
    }
    const std::vector<Vector3>& ObtenerVertices() const {
        return vertices; 
    }
    const std::vector<Face>& ObtenerCaras() const {
        return caras; 
    }

    void AgregarVertice(const Vector3& vertice) {
        vertices.push_back(vertice);
        arbolKD.insertar(vertice);  
    }

    void AgregarCara(const Face& cara) {
        caras.push_back(cara);
    }

    Vector3 BuscarVerticeMasCercano(const Vector3& punto) const {
        return arbolKD.buscarMasCercano(punto);
    }

    std::vector<Vector3> BuscarVerticesEnCaja(const Vector3& punto1, const Vector3& punto2) const;
    void CalcularCajaEnvolvente(Vector3& pmin, Vector3& pmax) const;

};

#endif 
