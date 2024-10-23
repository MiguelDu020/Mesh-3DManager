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

    const std::vector<Mesh>& ObtenerTodasLasMallas() const;
    Vector3 BuscarVerticeMasCercanoEnMalla(const std::string& nombre_malla, const Vector3& punto);
    bool ObtenerCajaEnvolvente(const std::string& nombre_malla, Vector3& pmin, Vector3& pmax) const;
    const std::vector<Vector3>& ObtenerVerticesDeMalla(const std::string& nombre_objeto) const;

    std::vector<Vector3> BuscarVerticesEnCaja(const std::string& nombre_malla, const Vector3& punto1, const Vector3& punto2);
};

#endif 
