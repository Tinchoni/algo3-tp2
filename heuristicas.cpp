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

/*************************************************************************************************************/

Grafo heuristicaAGM(Grafo g) {
    int n = g.size();
    Grafo t = AGM(g);
    vector<int> ordDFS = DFS(t,0);
    Grafo circuitoHamiltoniano(n, vector<Peso>(n, -1));

    //for (size_t i = 0; i < n; i++)
    //{
    //   cout << ordDFS[i];
    //}

    for (int i = 1; i < n; i++)
    {
        int desde = ordDFS[i-1];
        int hasta = ordDFS[i];
        conectar(circuitoHamiltoniano,desde,hasta,g[desde][hasta]);
    }
    
    conectar(circuitoHamiltoniano,ordDFS[0],ordDFS[n-1],g[ordDFS[0]][ordDFS[n-1]]);

    for (size_t i = 0; i < n; i++)  {
        conectar(circuitoHamiltoniano, i, i, 0);
    }

    return circuitoHamiltoniano;

}

/*************************************************************************************************************/

int elegirNodo(Grafo &g, vector<bool> &visitados, vector<int> &insertados) {
	// Como criterio de elección tomaremos el vértice más cercano a un vértice que ya está en el circuito. Sino dsp vemos otro criterio
	int n = g.size();
	int elegido = -1;
	int distanciaAlElegido = INFINITO;
	int distanciaAlActual = INFINITO;

	for (int i = 0; i < insertados.size(); i++) {
		int masCercanoAlActual = obtenerElVecinoNoVisitadoMasCercano(i, g, visitados);
		distanciaAlActual = g[i][masCercanoAlActual];
		if(distanciaAlActual < distanciaAlElegido) {
			elegido = masCercanoAlActual;
			distanciaAlElegido = distanciaAlActual;
		}
	}

	return elegido;
}

void insertarElementoEnPosicion(vector<int> &v, int valor, int indice) {
	v.push_back(valor);

	for(int i = v.size() - 1; i >= indice; i--) {
		//swappeo i con i-1
		int aux = v[i-1];
		v[i-1] = v[i];
		v[i] = aux;
	}
}

void insertarNodo(Grafo &circuitoHamiltoniano, int elegido, Grafo &g, vector<bool> &visitados, vector<int> &insertados) {
	// Como criterio de inserción tomaremos dos nodos consecutivos i e i+1 tales que minimicen el costo de insertar al nuevo nodo entre i e i+1. 
	int costoResultante = INFINITO;
	int costoActual;
	int izquierda;
	int derecha;

	//TODO: meter en el informe que debe valer la desigualdad triangular.
	for (int i = 0; i < insertados.size() - 1; i++) {
		// Si tengo (v1) -- (v2) -- (v3) y estoy parado en (v2) necesito saber hacia dónde avanzar, sino toy yendo para atras y me pierdo para siempre (?).
		costoActual = g[insertados[i]][elegido] + g[elegido][insertados[i+1]] - g[insertados[i]][insertados[i+1]];
		if(costoActual < costoResultante) {
				costoResultante = costoActual;
				izquierda = i;
				derecha = i+1;
		}
	}

	// me fijo a mano el costo de insertarlo entre el nodo final y el inicial del ciclo porque sino el for iba a ser asqueroso (?)
	costoActual =  g[insertados[insertados.size()-1]][insertados[0]];
	if(costoActual < costoResultante) {
		costoResultante = costoActual;
		izquierda = insertados.size()-1;
		derecha = 0;
	}

	//cout << "\n ahora toy por conectar el nodo " << elegido << "entre los nodos " << extremo1 << " y " << extremo2 <<"\n";
	//cout << "\n el grafo era este:\n";
	//imprimirGrafo(circuitoHamiltoniano);

	conectar(circuitoHamiltoniano, insertados[extremo1], elegido, g[insertados[extremo1]][elegido]);
	conectar(circuitoHamiltoniano, elegido, insertados[extremo2], g[elegido][insertados[extremo2]]);
	deconectar(circuitoHamiltoniano, insertados[extremo1], insertados[extremo2]);

	// queremos meter izquierda - elegido - derecha
	insertarElementoEnPosicion(insertados, elegido, derecha);
}

Grafo heuristicaDeInsercion(Grafo g) {
	int n = g.size();
	Grafo circuitoHamiltoniano(n, vector<Peso>(n, -1));
	vector<bool> visitados(n, false);
	vector<int> insertados; // vector en el que el nodo i es adyacente a los nodos i-1 e i+1. Capaz ya podemos volar el vector visitados pero por ahora lo dejo.

	for (size_t i = 0; i < n; i++)  {
        conectar(circuitoHamiltoniano, i, i, 0);
    }


	//elegimos 3 nodos cualesquiera para formar un ciclo inicial. En particular, tomamos los primeros 3 nodos:
	conectar(circuitoHamiltoniano, 0, 1, g[0][1]);
	conectar(circuitoHamiltoniano, 1, 2, g[1][2]);
	conectar(circuitoHamiltoniano, 2, 0, g[2][0]);
	visitados[0] = true;
	visitados[1] = true;
	visitados[2] = true;
	insertados.push_back(0);
	insertados.push_back(1);
	insertados.push_back(2);

	//cout << "\n\nHASTA AHORA METISTE LOS PRIMEROS 3 NODOS: \n";
    //imprimirGrafo(circuitoHamiltoniano);

	while(!todosVisitados(visitados)) { // Iteramos hasta que estén todos los nodos insertados en el ciclo, es decir, hasta que estén todos visitados.
		int elegido = elegirNodo(g, visitados, insertados);
		//cout << "el elegido es el nodo numero:" << elegido << "\n"; 
		visitados[elegido] = true;
		insertarNodo(circuitoHamiltoniano, elegido, g, visitados, insertados);


		//cout << "\nfin iteracion en el while,\n";
		//cout << "visitados vale:" << visitados[0] << visitados[1] << visitados[2] << visitados[3] << "\n";
	}

	return circuitoHamiltoniano;
}