#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 18:52:43 2020

@author: pablo
"""
from general import *

estimados = []
soluciones = []
ns = []
for nombre, solucion in costos_optimos.items():
	if type( solucion ) != int: continue
	
	print( nombre )
	try:
		gra = cargarGrafo_tsp("optimos/%s.tsp"%nombre)
		estimado = gra.optimo_estimado()[1]
	except:
		continue
	
	ns.append(gra.N)
	estimados.append(estimado)
	soluciones.append(solucion)
	
#with open("exp7.pkl", 'wb') as f:
#	pickle.dump((ns, estimados, soluciones), f)
	
	
#%%
with open("exp7.pkl", 'rb') as f:
	(ns, estimados, soluciones) = pickle.load(f)

plt.figure(figsize=(9,6))
plt.plot(ns, (np.array(soluciones)-np.array(estimados))/np.array(soluciones), 'ok')
plt.xlabel('Tamaño del grafo n')
plt.ylabel('Error relativo $(S-E)/S$')
plt.savefig("error_estimador.pdf")