#include "hamiltoniano.h"

int costo(Hamiltoniano &ciclo, Grafo &g) {
    int acum = 0;
    for (int i = 0; i < ciclo.size(); i++){
        acum += g[ciclo[i]][ciclo[((i+1) % ciclo.size())]];   
    }
    return acum;
}

//precondicion son dos circuitos hamilt del mismo grafo
bool sonIguales(Hamiltoniano &h1, Hamiltoniano &h2) {
    int offset = 0;
    while(h1[0] != h2[offset]) {
        offset++;
    }

    bool iguales = true;
    for (int i = 0; i < h1.size(); i++){
        iguales = iguales && h1[i] == h2[(offset + i) % h1.size()]; 
    }

    return iguales;
}

void imprimirHamiltoniano(Hamiltoniano &ciclo, Grafo &g) {
    cout << ciclo.size() << " " << costo(ciclo, g) << endl;
    for (auto elem: ciclo){
        cout << elem << " ";
    }
    cout << endl;
}