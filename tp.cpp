#include "common.h"
#include "grafo.h"
#include "heuristicas.h"

//#define CATCH_CONFIG_RUNNER
//#include "catch.hpp"

int main(int argc, char** argv) {
    freopen("completo100.txt", "r", stdin);
    
    bool no_tests = false;
    for(int j=1; j<argc; j++){
       if(string(argv[j]) == "--no-tests"){no_tests= true;}
    }

    Grafo G = leerGrafo();
    cout << "El grafo leido es:\n";
    imprimirGrafo(G);

    // Grafo elAGM = AGM(G);
    // cout << "\n\nY su AGM es: \n";
    // imprimirGrafo(elAGM);

    Hamiltoniano elCircHamiltoniano = heuristicaVecinoMasCercano(G, 0);
    cout << "\n\nY su Hamiltoniano por vecino mas cercano comenzando en v1 es: \n";
    imprimirHamiltoniano(elCircHamiltoniano, G);

    elCircHamiltoniano = heuristicaAGM(G);
    cout << "\n\nY su Hamiltoniano por AGM: \n";
    imprimirHamiltoniano(elCircHamiltoniano, G);


    elCircHamiltoniano = heuristicaDeInsercion(G);
    cout << "\n\nY su Hamiltoniano por insercion es: \n";
 	imprimirHamiltoniano(elCircHamiltoniano, G);

    elCircHamiltoniano = heuristicaTabuSolucionesExploradas(
                        G, 
                        heuristicaAGM, 
                        [](int cantIteraciones, int cantIteracionesSinMejora){ return cantIteraciones < 1000; },
                        10,
                        obtenerSubVecindad );
    cout << "\n\nY su Hamiltoniano por tabu con memoria de sols exploradas es: \n";
    imprimirHamiltoniano(elCircHamiltoniano, G);

    //if(!no_tests) {
    //    Catch::Session().run();
    //}

    return 0;
}

/*
TEST_CASE("Instancia ejemplo", "[Goloso - Vecino mas cercano]") {    
    freopen( "entradaEjemplo", "r", stdin );
    
    Grafo g = leerGrafo();
    
    Grafo elCircHamiltoniano = heuristicaVecinoMasCercano(g, 0);
    
    Grafo deberiaValer(g.size(), vector<Peso>(g.size(), -1));
    conectar(deberiaValer, 0, 1, 10);
    conectar(deberiaValer, 1, 3, 25);
    conectar(deberiaValer, 3, 2, 30);
    conectar(deberiaValer, 2, 0, 15);
    for (size_t i = 0; i < g.size(); i++)
    {
        deberiaValer[i][i] = 0;
    }

    
    REQUIRE(esIgual(deberiaValer, elCircHamiltoniano));

    elCircHamiltoniano = heuristicaVecinoMasCercano(g, 1);
    
    deberiaValer = Grafo(g.size(), vector<Peso>(g.size(), -1));
    conectar(deberiaValer, 1, 0, 10);
    conectar(deberiaValer, 0, 2, 15);
    conectar(deberiaValer, 2, 3, 30);
    conectar(deberiaValer, 3, 1, 25);
    for (size_t i = 0; i < g.size(); i++)
    {
        deberiaValer[i][i] = 0;
    }

    REQUIRE(esIgual(deberiaValer, elCircHamiltoniano));

    elCircHamiltoniano = heuristicaVecinoMasCercano(g, 2);
    
    deberiaValer = Grafo(g.size(), vector<Peso>(g.size(), -1));
    conectar(deberiaValer, 2, 0, 15);
    conectar(deberiaValer, 0, 1, 10);
    conectar(deberiaValer, 1, 3, 25);
    conectar(deberiaValer, 3, 2, 30);
    for (size_t i = 0; i < g.size(); i++)
    {
        deberiaValer[i][i] = 0;
    }

    REQUIRE(esIgual(deberiaValer, elCircHamiltoniano));

    elCircHamiltoniano = heuristicaVecinoMasCercano(g, 3);
    
    deberiaValer = Grafo(g.size(), vector<Peso>(g.size(), -1));
    conectar(deberiaValer, 3, 0, 20);
    conectar(deberiaValer, 0, 1, 10);
    conectar(deberiaValer, 1, 2, 35);
    conectar(deberiaValer, 2, 3, 30);
    for (size_t i = 0; i < g.size(); i++)
    {
        deberiaValer[i][i] = 0;
    }

    REQUIRE(esIgual(deberiaValer, elCircHamiltoniano));
}*/