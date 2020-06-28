#include "grafo.h"

Grafo leerGrafo() {
    int n, m;
    cin >> n >> m;
    Grafo G(n, vector<Peso>(n, -1));

    for (int i = 0; i < m; i++) {
        int v, w, peso;
        cin >> v >> w >> peso;
		conectar(G, v-1, w-1, peso);
    }
    for(int i = 0; i < G.size(); i++) {
    	G[i][i] = 0;
    }
    return G;
}

bool esIgual(Grafo a, Grafo b) {
	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; i < b.size(); i++)
		{
			if(a[i][j] != b[i][j]) return false;
		}
		
	}
	return true;
}

void imprimirGrafo(Grafo g) {
	cout << "   ";
	for(int i = 0; i< g.size(); i++) {
		cout << i << "\t";
	}
	cout << "\n";
	cout << "  ";
	for(int i = 0; i< (g.size()-1)*4; i++) {
		cout << "__";
	}
	cout << "\n";

    for (int i = 0; i < g.size(); i++)
    {
        cout << i << "| ";
        for (int j = 0; j < g[i].size(); j++)
        {
            cout << g[i][j] << "\t\n"[j == g.size() - 1]; 
        }
    }
}

void conectar(Grafo &g, int i, int j, int pesoDeLaArista) {
	g[i][j] = pesoDeLaArista;
	g[j][i] = pesoDeLaArista;
}

void desconectar(Grafo &g, int i, int j) {
	g[i][j] = -1;
	g[j][i] = -1;
}

bool todosVisitados(vector<bool> visitado) {
	bool res = true;

	for(int i = 0; i < visitado.size() ; i++) {
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

void vecinos(Grafo g, int i, int &deDondeVengo, int &aDondeVoy) {
	deDondeVengo = -1;
	aDondeVoy = -1;

	for (int j = 0; j < g.size(); j++){
		if(g[i][j] != -1){
			if(deDondeVengo == -1) {
				deDondeVengo = j;
			} else {
				aDondeVoy = j;
				j = g.size();
			}
		}
	}
}

bool esta(int elem, vector<int> v) {
	for (int i = 0; i < v.size(); i++){
		if(elem == v[i]) {
			return true;
		}
	}

	return false;
}

//precondicion: g es hamiltoniano y cualquier arista que no sea parte del ciclo hamilt. debe valer -1.
vector<int> convertirAListaDeNodos(Grafo g) {
	// este algoritmo se basa FUERTEMENTE en la idea de que todo nodo en un ciclo hamilt 
	// tiene 2 y solo 2 adyacentes, a uno lo llamo "desde" y al otro "hasta".

	//la idea basica es moverme hacia el adyacente que no me haya movido ya, es decir,
	//moverme hacia el adyacente que !esta(ady, recorridos). el adyacente puede ser desde o hasta.
	//si tanto desde como hasta ya los recorri entonces termine, le di la vuelta al ciclo.

	int n = g.size();
	vector<int> recorridos;
	int desde = 0;
	int hasta = 0;
	bool termine = false;

	while (!termine) {
		if(!esta(desde, recorridos)) {
			recorridos.push_back(desde);
			vecinos(g, desde, desde, hasta);
		} else if (!esta(hasta, recorridos)) {
			recorridos.push_back(hasta);
			vecinos(g, hasta, desde, hasta);
		} else {
			termine = true;
		}
	}

	return recorridos;
}

Grafo convertirAGrafo(vector<int> padre, Grafo g){
	Grafo res(g.size(), vector<Peso>(g.size(), -1));

	for(int i = 1; i < padre.size(); i++) {
		conectar(res, padre[i], i, g[padre[i]][i]);
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

	while(!todosVisitados(visitado)) {
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

void DFSAux(Grafo g, int v,vector<bool> &visitados,vector<int> &orden) {
    visitados[v] = true;
    orden.push_back(v);

    for (int i = 0; i < g[v].size(); i++){
        if (g[v][i] >= 0 && !visitados[i]) {
            DFSAux(g,i,visitados,orden);
        } 
    }
}

// Dado un grafo G devuelve el orden en el que recorre los nodos sin repetir
vector<int> DFS(Grafo g,int v) {
    vector<bool> visitados =  vector<bool>(g.size(),false);
    vector<int> orden = vector<int>();

    DFSAux(g,v,visitados,orden);

    return orden;
}