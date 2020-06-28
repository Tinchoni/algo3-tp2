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

// Heurística constructiva golosa con la idea de agregar en cada paso al vecino más cercano al último nodo agregado.
Hamiltoniano heuristicaVecinoMasCercano(Grafo g, int nodoInicial) {
    int n = g.size();
    vector<bool> visitados(n, false);
    Hamiltoniano circuitoHamiltoniano;

	circuitoHamiltoniano.push_back(nodoInicial);
    int actual = nodoInicial;
    visitados[nodoInicial] = true;

    while(!todosVisitados(visitados)) {
        int elMasCercano = obtenerElVecinoNoVisitadoMasCercano(actual, g, visitados);

        circuitoHamiltoniano.push_back(elMasCercano);
        
        actual = elMasCercano;
        visitados[actual] = true;
    }

    return circuitoHamiltoniano;
}

/*************************************************************************************************************/

// Heurística constructiva golosa con la idea de calcular el AGM, recorrerlo mediante DFS y conectar los nodos según el orden dado por DFS.
Hamiltoniano heuristicaAGM(Grafo g) {
    int n = g.size();
    Grafo t = AGM(g);
    Hamiltoniano ordDFS = DFS(t,0);

    return ordDFS;
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

	for(int i = v.size() - 1; i > indice; i--) {
		//swappeo i con i-1
		int aux = v[i-1];
		v[i-1] = v[i];
		v[i] = aux;
	}
}

void insertarNodo(int elegido, Grafo &g, vector<bool> &visitados, vector<int> &insertados) {
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

	// queremos meter izquierda - elegido - derecha
	insertarElementoEnPosicion(insertados, elegido, derecha);
}

// Heurística constructiva golosa con la idea de formar un ciclo inicial y en cada paso agregar un nodo al ciclo que minimice el costo.
Hamiltoniano heuristicaDeInsercion(Grafo g) {
	int n = g.size();
	Grafo circuitoHamiltoniano(n, vector<Peso>(n, -1));
	vector<bool> visitados(n, false);
	Hamiltoniano insertados; // vector en el que el nodo i es adyacente a los nodos i-1 e i+1. Capaz ya podemos volar el vector visitados pero por ahora lo dejo.


	//elegimos 3 nodos cualesquiera para formar un ciclo inicial. En particular, tomamos los primeros 3 nodos:
	visitados[0] = true;
	visitados[1] = true;
	visitados[2] = true;
	insertados.push_back(0);
	insertados.push_back(1);
	insertados.push_back(2);
	
	while(!todosVisitados(visitados)) { // Iteramos hasta que estén todos los nodos insertados en el ciclo, es decir, hasta que estén todos visitados.
		int elegido = elegirNodo(g, visitados, insertados);
		visitados[elegido] = true;
		insertarNodo(elegido, g, visitados, insertados);
	}

	return insertados;
}


/*************************************************************************************************************/
vector<int> darVuelta(vector<int> v) {
	vector<int> dadoVuelta;
	for (int i = v.size() - 1; i >= 0; i--){
		dadoVuelta.push_back(v[i]);
	}
	return dadoVuelta;
}

Hamiltoniano dosOpt(Hamiltoniano ciclo, int i, int j) {
	//ciclo[0:i-1]
	vector<int> primeraParte = vector<int>(ciclo.begin(), ciclo.begin() + (i-1));
	//darVuelta(ciclo[i:j])
	vector<int> medio = darVuelta(vector<int>(ciclo.begin() + i, ciclo.begin() + j));
	//ciclo[j+1:]
	vector<int> ultimaParte = vector<int>(ciclo.begin() + j + 1, ciclo.end());
	//medio += ciclo[j+1:]
	medio.insert(medio.end(), ultimaParte.begin(), ultimaParte.end());
	//primeraParte += medio
	primeraParte.insert(primeraParte.end(), medio.begin(), medio.end());
	return primeraParte;
}

vector<Hamiltoniano> obtenerSubVecindad(Hamiltoniano solucionParcial, Grafo g) {
	vector<Hamiltoniano> vecindad;
	int n = g.size();
	int probabilidadDeDescarte = 0.23;
	default_random_engine generator (42);
	bernoulli_distribution distribution(probabilidadDeDescarte);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
		{
			if(!distribution(generator)) {
				vecindad.push_back(dosOpt(solucionParcial, i, j));
			}
		}
	}
	return vecindad;
}

Hamiltoniano obtenerMejorConMemoriaDeSoluciones(vector<Hamiltoniano> &vecinos, vector<Hamiltoniano> &memoria, Grafo g) {
	vector<Hamiltoniano> vecinosFiltrados;	
	//saco de los posibles vecinos, aquellos que esten en memoria
	for (int j = 0; j < vecinos.size(); j++){
		for (int i = 0; i < memoria.size(); i++){
			if(!sonIguales(vecinos[j], memoria[i])) {
				vecinosFiltrados.push_back(vecinos[j]);
			}
		}
	}
	

	int elMejor = 0;
	for (int i = 1; i < vecinosFiltrados.size(); i++){	
		if(costo(vecinosFiltrados[i], g) < costo(vecinosFiltrados[elMejor], g)){
			elMejor = i;
		}
	}
	return vecinosFiltrados[elMejor];
}


// Metaheurística tabú cuya memoria guarda las últimas soluciones exploradas. 
Hamiltoniano heuristicaTabuSolucionesExploradas(Grafo g, Hamiltoniano solucionInicial(Grafo), bool criterioDeParada(int, int), int tamanioMemoria, vector<Hamiltoniano> obtenerSubVecindad(Hamiltoniano, Grafo) ) {
	Hamiltoniano ciclo = solucionInicial(g);
	Hamiltoniano mejor = ciclo;
	vector<Hamiltoniano> memoria(tamanioMemoria);
	int indiceMasViejoDeLaMemoria = 0;
	int cantIteracionesSinMejora = 0;
	int cantIteraciones = 0;
	while (criterioDeParada(cantIteraciones, cantIteracionesSinMejora)) {
		vector<Hamiltoniano> vecinos = obtenerSubVecindad(ciclo, g);
		ciclo = obtenerMejorConMemoriaDeSoluciones(vecinos, memoria, g);
		memoria[indiceMasViejoDeLaMemoria] = ciclo;
		indiceMasViejoDeLaMemoria = (indiceMasViejoDeLaMemoria + 1) % tamanioMemoria;
		
		if(costo(ciclo, g) < costo(mejor, g)) {
			mejor = ciclo;
		} else {
			cantIteracionesSinMejora++;
		}
		cantIteraciones++;
	}

	return mejor;
}

/*************************************************************************************************************/


// Metaheurística tabú cuya memoria guarda los últimos swaps entre pares de aristas. 
Grafo heuristicaTabuAristasIntercambiadas(Grafo g, int tamanioMemoria, int cantIteracionesSinMejora) {

	return g; // meh
}