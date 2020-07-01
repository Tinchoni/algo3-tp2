#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 13:29:28 2020

@author: pablo
"""
import subprocess as sp
import numpy as np
import random

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
		
		for arista in aristas.keys():
			(i,j) = arista
			peso = aristas[(i,j)]
			
			if i>=N or j>=N:
				raise Exception("Grafo no válido!")
			
			self.aristas[(i,j)] = peso
			self.aristas[(j,i)] = peso
	
	
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
		
		

def grafoRandomUniforme(Nvertices, limite_pesos=(1,20)):
	Naristas = Nvertices*(Nvertices-1)//2
	
	#definir las aristas
	aristas = dict()
	for i in range(Nvertices-1):
		for j in range(i+1, Nvertices):
			aristas[(i,j)] = random.randint(limite_pesos[0], limite_pesos[1])
	
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
		
def tprun(string_opciones, grafo):
	print('[tprun] :: N = %i'%grafo.N)
	comando = ["../tp"] + string_opciones.split(' ')
	proc = sp.run(comando, input=grafo.stdin(), capture_output=True, encoding="utf-8")
	
	return tpout(proc.stdout, proc.stderr)

