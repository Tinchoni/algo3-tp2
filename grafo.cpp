#include "grafo.h"


Grafo leerGrafo(bool dirigido) {
    int n, m;
    cin >> n >> m;
    Grafo G(n, vector<Vecino>());

    for (int i = 0; i < m; i++) {
        int v, w, peso;
        cin >> v >> w >> peso;
        G[v].push_back(Vecino(w, peso));
        if (!dirigido) {
            G[w].push_back(Vecino(v, peso));
        }
    }
    return G;
}