#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>  // Asegúrate de incluir este encabezado para cout
#include <vector>
#include "Vector3.h"

class KDTree {
  private:
    struct Nodo {
        Vector3 punto;
        Nodo* izquierda;
        Nodo* derecha;

        Nodo(const Vector3& p) : punto(p), izquierda(nullptr), derecha(nullptr){}
    };

    Nodo* raiz;

    Nodo* insertar(Nodo* nodo, const Vector3& punto, int profundidad);
    Vector3 buscarMasCercano(Nodo* nodo, const Vector3& objetivo, int profundidad, Vector3 mejor) const;
    void buscarVerticesEnCaja(Nodo* nodo, const Vector3& pmin, const Vector3& pmax, int profundidad, std::vector<Vector3>& resultado) const;

  public:
    KDTree() : raiz(nullptr) {}

    void insertar(const Vector3& punto) {
        raiz = insertar(raiz, punto, 0);
    }

    Vector3 buscarMasCercano(const Vector3& objetivo) const {
        if (raiz == nullptr) {
            std::cout << "El árbol está vacío.\n";  // Cambiado de cerr a cout
            return Vector3();  // Retorna un Vector3 vacío
        }
        return buscarMasCercano(raiz, objetivo, 0, raiz->punto);
    }

    std::vector<Vector3> buscarVerticesEnCaja(const Vector3& pmin, const Vector3& pmax) const;
};

#endif 
