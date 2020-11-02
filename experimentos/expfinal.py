#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  2 18:52:43 2020

@author: pablo
"""
from general import *


inp = "--algoritmo Tabu --solInicial AGM --itParada 50 --criterioParada itSinMejora --tipoMemoria aristas --tamanioMemoria 50 --probaDescarte 50"
out = dict()

grafos = ["a280","bayg29","berlin52","brg180","ch130","ch150","eil51","eil76","fri26","gr120","gr202","gr96","kroc100","krod100","lin105","pa561","pr76","rd100","st70","gr666"]


for nombre in grafos:
	out[nombre] = []
	gra = cargarGrafo_tsp("optimos/%s.tsp"%nombre)
	out[nombre].append( (nombre, tprun(inp, gra) ) )
	f=open("expfinal.csv", "a+")
	f.write(nombre+','+str(out[nombre][0][1].costo)+', \n') 
	f.close()

