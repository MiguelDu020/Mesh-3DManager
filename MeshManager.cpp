/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#include "MeshManager.h"
#include <iostream>
#include <fstream>
#include <cfloat>

bool MeshManager::ExisteMalla(const std::string& nombre) const {
    for (const auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre) {
            return true;
        }
    }
    return false;
}

bool MeshManager::CargarMesh(const std::string& nombreArchivo) {
    Mesh nuevaMalla("");

    if (!nuevaMalla.CargarDesdeArchivo(nombreArchivo)) {
        return false;
    }

    if (ExisteMalla(nuevaMalla.ObtenerNombre())) {
        std::cout << "El objeto " << nuevaMalla.ObtenerNombre() << " ya ha sido cargado en memoria.\n";
        return false;
    }

    meshes.push_back(nuevaMalla);
    std::cout << "El objeto " << nuevaMalla.ObtenerNombre() << " ha sido cargado exitosamente desde el archivo " << nombreArchivo << ".\n";
    return true;
}

void MeshManager::ListarMeshes() const {
    if (meshes.empty()) {
        std::cout << "Memoria vacía. Ningún objeto ha sido cargado en memoria.\n";
    } else {
        std::cout << "Hay " << meshes.size() << " objetos en memoria:\n";
        for (const auto& malla : meshes) {
            // Calcular el número de aristas
            int numAristas = 0;
            for (const auto& face : malla.ObtenerCaras()) {
                numAristas += face.ObtenerVertices().size();  // El número de aristas es igual al número de vértices en la cara
            }

            std::cout << malla.ObtenerNombre() << " contiene " 
                      << malla.ObtenerVertices().size() << " vértices, " 
                      << numAristas << " aristas y " 
                      << malla.ObtenerCaras().size() << " caras.\n";
        }
    }
}

bool MeshManager::GenerarCajaEnvolvente(const std::string &nombre_objeto){
    for(auto& malla : meshes){
        if(malla.ObtenerNombre() == nombre_objeto){
            Vector3 pmin(FLT_MAX, FLT_MAX, FLT_MAX);
            Vector3 pmax(FLT_MIN, FLT_MIN, FLT_MIN);

            for(const auto& vertice : malla.ObtenerVertices()){
                if (vertice.x < pmin.x) pmin.FijarX(vertice.x);
                if (vertice.y < pmin.y) pmin.FijarY(vertice.y);
                if (vertice.z < pmin.z) pmin.FijarZ(vertice.z);    

                if (vertice.x > pmax.x) pmax.FijarX(vertice.x);
                if (vertice.y > pmax.y) pmax.FijarY(vertice.y);
                if (vertice.z > pmax.z) pmax.FijarZ(vertice.z);
            }

            Mesh envolvente("env_" + nombre_objeto);
            envolvente.AgregarVertice(pmin);
            envolvente.AgregarVertice(pmax);

            meshes.push_back(envolvente);
            std::cout << "La caja envolvente del objeto " << nombre_objeto << " se ha generado con el nombre env_" << nombre_objeto << " y se ha agregado a los objetos en memoria.\n";
            return true;
        }
    }
    std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria.\n";
    return false;
}

bool MeshManager::GenerarCajaEnvolventeGlobal() {
    if (meshes.empty()) {
        std::cout << "Memoria vacía. Ningún objeto ha sido cargado en memoria.\n";
        return false;
    }

    Vector3 pmin(FLT_MAX, FLT_MAX, FLT_MAX);
    Vector3 pmax(FLT_MIN, FLT_MIN, FLT_MIN);

    for (const auto& malla : meshes){ 
        for(const auto& vertice : malla.ObtenerVertices()){
            if (vertice.x < pmin.x) pmin.FijarX(vertice.x);
            if (vertice.y < pmin.y) pmin.FijarY(vertice.y);
            if (vertice.z < pmin.z) pmin.FijarZ(vertice.z);    

            if (vertice.x > pmax.x) pmax.FijarX(vertice.x);
            if (vertice.y > pmax.y) pmax.FijarY(vertice.y);
            if (vertice.z > pmax.z) pmax.FijarZ(vertice.z);
        }
    }

    Mesh envolvente("env_global");
    envolvente.AgregarVertice(pmin);
    envolvente.AgregarVertice(pmax);

    meshes.push_back(envolvente);
    std::cout << "La caja envolvente de los objetos en memoria se ha generado con el nombre env_global y se ha agregado a los objetos en memoria.\n";
    return true;
}

bool MeshManager::EliminarMesh(const std::string &nombre){
    for (auto it = meshes.begin(); it != meshes.end(); ++it){
        if (it->ObtenerNombre() == nombre) {
            meshes.erase(it);
            std::cout << "El objeto " << nombre << " ha sido eliminado de la memoria de trabajo.\n";
            return true;
        }
    }
    std::cout << "El objeto " << nombre << " no ha sido cargado en memoria.\n";
    return false;
}

bool MeshManager::GuardarMesh(const std::string &nombre, const std::string &nombreArchivo){
    for(const auto& malla : meshes){
        if(malla.ObtenerNombre() == nombre){
            std::ofstream archivo(nombreArchivo);
            if (!archivo.is_open()) {
                std::cout << "Error al abrir el archivo para escribir.\n";
                return false;
            }
            archivo << malla.ObtenerNombre() << std::endl;
            archivo << malla.ObtenerVertices().size() << std::endl;
            for(const auto& vertice : malla.ObtenerVertices()){
                archivo << vertice.x << " " << vertice.y << " " << vertice.z << std::endl; 
            }
            for(const auto& cara : malla.ObtenerCaras()){
                archivo << cara.ObtenerVertices().size();
                for(int indice : cara.ObtenerVertices()){
                    archivo << " " << indice;
                }
                archivo << std::endl;
            }
            archivo << "-1\n";
            archivo.close();
            std::cout << "La información del objeto " << nombre << " ha sido guardada exitosamente en el archivo " << nombreArchivo << ".\n";
            return true;
        }
    }
    std::cout << "El objeto " << nombre << " no ha sido cargado en memoria.\n";
    return false;
}