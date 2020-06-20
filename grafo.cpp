#include "grafo.h"
#define INFINITO 10e6

Grafo leerGrafo(bool dirigido) {
    int n, m;
    cin >> n >> m;
    Grafo G(n, vector<Peso>(n,INFINITO));

    for (int i = 0; i < m; i++) {
        int v, w, peso;
        cin >> v >> w >> peso;
        G[v - 1][w-1] = peso;
        if (!dirigido) {
            G[w - 1][v-1] = peso;
        }
    }
    for(int i = 0; i < G.size(); i++) {
    	G[i][i] = 0;
    }
    return G;
}

void imprimirGrafo(Grafo g) {
	cout << "   ";
	for(int i = 0; i< g.size(); i++) {
		cout << i + 1<< "\t";
	}
	cout << "\n";
	cout << "  ";
	for(int i = 0; i< (g.size()-1)*4; i++) {
		cout << "__";
	}
	cout << "\n";

    for (int i = 0; i < g.size(); i++)
    {
        cout << i + 1 << "| ";
        for (int j = 0; j < g[i].size(); j++)
        {
            cout << g[i][j] << "\t\n"[j == g.size() - 1]; 
        }
    }
    
}

bool todosVisitados(Grafo g, int n, vector<bool> visitado) {
	bool res = true;
	for(int i = 0; i < n ; i++) {
		res = res && visitado[i];
	}
	return res;
}

int nodoDeMenorDistancia(Grafo g, int n, vector<bool> visitado, vector<int> distancia) {
	int min = INFINITO;
	int res;
	for(int i = 0; i < n; i++) {
		if(distancia[i] < res && !visitado[i]) {
			min = distancia[i];
			res = i;
		}
	}
	return res;
}

Grafo convertirAGrafo(vector<int> padre, Grafo g){
	Grafo res(g.size(), vector<Peso>(g.size(), -1));
	for(int i = 1; i < padre.size(); i++) {
		res[padre[i]][i] = g[padre[i]][i];
		res[i][padre[i]] = g[i][padre[i]];
	}
	return res;
}

Grafo AGM(Grafo g) {
	// Basado fuertemente en el pseudocódigo que vimos en la clase del laboratorio dedicada a árbol generador mínimo.
	int n = g.size(); // pa que sea mas declarativo (?)
	vector<bool> visitado(n,false);
	vector<int> distancia(n,INFINITO);
	vector<int> padre(n, -1);

	int inicial = 0;
	for(int i = 0; i < n - 1; i++) {
		if(i != inicial) {
			distancia[i] = g[inicial][i];
			padre[i] = inicial;
		}
	}

	distancia[inicial] = 0;
	visitado[inicial] = true;

	while(!todosVisitados(g,n,visitado)) {
		int v = nodoDeMenorDistancia(g, n, visitado, distancia);
		visitado[v] = true;

		for(int i = 0; i < n; i++) {
			if( g[v][i] && !visitado[i] && distancia[i] > g[v][i]) { // La onda es que cada i es un nodo sucesor de v. g[v][i] == 0 sii v==i. So, no queremos eso.
				distancia[i] = g[v][i];
				padre[i] = v;
			}
		}
	}

	// en este punto ya tengo padres, que es la sucesion de nodos que me arman el AGM. Lo transformo a lista de adyacencias y listorti:
	Grafo res = convertirAGrafo(padre, g);
	return res;
}