#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 13:29:28 2020

@author: pablo
"""
import subprocess as sp
import numpy as np
import random
from math import factorial, log10
from decimal import Decimal

import pickle

from scipy.optimize import curve_fit

# configuracion de plots
from matplotlib import pyplot as plt
from matplotlib import rc, rcParams, axes
from matplotlib import axes as mplibAxes

rc('text', usetex=True)
rcParams['text.latex.preamble'] = [r'\boldmath']
#rc('font', family='serif', size=20, weight='bold')
rc('font', family='serif', size=14)
rcParams['axes.axisbelow'] = True
rcParams['lines.linewidth'] = 2
rc('axes', labelsize=18)
rc('xtick', labelsize=18)
rc('ytick', labelsize=18)
rcParams['figure.figsize'] = (8.0, 8.0)
rcParams['figure.dpi'] = 120

########

class grafo: #Define un digrafo de N vertices con nombres 0...N-1	
	def __init__(self, N, aristas):
		#Lo considero con las restricciones del TP de una
		if len(aristas) != N*(N-1)//2: #completo
			raise Exception("Gafo no completo!")
		
		# chequear que no haya aristas contradictorias
		for arista in aristas.keys():
			(i,j) = arista
			if (j,i) in aristas.keys():
				raise Exception("Gafo no válido!")
		
		# expando las aristas para facilitar las cosas
		self.aristas = dict()
		self.N = N
		
		# costos pueden ser útiles
		self.costos_aristas = []
		
		for arista in aristas.keys():
			(i,j) = arista
			peso = aristas[(i,j)]
			self.costos_aristas.append(peso)
			
			if i>=N or j>=N:
				raise Exception("Grafo no válido!")
			
			self.aristas[(i,j)] = peso
			self.aristas[(j,i)] = peso
	
	def costo_medio(self):
		return np.mean( list(self.aristas.values()) )
		
	def costo(self, camino):
		out = 0
		for i in range(len(camino)-1):
			out += self.aristas[(camino[i], camino[i+1])]
		return out
	
	def stdin(self):
		out = "%i %i\n"%(self.N, len(self.aristas)//2)
		
		for i in range(self.N):
			for j in range(i+1, self.N):
				peso = self.aristas[(i,j)]
				out += "%i %i %i\n"%(i, j, peso)
			
		return out
	
	
	def exportar(self, filename):
		with open(filename, 'w') as f:
			f.write(self.stdin())
	
	def Ec(self, r):
		n = self.N
		t1 = Decimal( factorial(n-1)//2 )
		t2 = Decimal( (r-1)**(n-1) )
		t3 = Decimal( (n-2)**(n-1) )
		t4 = Decimal(r/(n-1))
		out = ((t1 * t2) / t3 )*t4
		return  out
	
	def optimo_estimado(self):
		r = 1
		objetivo = 1.
		# caca search
		while( self.Ec(r) < objetivo):
			r += 1
		
		low = r-1
		upp = r
		val = -1
		while( abs(val-1) > 0.0001 ):
			r = (low + upp)/2
			val = self.Ec(r)
			if val<1.: low = r
			else: upp = r
		
		numero_aristas = int(self.N*r + 1)//2
		menos_costosas = sorted(self.costos_aristas)[:numero_aristas]
		
		return (r, sum(menos_costosas)/numero_aristas*self.N)
		

def cargarGrafo(filename):
	aristas = dict()
	with open(filename, 'r') as f:
		header = f.readline()
		[N, control] = [int(x) for x in header.rstrip('\n').split(' ')]
		
		for line in f:
			[i, j, peso] = [int(x) for x in line.rstrip('\n').split(' ')]
			aristas[(i, j)] = peso
			
	if len(aristas) != control:
		raise Exception("Archivo corrupto!")
	
	return grafo(N, aristas)



def grafoRandomDesconectado(Nvertices, alpha=0.5):
	Naristas = Nvertices*(Nvertices-1)//2
	
	#definir las aristas
	aristas = dict()
	for i in range(Nvertices-1):
		for j in range(i+1, Nvertices):
			if random.random() > alpha: #alpha grande significa más desconectado
				aristas[(i,j)] = random.randint(1, 5)
			else:
				aristas[(i,j)] = random.randint(100, 105)
	
	return grafo(Nvertices, aristas)


def grafoRandomUniforme(Nvertices, limite_pesos=(1,20)):
	Naristas = Nvertices*(Nvertices-1)//2
	
	#definir las aristas
	aristas = dict()
	for i in range(Nvertices-1):
		for j in range(i+1, Nvertices):
			aristas[(i,j)] = random.randint(limite_pesos[0], limite_pesos[1])
	
	return grafo(Nvertices, aristas)



def grafoRandomEuclideo(Nvertices, distancia_maxima=40):
	if (distancia_maxima//2+1)**2 < Nvertices:
		raise Exception("Necesito distancia")
	
	puntos = []
	#generar lista con las coordenadas posibles
	while(len(puntos)<Nvertices):
		x = random.randint(0, (distancia_maxima//2+1) )
		y = random.randint(0, (distancia_maxima//2+1) )
		if (x,y) not in puntos:
			puntos.append((x,y))
	
	
	#coordenadas = [(x, y) for x in range(distancia_maxima//2+1) for y in range(distancia_maxima//2+1)]
	#elijo los puntos
	#random.shuffle(coordenadas)
	#puntos = coordenadas[:Nvertices]
	
	#el peso va a ser la vieja y querida norma 1
	def norma1(a, b): return abs(a[0]-b[0]) + abs(a[1]-b[1])
	
	#defino el grafo
	aristas = dict()
	for i in range(Nvertices-1):
		for j in range(i+1, Nvertices):
			aristas[(i,j)] = norma1( puntos[i], puntos[j] )
	
	return grafo(Nvertices, aristas)



class tpout:
	def __init__(self, salida, tiempo):
		salida = salida.split('\n')
		[N, costo] = salida[0].split(' ')
		ciclo = salida[1].split(' ')[:-1]
		
		self.N = int(N)
		self.costo = int(costo)
		self.ciclo = [int(x) for x in ciclo]
		
		self.tiempo = float(tiempo)
		
		#Verificaciones elementales
		if self.N != len(self.ciclo):
			print("No coinciden los tamaños del ciclo!")
			return
		
		if len(set(self.ciclo)) != len(self.ciclo):
			print("Solución incorrecta, hay elementos repetidos!")
			return
		
	def verificar(self, grafo): #verificar si la solución es tal
		if self.N != grafo.N:
			print("La solución y el grafo tienen N distintos")
			return False
		
		cierre = (self.ciclo[-1], self.ciclo[0])
		if self.costo != grafo.costo(self.ciclo) + grafo.aristas[cierre]: #el out del ejecutable no cierra el ciclo
			print("El costo de la solución no coincide con el costo del camino sobre el grafo")
			return False
		
		return True
	
	
	def guardar(self, filename):
		with open(filename, 'wb') as f:
			pickle.dump(f, self)
		return
		
def tprun(string_opciones, grafo):
	print('[tprun] :: N = %i'%grafo.N)
	comando = ["../tp"] + string_opciones.split(' ')
	proc = sp.run(comando, input=grafo.stdin(), capture_output=True, encoding="utf-8")
	
	return tpout(proc.stdout, proc.stderr)


global memo
def dado(X, N, F):
	global memo
	memo = [[-1 for _ in range(N+1)] for _ in range(X+1)]
	
	#return dado_comp(X, N, F)
	return sum( [dado_comp(i, N, F) for i in range(X+1)])
	
def dado_comp(X, N, F):
	if N*F<X or X<N: return 0
	if N == 1: return 1
	
	if memo[X][N] == -1:
		memo[X][N] = 0
		for i in range(1, F+1):
			memo[X][N] += dado_comp(X-i, N-1, F)
	
	return memo[X][N]





import tsplib95

def cargarGrafo_tsp(filename):
	problema = tsplib95.load(filename)
	if problema.dimension > 2000:
		raise Exception("demasiado grande")
		
	nodos = list( problema.get_nodes() )
	N = len( nodos )
	
	
	aristas = dict()
	for i in range(N-1):
		for j in range(i+1, N):
			peso = problema.get_weight(*(nodos[i],nodos[j]))
			#chequeo
			if peso != problema.get_weight(*(nodos[j],nodos[i])):
				raise Exception("Es un digrafo!")
			
			aristas[(i, j)] = peso
	
	return grafo(N, aristas)

def cargarCiclo_tour(filename):
	with open(filename, 'r') as f:
		lineas = [x.strip('\n') for x in f.readlines()]
	
	ciclo = []
	for line in lineas:
		try:
			x = int(line)
		except:
			continue
		if x == -1:
			ciclo.append(ciclo[0])
			continue
		ciclo.append(x-1)
		
	return ciclo

# Esto estaba para  traducir a archivos de entrada del TP, pero me parece al pedo
#import os
#for filename in [x for x in os.listdir('grafos_test') if '.tsp' in x]:
#	print(filename)
#	try:
#		g = cargarGrafo_tsp('grafos_test/%s'%filename)
#		g.exportar('optimos/%s.txt'%filename[:-4])
#	except:
#		continue
	