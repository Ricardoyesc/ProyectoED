#ifndef __CONECTA_H__
#define __CONECTA_H__
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int dificultad = 0;

struct nodo {
    char tablero[6][7];
    int valor;
    int siguiente;
    struct nodo *hijos[7];
};

struct nodo* generarJugadas(char tablero[6][7], int columna, int nivel, char color, struct nodo* padre);
bool gano(char tablero[6][7], char color);
bool tirar(char tablero[6][7], char color, int columna);
void imprimeTablero(char tablero[6][7]);
void imprimeArbol(struct nodo* raiz);
void liberarMemoria(struct nodo* raiz);
int minMax(int nivel, bool buscarMax, struct nodo* nodo);
int puntuarJugada(char tablero[6][7], int i);

#endif
