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