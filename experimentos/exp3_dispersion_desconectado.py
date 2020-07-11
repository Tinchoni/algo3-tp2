#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 22:54:06 2020

@author: pablo
"""
from general import *


i_agm = "--algoritmo AGM";
o_agm = []
o_agm_euclideo = []
i_vmc = "--algoritmo VecinoMasCercano"
o_vmc = []
o_vmc_euclideo = []
i_ins = "--algoritmo Insercion"
o_ins = []
o_ins_euclideo = []

N = 100
alps = np.array(range(0, 300, 1))/300 #Dispersión
cs = []

for a in alps:
	#gra = grafoRandomUniforme(N, (1000-D, 1000+D)) #grafo de tamaño 100
	#gra = grafoRandomUniforme(N, (10000-D, 10000+D)) #grafo de tamaño 100
	#gra = grafoRandomEuclideo(N, D) #grafo de tamaño N
	gra = grafoRandomDesconectado(N, a) #grafo de tamaño N
	cs.append(gra.optimo_estimado()[1])
	
	for entrada, salida in zip((i_agm, i_vmc, i_ins), (o_agm, o_vmc, o_ins)):
	#for entrada, salida in zip((i_vmc, i_ins), (o_vmc, o_ins)):
		salida.append( tprun(entrada, gra) )
		
		if not salida[-1].verificar(gra):
			raise Exception("Ups!")
	
		
#%%

plt.figure()
cs = np.array(cs)
c_agm = np.array( [x.costo for x in o_agm] )
#c_agm_euclideo = np.array( [x.costo for x in o_agm_euclideo] )/np.array(Ns)
c_vmc = np.array( [x.costo for x in o_vmc] )
c_ins = np.array( [x.costo for x in o_ins] )


#plt.plot(Ns, c_agm_euclideo, 'xC0', mew=3	, ms=8, label='AGM - grafo euclideo')
#plt.plot(Ds, c_agm/cs, 'oC0', label='AGM')
plt.plot(alps, c_vmc/cs, 'oC1', label='Vecino más cercano')
plt.plot(alps, c_ins/cs, 'oC2', label='Inserción')
#plt.plot(alps, cs, 'ok', label='c')

plt.ylabel("Costo relativo al óptimo estimado")
plt.xlabel("Proporción de aristas caras $\\alpha$")
plt.legend(title='Costo del ciclo hallado')
plt.savefig('costo_dispersion_desconectado_n=%i.pdf'%N)