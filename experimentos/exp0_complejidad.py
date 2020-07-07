#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 19:56:38 2020

@author: pablo
"""

from matplotlib import pyplot as plt
from scipy.optimize import curve_fit
from general import *


i_agm = "--algoritmo AGM";
o_agm = []
i_vmc = "--algoritmo VecinoMasCercano"
o_vmc = []
i_ins = "--algoritmo Insercion"
o_ins = []

Ns = list(range(20, 721, 100)) #N del grafo
ts = []

for N in Ns:
	grafo = grafoRandomUniforme(N, (1, 50)) #aristas de peso 1 a 50
	
	for entrada, salida in zip((i_agm, i_vmc, i_ins), (o_agm, o_vmc, o_ins)):
		salida.append( tprun(entrada, grafo) )
		
		if not salida[-1].verificar(grafo):
			raise Exception("Ups!")
		
#%%
t_agm = np.array( [x.tiempo for x in o_agm] )
t_vmc = np.array( [x.tiempo for x in o_vmc] )
t_ins = np.array( [x.tiempo for x in o_ins] )

plt.plot(Ns, np.log(t_agm), 'oC0', label='AGM')
plt.plot(Ns, np.log(t_vmc), 'oC1', label='Vecino más cercano')
plt.plot(Ns, np.log(t_ins), 'oC2', label='Inserción')

P = 3
xs = np.linspace(Ns[0], Ns[-1], 200)
fit_agm = curve_fit(lambda n,a,b: a+b*np.log(n),  Ns[P:],  np.log(t_agm[P:]))
plt.plot(xs, fit_agm[0][0] + fit_agm[0][1]*np.log(xs), '--C0', label='%0.2f log(n)'%fit_agm[0][1])

fit_vmc = curve_fit(lambda n,a,b: a+b*np.log(n),  Ns[P:],  np.log(t_vmc[P:]))
plt.plot(xs, fit_vmc[0][0] + fit_vmc[0][1]*np.log(xs), '--C1', label='%0.2f log(n)'%fit_vmc[0][1])

fit_ins = curve_fit(lambda n,a,b: a+b*np.log(n),  Ns[P:],  np.log(t_ins[P:]))
plt.plot(xs, fit_ins[0][0] + fit_ins[0][1]*np.log(xs), '--C2', label='%0.2f log(n)'%fit_ins[0][1])

plt.ylabel("log( Tiempo [s] )")
plt.xlabel("Número de nodos [N]")
plt.legend()
plt.savefig('complejidad.pdf')

plt.figure()
c_agm = np.array( [x.costo for x in o_agm] )/np.array(Ns)/25
c_vmc = np.array( [x.costo for x in o_vmc] )/np.array(Ns)/25
c_ins = np.array( [x.costo for x in o_ins] )/np.array(Ns)/25

plt.plot(Ns, c_agm, 'oC0', label='AGM')
plt.plot(Ns, c_vmc, 'oC1', label='Vecino más cercano')
plt.plot(Ns, c_ins, 'oC2', label='Inserción')

plt.ylabel("Costo medio por nodo del ciclo normaizado")
plt.xlabel("Número de nodos [N]")
plt.legend()
plt.savefig('costo_por_ciclo.pdf')
