#ifndef HEURISTICAS_H_
#define HEURISTICAS_H_

#include "hamiltoniano.h"
#include "grafo.h"

Hamiltoniano heuristicaVecinoMasCercano(Grafo g, int nodoInicial);
Hamiltoniano heuristicaAGM(Grafo g);
Hamiltoniano heuristicaDeInsercion(Grafo g);

vector<Hamiltoniano> obtenerSubVecindad(Hamiltoniano solucionParcial, Grafo g);
Hamiltoniano heuristicaTabuSolucionesExploradas(Grafo g, Hamiltoniano solucionInicial(Grafo), bool criterioDeParada(int, int), int tamanioMemoria, vector<Hamiltoniano> obtenerSubVecindad(Hamiltoniano, Grafo));
// Hamiltoniano heuristicaTabuAristasIntercambiadas(Grafo g, int tamanioMemoria, int cantIteracionesSinMejora);

#endif