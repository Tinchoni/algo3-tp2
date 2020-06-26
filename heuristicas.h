#ifndef HEURISTICAS_H_
#define HEURISTICAS_H_

#include "grafo.h"

Grafo vecinoMasCercano(Grafo g, int nodoInicial);
Grafo heuristicaAGM(Grafo g);
Grafo heuristicaDeInsercion(Grafo g);

#endif