/********************************************************************************
 * NOME
 *   Dijkstra.h
 *
 * DESCRICAO
 *   Contem os cabecalhos das funcoes utilizadas no Dijkstra.c. e a estrutura dos 
 *   nos da nossa lista de espera utilizada no algoritmo Dijkstra.
 *
 ********************************************************************************/
#ifndef DIJKSTRA
#define DIJKSTRA

#include <stdio.h>
#include "Graph.h"
#include "ReadFile.h"

/* Estrutura dos nos da nossa lista de espera utilizada no algoritmo Dijkstra. */
typedef struct queue
{
    int vertice;
    struct queue *next;
    
}Queue;

void Dijkstra(Graph *G,int different_cells,int start,int finish,FILE *fp1);
void CreateVertice(int v,Queue **head);
void print_queue(Queue *head);
Queue *PopFirst(Queue **head,int *dist);
void FreeQueue(Queue **head);
void PrintBreak(Graph *G, int vertice,int b);


#endif