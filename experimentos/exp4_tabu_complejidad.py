#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 18:52:43 2020

@author: pablo
"""
from general import *

inp_iter = "--algoritmo Tabu --solInicial Hardcoded --itParada %i --tipoMemoria aristas --tamanioMemoria 50"
out_iter = []

inp_sol = "--algoritmo Tabu --solInicial Hardcoded --itParada 50 --tipoMemoria soluciones --tamanioMemoria %i"
out_sol = []

inp_ari = "--algoritmo Tabu --solInicial Hardcoded --itParada 50 --tipoMemoria aristas --tamanioMemoria %i"
out_ari = []

gra = grafoRandomUniforme(100, (1,50)) #genera grafo random de 100 vértices

iteraciones = list(range(10, 151, 10))
for I in iteraciones:
	out_iter.append( tprun(inp_iter%I, gra) )
	if not out_iter[-1].verificar(gra):
		raise Exception("Ups!")

memorias = list(range(10, 200, 10))
for M in memorias:
	out_sol.append( tprun(inp_sol%M, gra) )		
	if not out_sol[-1].verificar(gra):
		raise Exception("Ups!")
		
	out_ari.append( tprun(inp_ari%M, gra) )		
	if not out_ari[-1].verificar(gra):
		raise Exception("Ups!")

#%%
t_iter = np.array( [x.tiempo for x in out_iter] )/1000
t_sol = np.array( [x.tiempo for x in out_sol] )/1000
t_ari = np.array( [x.tiempo for x in out_ari] )/1000

plt.plot(iteraciones, t_iter, 'oC0', label='AGM')
plt.plot(memorias, t_sol, 'oC1', label='Vecino más cercano')
plt.plot(memorias, t_ari, 'oC2', label='Inserción')


plt.xlabel('\# iteraciones tabú')
plt.ylabel('Tiempo [s]')
plt.legend(title="Solución inicial")
#plt.savefig('complejidad_iteraciones.pdf')
ieufbili
plt.figure()
ax = plt.gca()

c_agm = np.array( [x.costo for x in o_agm] )/100
c_vmc = np.array( [x.costo for x in o_vmc] )/100
c_ins = np.array( [x.costo for x in o_ins] )/100

ax.axhline(gra.optimo_estimado()[1]/100, color='k', linestyle='--')

plt.plot(iteraciones, c_agm, 'oC0', label='AGM')
plt.plot(iteraciones, c_vmc, 'oC1', label='Vecino más cercano')
plt.plot(iteraciones, c_ins, 'oC2', label='Inserción')

plt.xlabel('\# iteraciones tabú')
plt.ylabel('Costo medio por nodo del camino hallado')
plt.legend(title="Solución inicial")
plt.savefig('costo_iteraciones.pdf')