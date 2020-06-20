#ifndef GRAFO_H_
#define GRAFO_H_

#include <vector>
#include <iostream>

using namespace std;

typedef int Vertice;
typedef int Peso;

struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p)
        : dst(d), peso(p) {}
};

typedef vector<vector<Vecino>> Grafo;


Grafo leerGrafo(bool dirigido);

void imprimirGrafo(Grafo g);

#endif