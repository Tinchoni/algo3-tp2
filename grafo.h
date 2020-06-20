#ifndef GRAFO_H_
#define GRAFO_H_

#include <vector>
#include <iostream>

using namespace std;

typedef int Peso;
typedef vector<vector<Peso>> Grafo;

Grafo leerGrafo(bool dirigido);
void imprimirGrafo(Grafo g);
Grafo AGM(Grafo g);

#endif