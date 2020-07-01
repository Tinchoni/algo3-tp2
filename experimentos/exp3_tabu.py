#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 22:54:06 2020

@author: pablo
"""
from matplotlib import pyplot as plt
from general import *


opts = "--algoritmo Tabu --solInicial Insercion --itParada 100 --tamanioMemoria 20"

Ns = list(range(50, 151, 50)) #N del grafo
ts = []

for N in Ns:
	grafo = grafoRandomUniforme(N, (1,300)) #aristas de peso 1 a 300
	
	out = tprun(opts, grafo)
	if not out.verificar(grafo):
		raise Exception("El resultado es inconsistente!")
	
	ts.append(out.tiempo/1000.) #segundos

plt.plot(Ns, ts, '*')
plt.title("Test :: Tabu 1")
plt.xlabel("Número de nodos [N]")
plt.ylabel("Tiempo [s]")