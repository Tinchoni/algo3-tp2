#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 18:52:43 2020

@author: pablo
"""
from general import *

inp_ari = "--algoritmo Tabu --solInicial AGM --itParada 50 --tipoMemoria aristas --tamanioMemoria %i"
out_ari = dict()
inp_sol = "--algoritmo Tabu --solInicial AGM --itParada 50 --tipoMemoria soluciones --tamanioMemoria %i"
out_sol = dict()

grafos = ["gr21", "gr48", "gr96", "gr202"]#, "gr431"]

for nombre in grafos:
	out_ari[nombre] = []
	out_sol[nombre] = []
	gra = cargarGrafo_tsp("optimos/%s.tsp"%nombre)
	
	memorias = list(range(1, 71, 1))
	for M in memorias:
		out_ari[nombre].append( tprun(inp_ari%M, gra) )
		if not out_ari[nombre][-1].verificar(gra):
			raise Exception("Ups!")
		
		out_sol[nombre].append( tprun(inp_sol%M, gra) )
		if not out_sol[nombre][-1].verificar(gra):
			raise Exception("Ups!")

with open("exp5.pkl", 'wb') as f:
	pickle.dump((grafos, out_ari, out_sol), f)

#%%
with open("exp5.pkl", 'rb') as f:
	(grafos, out_ari, out_sol) = pickle.load(f)

#%%
c=0
plt.figure(1)
for nombre in grafos:
	ts = np.array( [x.tiempo for x in out_ari[nombre]] )/1000
	plt.plot(memorias, ts, '-C%i'%c, label=nombre)
	
	ts = np.array( [x.tiempo for x in out_sol[nombre]] )/1000
	plt.plot(memorias, ts, '--C%i'%c)
	c += 1
	
plt.xlabel('Memoria tabú')
plt.ylabel('Tiempo [s]')
plt.xlim([memorias[0], memorias[-1]])

#M = max( [x.tiempo for x in out_ari["gr202"]] )/1000
#plt.ylim([0, M])
plt.legend(title="Grafo")

plt.savefig('tabu_complejidad_memoria.pdf')

c=0
plt.figure(2)

for nombre in ["gr48", "gr202"]:
	cs = np.array( [x.costo for x in out_ari[nombre]] )/costos_optimos[nombre]
	plt.plot(memorias[:60], cs[:60], '-C%i'%c, label=nombre)
	
	cs = np.array( [x.costo for x in out_sol[nombre]] )/costos_optimos[nombre]
	plt.plot(memorias[:60], cs[:60], '--C%i'%c)
	c += 1
	
plt.xlabel('Memoria tabú')
plt.ylabel('Costo del ciclo hallado (relativo al óptimo)')
plt.xlim([memorias[0], memorias[60]])
plt.legend(title="Grafo")
plt.savefig('tabu_costo_memoria.pdf')