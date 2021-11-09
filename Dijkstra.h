#ifndef DIJKSTRA
#define DIJKSTRA

#include "Graph.h"

typedef struct queue
{
    int vertice;
    struct queue *next;
    
}Queue;

void Dijkstra(Graph *G,int different_cells,int start,int finish);
void CreateVertice(int v,Queue **head);
void print_queue(Queue *head);
Queue *PopFirst(Queue **head,int *dist);


#endif