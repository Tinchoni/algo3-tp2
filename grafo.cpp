#include "grafo.h"


Grafo leerGrafo(bool dirigido) {
    int n, m;
    cin >> n >> m;
    Grafo G(n, vector<Vecino>());

    for (int i = 0; i < m; i++) {
        int v, w, peso;
        cin >> v >> w >> peso;
        G[v - 1].push_back(Vecino(w - 1, peso));
        if (!dirigido) {
            G[w - 1].push_back(Vecino(v-1, peso));
        }
    }
    return G;
}

void imprimirGrafo(Grafo g) {
    for (int i = 0; i < g.size(); i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < g[i].size(); j++)
        {
            cout << "(" << g[i][j].dst + 1 << ", " << g[i][j].peso << ") - "; 
        }
        cout << endl;
    }
    
}