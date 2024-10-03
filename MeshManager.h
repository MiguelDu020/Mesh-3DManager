/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <string>
#include <vector>
#include "Mesh.h"

class MeshManager {
private:
    std::vector<Mesh> meshes; // Lista de mallas cargadas en memoria
public:
    bool CargarMesh(const std::string& nombreArchivo);
    void ListarMeshes() const;
    bool ExisteMalla(const std::string& nombre) const;
    bool GenerarCajaEnvolvente(const std::string& nombre_objeto);
    bool GenerarCajaEnvolventeGlobal();
    bool EliminarMesh(const std::string& nombre);
    bool GuardarMesh(const std::string& nombre, const std::string& nombreArchivo);

    
};

#endif // MESH_MANAGER_H
