#ifndef HEURISTICAS_H_
#define HEURISTICAS_H_

#include "grafo.h"

Grafo heuristicaVecinoMasCercano(Grafo g, int nodoInicial);
Grafo heuristicaAGM(Grafo g);
Grafo heuristicaDeInsercion(Grafo g);
Grafo heuristicaTabuSolucionesExploradas(Grafo g, int tamanioMemoria, int cantIteracionesSinMejora);
Grafo heuristicaTabuAristasIntercambiadas(Grafo g, int tamanioMemoria, int cantIteracionesSinMejora);

#endif