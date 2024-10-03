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

Mesh::Mesh(const std::string& nombre) : nombre(nombre) {}

bool Mesh::CargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "Error: El archivo " << nombreArchivo << " no existe o es ilegible." << std::endl;
        return false;
    }
    //std::cout << "Archivo abierto correctamente." << std::endl;

    std::string nombreMalla;
    getline(archivo, nombreMalla);
    if (nombreMalla.empty()) {
        std::cout << "Error: El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << std::endl;
        return false;
    }

    this->nombre = nombreMalla;
   // std::cout << "Nombre de la malla leído: " << this->nombre << std::endl;

    int numVertices;
    archivo >> numVertices;
    if (numVertices <= 0) {
        std::cout << "Error: El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << std::endl;
        return false;
    }

    vertices.clear();
    caras.clear();

   // std::cout << "Leyendo " << numVertices << " vértices." << std::endl;
    // Leer vértices
    for (int i = 0; i < numVertices; ++i) {
        float x, y, z;
        if (!(archivo >> x >> y >> z)) { // Verificamos que se puedan leer correctamente los valores.
            std::cout << "Error: Formato incorrecto al leer los vértices." << std::endl;
            return false;
        }
        vertices.emplace_back(x, y, z);
       // std::cout << "Vértice " << i << ": (" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    // Leer caras
    std::string linea;
    //std::cout << "Comenzando a leer las caras." << std::endl;

    while (getline(archivo, linea)) {
      // Ignorar las lineas en blanco
      if(linea.empty()){
        continue;
      }
        //std::cout << "Línea leída: " << linea << std::endl;

        std::istringstream iss(linea);
        int numCaras;
        if (!(iss >> numCaras) || numCaras < 0) { // Verificamos que se pueda leer correctamente el número de vértices por cara.
            if (numCaras == -1) {
               // std::cout << "Fin de las caras detectado." << std::endl;
                break;
            }
            std::cout << "Error: Formato incorrecto en la definición de caras." << std::endl;
            return false;
        }

        //std::cout << "Número de vértices en la cara: " << numCaras << std::endl;

        std::vector<int> indicesCaras(numCaras);
        for (int i = 0; i < numCaras; ++i) {
            if (!(iss >> indicesCaras[i])) {
                std::cout << "Error: Formato incorrecto en los índices de las caras." << std::endl;
                return false;
            }
            //std::cout << "Índice de vértice para la cara: " << indicesCaras[i] << std::endl;
        }

        caras.emplace_back(indicesCaras);
       // std::cout << "Cara agregada con " << numCaras << " vértices." << std::endl;
    }

    //std::cout << "Lectura de caras completada." << std::endl;

    if (vertices.empty() || caras.empty()) {
        std::cout << "Error: El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << std::endl;
        return false;
    }

    // std::cout << "El objeto " << this->nombre << " ha sido cargado exitosamente desde el archivo " << nombreArchivo << "." << std::endl;
    return true;
}
