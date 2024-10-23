#include "KDTree.h"
#include <cmath>
#include <algorithm>

// Recursividad para insertar
KDTree::Nodo* KDTree::insertar(Nodo* nodo, const Vector3& punto, int profundidad) {
    if (nodo == nullptr) return new Nodo(punto);

    int dimension = profundidad % 3;  // Dimension en la que comparar (x, y o z)
    if (punto.Comparar(nodo->punto, dimension)) {
        nodo->izquierda = insertar(nodo->izquierda, punto, profundidad + 1);
    } else {
        nodo->derecha = insertar(nodo->derecha, punto, profundidad + 1);
    }
    return nodo;
}

// Recursividad para buscar el punto más cercano
Vector3 KDTree::buscarMasCercano(Nodo* nodo, const Vector3& objetivo, int profundidad, Vector3 mejor) const {
    if (nodo == nullptr) return mejor;

    float distanciaActual = nodo->punto.DistanciaA(objetivo);
    float distanciaMejor = mejor.DistanciaA(objetivo);

    if (distanciaActual < distanciaMejor) {
        mejor = nodo->punto;
    }

    int dimension = profundidad % 3;
    Nodo* primero = (objetivo.Comparar(nodo->punto, dimension)) ? nodo->izquierda : nodo->derecha;
    Nodo* segundo = (objetivo.Comparar(nodo->punto, dimension)) ? nodo->derecha : nodo->izquierda;

    mejor = buscarMasCercano(primero, objetivo, profundidad + 1, mejor);
    if (distanciaMejor > fabs((dimension == 0 ? objetivo.ObtenerX() : (dimension == 1 ? objetivo.ObtenerY() : objetivo.ObtenerZ())) -
                              (dimension == 0 ? nodo->punto.ObtenerX() : (dimension == 1 ? nodo->punto.ObtenerY() : nodo->punto.ObtenerZ())))) {
        mejor = buscarMasCercano(segundo, objetivo, profundidad + 1, mejor);
    }
    return mejor;
}

// Recursividad para buscar puntos dentro de una caja delimitadora
void KDTree::buscarVerticesEnCaja(Nodo* nodo, const Vector3& pmin, const Vector3& pmax, int profundidad, std::vector<Vector3>& resultado) const {
    if (nodo == nullptr) return;

    // Verificar si el punto del nodo está dentro de la caja delimitadora
    if (nodo->punto.ObtenerX() >= pmin.ObtenerX() && nodo->punto.ObtenerX() <= pmax.ObtenerX() &&
        nodo->punto.ObtenerY() >= pmin.ObtenerY() && nodo->punto.ObtenerY() <= pmax.ObtenerY() &&
        nodo->punto.ObtenerZ() >= pmin.ObtenerZ() && nodo->punto.ObtenerZ() <= pmax.ObtenerZ()) {
        resultado.push_back(nodo->punto);
    }

    int dimension = profundidad % 3;

    // Recorrer el subárbol izquierdo
    if (pmin.Comparar(nodo->punto, dimension)) {
        buscarVerticesEnCaja(nodo->izquierda, pmin, pmax, profundidad + 1, resultado);
    }

    // Recorrer el subárbol derecho
    if (!pmax.Comparar(nodo->punto, dimension)) {
        buscarVerticesEnCaja(nodo->derecha, pmin, pmax, profundidad + 1, resultado);
    }
}

// Implementación del método público
std::vector<Vector3> KDTree::buscarVerticesEnCaja(const Vector3& pmin, const Vector3& pmax) const {
    std::vector<Vector3> resultado;
    buscarVerticesEnCaja(raiz, pmin, pmax, 0, resultado);
    return resultado;
}
