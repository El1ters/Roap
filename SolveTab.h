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

void SolveTab(int **tabuleiro,char *mode,int *def,int * sec,int *dim,FILE *fp1);
int BFS(int *inicial,int *final,int **tabuleiro,int *dim);

#endif