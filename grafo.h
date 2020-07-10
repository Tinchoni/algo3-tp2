#ifndef GRAFO_H_
#define GRAFO_H_

#include "common.h"

using namespace std;

typedef int Peso;
typedef vector<vector<Peso>> Grafo;

Grafo leerGrafo();
Grafo leerGrafoDesdeArchivo(string pathAlArchivo);

bool esIgual(Grafo &a, Grafo &b);

void conectar(Grafo &g, int i, int j, int pesoDeLaArista);
void desconectar(Grafo &g, int i, int j);
void imprimirGrafo(Grafo &g);
bool todosVisitados(vector<bool> &visitado);
vector<int> convertirAListaDeNodos(Grafo &g);
Grafo convertirAGrafo(vector<int> &padre, Grafo &g);
int costo(Grafo &g);
Grafo AGM(Grafo &g);
vector<int> DFS(Grafo &g, int v);
vector<int> convertirAListaDeNodos(Grafo &g);

#endif