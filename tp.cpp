#include "grafo.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    Grafo G = leerGrafo(false);

    cout << G[0][0].peso;

}