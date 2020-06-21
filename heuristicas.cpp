#include "heuristicas.h"

int obtenerElVecinoNoVisitadoMasCercano (int actual, Grafo g, vector<bool> visitados) {
    int n = g.size();
    int elMasCercano = -1;
    for(int i = 0; i < n; i++){
        if(
            !visitados[i] && //no se puede volver a visitar nodos 
            (elMasCercano == -1 || g[actual][i] < g[actual][elMasCercano]) //que le gane a elMasCercano
            ) {
            elMasCercano = i;
        }
    }
    return elMasCercano;
}

//heurística constructiva golosa con la idea de "Vecino más cercano"
Grafo vecinoMasCercano(Grafo g, int nodoInicial) {
    int n = g.size();
    vector<bool> visitados(n, false);
    Grafo circuitoHamiltoniano(n, vector<Peso>(n, -1));

    int actual = nodoInicial;
    visitados[nodoInicial] = true;

    while(!todosVisitados(visitados)) {
        int elMasCercano = obtenerElVecinoNoVisitadoMasCercano(actual, g, visitados);
        conectar(circuitoHamiltoniano, actual, elMasCercano, g[actual][elMasCercano]);
        
        actual = elMasCercano;
        visitados[actual] = true;
    }

    //conecto el ultimo con el primero
    conectar(circuitoHamiltoniano, actual, nodoInicial, g[actual][nodoInicial]);

    for (size_t i = 0; i < n; i++)
    {
        conectar(circuitoHamiltoniano, i, i, 0);
    }

    return circuitoHamiltoniano;
}

