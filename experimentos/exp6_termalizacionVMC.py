#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 23:31:20 2020

@author: pablo
"""

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 18:52:43 2020

@author: pablo
"""
from matplotlib import pyplot as plt
from general import *

i_agm = "--algoritmo Tabu --solInicial AGM --itParada %i --tamanioMemoria 20"
o_agm = []
i_vmc = "--algoritmo Tabu --solInicial VecinoMasCercano --itParada %i --tamanioMemoria 20"
o_vmc = []
i_ins = "--algoritmo Tabu --solInicial Insercion --itParada %i --tamanioMemoria 20"
o_ins = []

iteraciones = list(range(1, 100, 1))

entrada = i_vmc
grafo = grafoRandomUniforme(50, (1, 50**3))

for I in iteraciones:
	
	o_vmc.append( tprun(entrada%I, grafo) )	
	if not o_vmc[-1].verificar(grafo):
		raise Exception("Ups!")


#%%

t_vmc = np.array( [x.tiempo for x in o_vmc] )/1000

plt.plot(iteraciones, t_vmc, 'oC1', label='Vecino más cercano')

plt.xlabel('# iteraciones tabú')
plt.ylabel('Tiempo [s]')
plt.legend(title="Solución inicial")
plt.savefig('iteraciones_vmc.pdf')


plt.figure()
c_vmc = np.array( [x.costo for x in o_vmc] )/50/grafo.costo_medio()

plt.plot(iteraciones, c_vmc, 'oC1', label='Vecino más cercano')

plt.xlabel('# iteraciones tabú')
plt.ylabel('Costo medio por nodo del camino hallado')
plt.legend(title="Solución inicial")
plt.savefig('costo_vmc.pdf')