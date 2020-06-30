# algo3-tp2
* link al informe https://es.overleaf.com/8296535711jqzxvmdcqnkf

## Instrucciones de uso

./tp --algoritmo {VecinoMasCercano,Insercion,AGM,Tabu} 
si se usa tabú:
--solInicial {VecinoMasCercano,Insercion,AGM} (Default AGM)
--tamanioMemoria (Default 50)
--criterioParada {cantIteraciones,cantIteracionesSinMejora} (Default cantIteraciones)
--itParada (Default 500) Desc: threshold para el criterio de parada 

EJ:
./tp -a Tabu --solInicial Insercion --itParada 100  -m 100 < completo100.txt