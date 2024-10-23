/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cfloat>

// Constructor de Mesh
Mesh::Mesh(const std::string& nombre) : nombre(nombre) {}

// Cargar malla desde un archivo
bool Mesh::CargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "Error: El archivo " << nombreArchivo << " no existe o es ilegible." << std::endl;
        return false;
    }

    std::string nombreMalla;
    getline(archivo, nombreMalla);
    if (nombreMalla.empty()) {
        std::cout << "Error: El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << std::endl;
        return false;
    }

    this->nombre = nombreMalla;

    int numVertices;
    archivo >> numVertices;
    if (numVertices <= 0) {
        std::cout << "Error: El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << std::endl;
        return false;
    }

    vertices.clear();
    caras.clear();

    // Leer vértices
    for (int i = 0; i < numVertices; ++i) {
        float x, y, z;
        if (!(archivo >> x >> y >> z)) {
            std::cout << "Error: Formato incorrecto al leer los vértices." << std::endl;
            return false;
        }
        Vector3 vertice(x, y, z);
        vertices.push_back(vertice);
        arbolKD.insertar(vertice);  // Insertar el vértice en el KDTree (Componente 2)
    }

    // Leer caras
    std::string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::istringstream iss(linea);
        int numCaras;
        if (!(iss >> numCaras) || numCaras < 0) {
            if (numCaras == -1) break;  // Fin de la lectura de caras
            std::cout << "Error: Formato incorrecto en la definición de caras." << std::endl;
            return false;
        }

        std::vector<int> indicesCaras(numCaras);
        for (int i = 0; i < numCaras; ++i) {
            if (!(iss >> indicesCaras[i])) {
                std::cout << "Error: Formato incorrecto en los índices de las caras." << std::endl;
                return false;
            }
        }

        caras.emplace_back(indicesCaras);
    }

    if (vertices.empty() || caras.empty()) {
        std::cout << "Error: El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << std::endl;
        return false;
    }

    return true;
}

std::vector<Vector3> Mesh::BuscarVerticesEnCaja(const Vector3& punto1, const Vector3& punto2) const {
    return arbolKD.buscarVerticesEnCaja(punto1, punto2);  // KDTree realiza la búsqueda
}
void Mesh::CalcularCajaEnvolvente(Vector3& pmin, Vector3& pmax) const {
    pmin = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
    pmax = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (const auto& vertice : vertices) {
        if (vertice.ObtenerX() < pmin.x) pmin.FijarX(vertice.ObtenerX());
        if (vertice.ObtenerY() < pmin.y) pmin.FijarY(vertice.ObtenerY());
        if (vertice.ObtenerZ() < pmin.z) pmin.FijarZ(vertice.ObtenerZ());

        if (vertice.ObtenerX() > pmax.x) pmax.FijarX(vertice.ObtenerX());
        if (vertice.ObtenerY() > pmax.y) pmax.FijarY(vertice.ObtenerY());
        if (vertice.ObtenerZ() > pmax.z) pmax.FijarZ(vertice.ObtenerZ());
    }
}
