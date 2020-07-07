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

iteraciones = list(range(15, 151, 15))

grafo = grafoRandomUniforme(200, (1,50)) #genera grafo random de 200 vertices

for I in iteraciones:
	
	for entrada, salida in zip((i_agm, i_vmc, i_ins), (o_agm, o_vmc, o_ins)):
		salida.append( tprun(entrada%I, grafo) )
		
		if not salida[-1].verificar(grafo):
			raise Exception("Ups!")


#%%

t_agm = np.array( [x.tiempo for x in o_agm] )/1000
t_vmc = np.array( [x.tiempo for x in o_vmc] )/1000
t_ins = np.array( [x.tiempo for x in o_ins] )/1000

plt.plot(iteraciones, t_agm, 'oC0', label='AGM')
plt.plot(iteraciones, t_vmc, 'oC1', label='Vecino más cercano')
plt.plot(iteraciones, t_ins, 'oC2', label='Inserción')

plt.xlabel('# iteraciones tabú')
plt.ylabel('Tiempo [s]')
plt.legend(title="Solución inicial")
plt.savefig('complejidad_iteraciones.pdf')

plt.figure()
c_agm = np.array( [x.costo for x in o_agm] )/200
c_vmc = np.array( [x.costo for x in o_vmc] )/200
c_ins = np.array( [x.costo for x in o_ins] )/200

plt.plot(iteraciones, c_agm, 'oC0', label='AGM')
plt.plot(iteraciones, c_vmc, 'oC1', label='Vecino más cercano')
plt.plot(iteraciones, c_ins, 'oC2', label='Inserción')

plt.xlabel('# iteraciones tabú')
plt.ylabel('Costo medio por nodo del camino hallado')
plt.legend(title="Solución inicial")
plt.savefig('costo_iteraciones.pdf')