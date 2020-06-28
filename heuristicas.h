#ifndef HEURISTICAS_H_
#define HEURISTICAS_H_

#include "hamiltoniano.h"
#include "grafo.h"

Hamiltoniano vecinoMasCercano(Grafo g, int nodoInicial);
Hamiltoniano heuristicaAGM(Grafo g);
Hamiltoniano heuristicaDeInsercion(Grafo g);

#endif