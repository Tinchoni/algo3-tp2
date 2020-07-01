#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 22:54:06 2020

@author: pablo
"""
from matplotlib import pyplot as plt
from general import *


opts = "--algoritmo AGM"

Ns = list(range(50, 501, 50)) #N del grafo
ts = []

for N in Ns:
	grafo = grafoRandomUniforme(N, (1,20)) #aristas de peso 1 a 300
	
	out = tprun(opts, grafo).tiempo #no lo verifico
	
	ts.append(tiempo/1000.) #segundos

plt.plot(Ns, ts, '*')
plt.title("Test :: AGM")
plt.xlabel("Número de nodos [N]")
plt.ylabel("Tiempo [s]")