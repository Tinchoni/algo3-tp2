# algo3-tp2
* link al informe https://es.overleaf.com/8296535711jqzxvmdcqnkf

## Instrucciones de uso

./tp --algoritmo {Hardcoded, VecinoMasCercano, Insercion, AGM, Tabu} 
si se usa tabú:
--solInicial {Hardcoded, VecinoMasCercano, Insercion, AGM}
--tamanioMemoria (Default 50)
--criterioParada {cantIteraciones,cantIteracionesSinMejora} (Default cantIteraciones)
--itParada (Default 500) Desc: umbral para el criterio de parada 
--tipoMemoria {soluciones, aristas}

EJ:
./tp -a Tabu --solInicial Insercion --itParada 100  -m 100 < completo100.txt