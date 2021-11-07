/******************************************************************************
 * NOME
 *   SolveTab.h
 *
 * DESCRICAO
 *   Contem os cabecalhos das funcoes utilizadas no SolveTab.h.
 *
 ******************************************************************************/
#ifndef SOLVETAB
#define SOLVETAB

#include <stdio.h>
#include "ReadFile.h"

/*
Estrutura que guarda coordenadas de celulas do labirinto. */
typedef struct Coord{
    int x;
    int y;
}Coord;

int Break(int **tabuleiro,int *def,int *dim);
void BFS(int *inicial,int **tabuleiro,int *dim,int number_of_lines,int value);
/*void Init(int pSize);
void Push(Coord pI);
int IsEmpty();
Coord Pop();*/

#endif