#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 18:52:43 2020

@author: pablo
"""
from general import *

inp = "--algoritmo Tabu --solInicial AGM --itParada %i --tipoMemoria aristas --tamanioMemoria %i"
out = dict()

grafos = ["gr21"]#, "gr48", "gr96", "gr202"]#, "gr431"]

iters = list(range(1, 101, 5))
memos = list(range(1, 51, 5))

for nombre in grafos:
	out[nombre] = []
	gra = cargarGrafo_tsp("optimos/%s.tsp"%nombre)
	
	for i in range(len(iters)):
		for m in range(len(memos)):
			out[nombre].append( (i, m, tprun(inp%(iters[i], memos[m]), gra) ) )


with open("exp6.pkl", 'wb') as f:
	pickle.dump((grafos, out), f)

#%%
with open("exp6.pkl", 'rb') as f:
	(grafos, out) = pickle.load(f)

#%%
nombre = "gr21"

mat = np.zeros([len(iters), len(memos)])
for elem in out[nombre]:
	(i, m, costo) = (elem[0], elem[1], elem[2].costo)
	mat[i, m] = costo

mat = mat/costos_optimos[nombre]

plt.figure(1)
plt.pcolormesh(memos, iters, mat)
plt.colorbar()
plt.xlabel('\# Memoria')
plt.ylabel('\# Iteraciones')