#ifndef HEURISTICAS_H_
#define HEURISTICAS_H_

#include "hamiltoniano.h"
#include "grafo.h"

Hamiltoniano heuristicaVecinoMasCercano(Grafo &g, int nodoInicial);
Hamiltoniano heuristicaAGM(Grafo &g);
Hamiltoniano heuristicaDeInsercion(Grafo &g);
Hamiltoniano heuristicaTabuSolucionesExploradas(Grafo &g, Hamiltoniano solucionInicial(Grafo&), string criterioDeParada,int umbral, int tamanioMemoria, float probabilidadDeDescarte); 
Hamiltoniano heuristicaTabuAristasIntercambiadas(Grafo &g, Hamiltoniano solucionInicial(Grafo&), string criterioDeParada,int umbral, int tamanioMemoria, float probabilidadDeDescarte);

Hamiltoniano solucionHardcoded(Grafo &g);

#endif