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

N = 30
Ds = np.array(range(20, 10021, 50)) #Dispersión
cs = []

for D in Ds:
	gra = grafoRandomEuclideo(N, D) #grafo de tamaño N
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
plt.plot(Ds, c_agm/N, 'oC0', label='AGM')
plt.plot(Ds, c_vmc/N, 'oC1', label='Vecino más cercano')
plt.plot(Ds, c_ins/N, 'oC2', label='Inserción')
plt.plot(Ds, cs/N, '.k', label='Estimado (modelo prob.)')

plt.ylabel("Costo medio por arista del ciclo")
plt.xlabel("Tamaño de la grilla ($D$)")
plt.legend(title='Costo del ciclo hallado')
plt.savefig('costo_dispersion_AGM.pdf')