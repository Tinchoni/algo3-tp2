#include "grafo.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    Grafo G = leerGrafo(false);
    cout << "El grafo leido es:\n";
    imprimirGrafo(G);

    Grafo elAGM = AGM(G);
    cout << "\n\nY su AGM es: \n";
    imprimirGrafo(elAGM);

    return 0;
}