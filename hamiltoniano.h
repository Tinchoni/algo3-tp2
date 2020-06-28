#include "common.h"
#include "grafo.h"

typedef vector<int> Hamiltoniano;
int costo(Hamiltoniano ciclo, Grafo g);
bool sonIguales(Hamiltoniano h1, Hamiltoniano h2);
void imprimirHamiltoniano(Hamiltoniano ciclo, Grafo g);
