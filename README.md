## Instrucciones de uso

**Se debe poseer un archivo de texto que satisfaga el formato de entrada indicado en el enunciado. En el ejemplo de uso, utilizamos completo100.txt

./tp --algoritmo {Hardcoded, VecinoMasCercano, Insercion, AGM, Tabu}

**Si se usa Tabú:

--solInicial {Hardcoded, VecinoMasCercano, Insercion, AGM}
--tamanioMemoria (Default 50)
--tipoMemoria {soluciones, aristas}
--criterioParada {cantIteraciones,cantIteracionesSinMejora} (Default cantIteraciones)
--itParada (Default 500) Descripción: umbral para el criterio de parada 
--probaDescarte (Default 80) Descripción: valor entre 0 y 100 que indica el porcentaje de vecindad descartada.

**Ejemplo:
./tp --algoritmo Tabu --solInicial Insercion --tamanioMemoria 60 --tipoMemoria aristas --criterioParada cantIteraciones --itParada 100 --probaDescarte 60 < completo100.txt
