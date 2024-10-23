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
#include <vector>

// Verifica si ya existe una malla con el nombre dado
bool MeshManager::ExisteMalla(const std::string& nombre) const {
    for (const auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre) {
            return true;
        }
    }
    return false;
}

// Carga una nueva malla desde un archivo
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

// Lista las mallas cargadas en memoria
void MeshManager::ListarMeshes() const {
    if (meshes.empty()) {
        std::cout << "Memoria vacía. Ningún objeto ha sido cargado en memoria.\n";
    } else {
        std::cout << "Hay " << meshes.size() << " objetos en memoria:\n";
        for (const auto& malla : meshes) {
            int numAristas = 0;
            for (const auto& face : malla.ObtenerCaras()) {
                numAristas += face.ObtenerVertices().size();  // Número de aristas igual al número de vértices por cara
            }
            std::cout << malla.ObtenerNombre() << " contiene " 
                      << malla.ObtenerVertices().size() << " vértices, " 
                      << numAristas << " aristas y " 
                      << malla.ObtenerCaras().size() << " caras.\n";
        }
    }
}

// Genera la caja envolvente de un objeto específico
bool MeshManager::GenerarCajaEnvolvente(const std::string &nombre_objeto) {
    for (auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre_objeto) {
            Vector3 pmin(FLT_MAX, FLT_MAX, FLT_MAX);
            Vector3 pmax(-FLT_MAX, -FLT_MAX, -FLT_MAX);

            for (const auto& vertice : malla.ObtenerVertices()) {
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

// Genera la caja envolvente global para todos los objetos cargados
bool MeshManager::GenerarCajaEnvolventeGlobal() {
    if (meshes.empty()) {
        std::cout << "Memoria vacía. Ningún objeto ha sido cargado en memoria.\n";
        return false;
    }

    Vector3 pmin(FLT_MAX, FLT_MAX, FLT_MAX);
    Vector3 pmax(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (const auto& malla : meshes) { 
        for (const auto& vertice : malla.ObtenerVertices()) {
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

// Elimina una malla de la memoria
bool MeshManager::EliminarMesh(const std::string &nombre) {
    for (auto it = meshes.begin(); it != meshes.end(); ++it) {
        if (it->ObtenerNombre() == nombre) {
            meshes.erase(it);
            std::cout << "El objeto " << nombre << " ha sido eliminado de la memoria de trabajo.\n";
            return true;
        }
    }
    std::cout << "El objeto " << nombre << " no ha sido cargado en memoria.\n";
    return false;
}

// Guarda una malla en un archivo
bool MeshManager::GuardarMesh(const std::string &nombre, const std::string &nombreArchivo) {
    for (const auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre) {
            std::ofstream archivo(nombreArchivo);
            if (!archivo.is_open()) {
                std::cout << "Error al abrir el archivo para escribir.\n";
                return false;
            }
            archivo << malla.ObtenerNombre() << std::endl;
            archivo << malla.ObtenerVertices().size() << std::endl;
            for (const auto& vertice : malla.ObtenerVertices()) {
                archivo << vertice.x << " " << vertice.y << " " << vertice.z << std::endl; 
            }
            for (const auto& cara : malla.ObtenerCaras()) {
                archivo << cara.ObtenerVertices().size();
                for (int indice : cara.ObtenerVertices()) {
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

// Busca el vértice más cercano en una malla usando KDTree
const std::vector<Vector3>& MeshManager::ObtenerVerticesDeMalla(const std::string& nombre_malla) const {
    for (const auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre_malla) {
            return malla.ObtenerVertices();
        }
    }
    static const std::vector<Vector3> vacio;  // Devuelve un vector vacío si no se encuentra la malla
    return vacio;
}

Vector3 MeshManager::BuscarVerticeMasCercanoEnMalla(const std::string& nombre_malla, const Vector3& punto) {
    for (const auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre_malla) {
            return malla.BuscarVerticeMasCercano(punto);
        }
    }
    std::cout << "Malla no encontrada" << std::endl;
    return Vector3();  
}

// Definir la función BuscarVerticesEnCaja
std::vector<Vector3> MeshManager::BuscarVerticesEnCaja(const std::string& nombre_malla, const Vector3& punto1, const Vector3& punto2) {
    for (const auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre_malla) {
            return malla.BuscarVerticesEnCaja(punto1, punto2);  
        }
    }
    std::cout << "Malla no encontrada." << std::endl;
    return {};  
}

bool MeshManager::ObtenerCajaEnvolvente(const std::string& nombre_malla, Vector3& pmin, Vector3& pmax) const {
    for (const auto& malla : meshes) {
        if (malla.ObtenerNombre() == nombre_malla) {
            malla.CalcularCajaEnvolvente(pmin, pmax);
            return true;
        }
    }
    std::cout << "Malla no encontrada.\n";
    return false;
}
const std::vector<Mesh>& MeshManager::ObtenerTodasLasMallas() const {
    return meshes;
}


