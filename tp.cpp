#include "common.h"
#include "grafo.h"
#include "heuristicas.h"
#include "argparse.hpp"
#include <chrono>

//#define CATCH_CONFIG_RUNNER
//#include "catch.hpp"

int main(int argc, const char** argv) {
    // freopen("completo100.txt", "r", stdin);

    //ArgParser
    ArgumentParser parser;


    parser.addArgument("-a","--algoritmo",1,false);


    //Parametros para TABU Search
    parser.addArgument("-s","--solInicial",1);
    parser.addArgument("-m","--tamanioMemoria",1);
    parser.addArgument("-s","--tipoMemoria",1);
    parser.addArgument("-p","--criterioParada",1);
    parser.addArgument("-i","--itParada",1);
    //Valido Parametros
    parser.parse(argc, argv);

    Grafo g = leerGrafo();
    Hamiltoniano res;


    string algo = parser.retrieve<string>("algoritmo");

    auto start = chrono::steady_clock::now();

    if (algo == "VecinoMasCercano") {
        res = heuristicaVecinoMasCercano(g,0);
    } else if (algo == "Insercion") {
        res = heuristicaDeInsercion(g);
    } else if (algo == "AGM") {
        res = heuristicaAGM(g);
    } else if (algo == "Tabu"){

        // Que algoritmo uso para la solucion inicial? Default: AGM
        string algoInicial = parser.retrieve<string>("solInicial");
        auto solInicial = heuristicaAGM;

        if (algoInicial == "Insercion") {
            solInicial = heuristicaDeInsercion;
        }  else if (algoInicial == "VecinoMasCercano")  {
            solInicial = [](Grafo &g){return heuristicaVecinoMasCercano(g,0);};
        } else if (algoInicial == "Hardcoded") {
            solInicial = solucionHardcoded;
        } else if(algoInicial != "AGM") {
            solInicial = NULL;
            cerr << "Mala invocacion, la solInicial debe ser una de {Insercion, VecinoMasCercano, Hardcoded, AGM}" << endl;
        }

        // Qué criterio de parada uso? Default: cantIteraciones -- Posibles {cantIteraciones,cantIteracionesSinMejora}
        string argCriterioParada = parser.retrieve<string>("criterioParada");

        // Cuántas iteraciones? Default: 500
        string argIter = parser.retrieve<string>("itParada");
        int itParada;
        if (argIter != "") {
            itParada = stoi(parser.retrieve<string>("itParada"));
        } else {
            itParada = 500;
        }

        string arMemoria = parser.retrieve<string>("tamanioMemoria");

        int tamanioMemoria = 50;
        if(arMemoria != "") {
            tamanioMemoria = stoi(parser.retrieve<string>("tamanioMemoria"));
        }

        string tipoMemoria = parser.retrieve<string>("tipoMemoria");

        //para tabu vuelvo a tomar el tiempo acá para no tomar en cuenta el tiempo que me lleva parsear todos los paramettros
        start = chrono::steady_clock::now();

        if(tipoMemoria == "soluciones") {
            res = heuristicaTabuSolucionesExploradas(
                    g,
                    solInicial,
                    argCriterioParada,
                    itParada,
                    tamanioMemoria);
        } else if (tipoMemoria == "aristas") {
            res = heuristicaTabuAristasIntercambiadas(
                    g,
                    solInicial,
                    argCriterioParada,
                    itParada,
                    tamanioMemoria );
        } else {
            cerr << "Mala invocacion, el tipoMemoria debe ser uno de {soluciones, aristas}" << endl;
        }
    }


    auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << total_time << endl;
    imprimirHamiltoniano(res,g);

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
