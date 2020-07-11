#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 19:56:38 2020

@author: pablo
"""

from general import *


i_agm = "--algoritmo AGM";
o_agm = []
o_agm_euclideo = []
i_vmc = "--algoritmo VecinoMasCercano"
o_vmc = []
i_ins = "--algoritmo Insercion"
o_ins = []

Ns = list(range(20, 1221, 50)) #N del grafo
ts = []

for N in Ns:
	grafo = grafoRandomUniforme(N, (1, 500)) #aristas de peso 1 a 500
	
	for entrada, salida in zip((i_agm, i_vmc, i_ins), (o_agm, o_vmc, o_ins)):
		salida.append( tprun(entrada, grafo) )
		
		if not salida[-1].verificar(grafo):
			raise Exception("Ups!")
	
	grafo = grafoRandomEuclideo(N, 500)
	o_agm_euclideo.append( tprun(i_agm, grafo) )
	
		
#%%
#plt.rcParams['legend.title_fontsize'] = 'xx-small'
plt.figure(figsize= (8,8))
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
plt.savefig('complejidad_temporal.pdf')

plt.figure()
c_agm = np.array( [x.costo for x in o_agm] )/np.array(Ns)
c_agm_euclideo = np.array( [x.costo for x in o_agm_euclideo] )/np.array(Ns)
c_vmc = np.array( [x.costo for x in o_vmc] )/np.array(Ns)
c_ins = np.array( [x.costo for x in o_ins] )/np.array(Ns)

plt.plot(Ns, c_agm_euclideo, 'xC0', mew=3	, ms=8, label='AGM - grafo euclideo')
plt.plot(Ns, c_agm, 'oC0', label='AGM')
plt.plot(Ns, c_vmc, 'oC1', label='Vecino más cercano')
plt.plot(Ns, c_ins, 'oC2', label='Inserción')

plt.ylabel("Costo medio por arista del ciclo")
plt.xlabel("Número de nodos [N]")
plt.legend()
plt.savefig('costo_por_ciclo.pdf')
