#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 22:54:06 2020

@author: pablo
"""
from matplotlib import pyplot as plt
from general import *

opt_agm = "--algoritmo AGM"
opt_vmc = "--algoritmo VecinoMasCercano"
opt_tabu = "--algoritmo Tabu --solInicial Insercion --itParada 1000 --tamanioMemoria 30"

iteraciones = 1
c_tabu = []
c_vmc  = []
c_agm  = []

for _ in range(iteraciones):
	grafo = grafoRandomUniforme(150, (1,50)) #genera grafo random de 150 vertices
	
	out_tabu = tprun(opt_tabu, grafo)
	out_vmc = tprun(opt_vmc, grafo)
	out_agm = tprun(opt_agm, grafo)
	
	if not (out_tabu.verificar(grafo) and out_vmc.verificar(grafo) and out_agm.verificar(grafo)):
		raise Exception("Algo no anda bien!")
	
	c_tabu.append(out_tabu.costo)
	c_vmc .append(out_vmc .costo)
	c_agm .append(out_agm .costo)
	
#%%
fig, ax = plt.subplots()

indices = np.arange(iteraciones)

ax.bar(indices, c_tabu, 0.3, label="Tabu")
ax.bar(indices+0.3, c_vmc, 0.3, label="VMC")
ax.bar(indices+0.6, c_agm, 0.3, label="AGM")

ax.set_xticks(indices + 0.3)
ax.set_xticklabels(["grafo %i"%x for x in (indices+1)])
ax.legend()

plt.title("Test :: Comparación 1")
plt.xlabel("Grafo aleatorio de 200 vértices")
plt.ylabel("Costo del ciclo")