/**************************************************************
  Pontificia Universidad Javeriana
  Autores:  Sebastian Sanchez
            Miguel Duarte 
  Fecha: Agosto 2024
  Materia: Estructuras de datos
****************************************************************/
#include <iostream>
#include <sstream>
#include <limits>
#include "MeshManager.h"

MeshManager manager;
using namespace std; 

// Declaración de funciones para la estructura del programa
void mostrarMenu();
void Menu();
void ayuda();
void pausar();  
void limpiarPantalla();
void inicio() {
  limpiarPantalla();
  mostrarMenu(); // Muestra el menú principal del programa
  Menu(); // Accede al menú de opciones para interactuar con el usuario
}

void ayuda() {
  limpiarPantalla();
  cout << "\033[0m" << endl;
  cout << "\033[1;31mBienvenido \033[0m" << endl;
  cout << "\033[0mA continuación aparecerán los comandos del programa " << endl << endl;
  cout << "\033[34m     1).$cargar nombre_archivo: Carga un archivo de malla poligonal en memoria\033[0m" << endl;
  cout << "\033[32m     2).$listado: Lista los objetos cargados en el sistema junto con la información básica de cada uno (Cantidad de puntos, aristas y caras)\033[0m" << endl;
  cout << "\033[34m     3).$envolvente nombre_objeto: Calcula y muestra la envolvente convexa de un objeto y se guarda como env-nombre_objeto\033[0m" << endl;
  cout << "\033[34m     4).$envolvente: Calcula y muestra la envolvente convexa de todos los objetos y se guarada como env_global\033[0m" << endl;
  cout << "\033[32m     5).$descargar nombre_objeto: Descarga de la memoria toda la información básica (vértices, aristas, caras) del objeto identificado por nombre_objeto\033[0m" << endl;
  cout << "\033[34m     6).$guardar nombre_objeto nombre_archivo: Guarda un objeto en un archivo en el disco\033[0m" << endl;
  cout << "\033[32m     7).$v_cercano px py pz nombre_objeto: Encuentra el vértice más cercano a un punto dado en un objeto o en todos los objetos\033[0m" << endl;
  cout << "\033[34m     8).$v_cercanos_caja nombre_objeto: Encuentra los vértices dentro de una caja delimitadora en un objeto.\033[0m" << endl;
  cout << "\033[32m     9).$ruta_corta i1 i2 nombre_objeto: Calcula la ruta más corta entre dos vértices en un objeto\033[0m" << endl;
  cout << "\033[34m     10).$ruta_corta_centro i1 nombre_objeto: Calcula la ruta más corta entre un vértice y el centro de un objeto\033[0m" << endl;
  cout << "\033[32m     11).$salir: Sale del programa\033[0m" << endl;
  cout << "\033[32m     12).$ayuda: Muestra esta ayuda o la ayuda específica para un comando\033[0m" << endl;
}

void mostrarMenu() {
  limpiarPantalla();  // Limpia la pantalla antes de mostrar el menú
   cout << "\n";  // Agrega espacios para centrar verticalmente

      // Agrega espacios para centrar horizontalmente (asumiendo una consola de 80 caracteres de ancho)
      cout << "                                      MENU             " << endl
           << "                                                                     " << endl
           << "===================                  \033[1;31mcargar\033[1;37m                         ===================  " << endl
           << "===================                  \033[1;31mlistado\033[1;37m                        ===================  " << endl
           << "===================               \033[1;31menvolvente\033[1;37m                        ===================  " << endl
           << "===================                \033[1;31mdescargar\033[1;37m                        ===================  " << endl
           << "===================                  \033[1;31mguardar\033[1;37m                        ===================  " << endl
           << "===================                 \033[1;31mv_cercano\033[1;37m                       ===================  " << endl
           << "===================               \033[1;31mv_cercano_caja\033[1;37m                    ===================  " << endl
           << "===================                \033[1;31mruta_corta\033[1;37m                       ===================  " << endl
           << "===================              \033[1;31mruta_corta_centro\033[1;37m                  ===================  " << endl
           << "===================                  \033[1;31mayuda\033[1;37m                          ===================  " << endl
           << "===================                  \033[1;31msalir\033[1;37m                          ===================  " << endl;
      cout << "\033[0m";
      cout << "                                                          \n\n";
  }

void limpiarPantalla() {// Se usa para que la pantalla no se llene del uso de cada comando o movimiento
    // Se usa ANSI escape code para limpiar la pantalla
    cout << "\033[2J\033[1;1H"; 
}

void pausar() {// Se usa para que el usuario pueda ver bien lo que este en pantalla para que cuando presione enter se limpie
    cout << "Presiona Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Espera a que el usuario presione Enter
    limpiarPantalla();
}

void Menu() {
   string entrada; // Para almacenar la entrada del usuario
   bool menu = true; // Controla el bucle del menú
   do {
       cout << "Selecciona una opción:" << endl << "$/";
       getline(cin, entrada); // Obtiene la línea completa de entrada del usuario
       stringstream input_stringstream(entrada); // Usa stringstream para procesar la entrada
       string comando; 
       input_stringstream >> comando;

       if (comando == "cargar") {
           string nombre_archivo;
           input_stringstream >> nombre_archivo;  // Extrae el nombre del archivo
           if (nombre_archivo.empty()) {
               cout << "Uso: $cargar nombre_archivo" << endl;
           } else {
               if (manager.CargarMesh(nombre_archivo)) {
                   cout << "Archivo cargado exitosamente.\n";
               }
           }
           pausar();
           mostrarMenu();
       } else if (comando == "listado") {
           manager.ListarMeshes();
           pausar();
           mostrarMenu();
       } else if (comando == "envolvente") {
           string nombre_objeto;
           input_stringstream >> nombre_objeto;
           if (nombre_objeto.empty()) {
               manager.GenerarCajaEnvolventeGlobal();
           } else {
               manager.GenerarCajaEnvolvente(nombre_objeto);
           }
           pausar();
           mostrarMenu();
       } else if (comando == "descargar") {
           string nombre_objeto;
           input_stringstream >> nombre_objeto;
           if (nombre_objeto.empty()){
               cout << "Uso: $descargar nombre_objeto" << endl;
           } else {
               manager.EliminarMesh(nombre_objeto);
           }
           pausar();
           mostrarMenu();
       } else if (comando == "guardar") {
           string nombre_objeto, nombre_archivo;
           input_stringstream >> nombre_objeto >> nombre_archivo;
           if(nombre_objeto.empty() || nombre_archivo.empty()){
               cout << "Uso: $guardar nombre_objeto nombre_archivo" << endl;
           } else {
               manager.GuardarMesh(nombre_objeto, nombre_archivo);
           }
           pausar();
           mostrarMenu();
       } else if (comando == "v_cercano") {
           cout << "Encuentra el vértice más cercano a un punto dado (no implementado)" << endl;
           pausar();
           mostrarMenu();
       } else if (comando == "v_cercano_caja") {
           cout << "Encuentra los vértices dentro de una caja (no implementado)" << endl;
           pausar();
           mostrarMenu();
       } else if (comando == "ruta_corta") {
           cout << "Calcula la ruta más corta entre dos vértices de un objeto (no implementado)" << endl;
           pausar();
           mostrarMenu();
       } else if (comando == "ruta_corta_centro") {
           cout << "Calcula la ruta más corta entre un vértice y el centro de un objeto (no implementado)" << endl;
           pausar();
           mostrarMenu();
       } else if (comando == "ayuda") {
           ayuda();
           pausar();
           mostrarMenu();
       } else if (comando == "salir") {
           cout << "Saliendo del programa..." << endl;
           menu = false;
       } else {
           cout << "Comando inválido. Usa $ayuda para ver las opciones." << endl;
           pausar();
           mostrarMenu();
       }
       cin.clear(); // Limpiar el estado del cin
   } while (menu); // Continúa mientras la bandera menu sea true
}

int main() {
    inicio(); // Llama a la función de inicio que muestra el menú
    return 0; // Termina el programa correctamente
}
