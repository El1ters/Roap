#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "Graph.h"

Graph* GraphInit(int V){
    int v;
    Graph *G = malloc(sizeof(Graph));
    if(G == NULL)
        exit(0);
    G->V = V;
    G->E = 0;
    if((G->adj = (Node**)malloc(sizeof(Node*) * V)) == NULL)
        exit(0);
    for(v = 0; v < V;v++)
        G->adj[v] = NULL;

    return G;
}

void GraphInsertE(Graph *G,int v_inicial,int v_final){
    G->adj[(v_inicial * -1) - 2] = New(v_final,G->adj[(v_inicial * -1) - 2]);
    G->adj[(v_final *-1) - 2] = New(v_inicial,G->adj[(v_final *-1) - 2]);
    G->E++;
}

Node *New(int v,Node *next){
    Node *x;
    if((x = (Node*)malloc(sizeof(Node))) == NULL){
        exit(0);
    }
    x->V = v;
    x->min = 100;
    x->next = next; 
    return x;
}

int Verify(Graph *G,int v,int w){
    Node *aux;
        aux = G->adj[(v * -1) - 2];
        while(aux != NULL){
            if(aux->V == w)
                return 0;
            aux = aux->next;
        }
    return 1;
}

void ChangeMin(Graph *G,int v, int w, int value){
    Node *aux;
        aux = G->adj[(v * -1) - 2];
        while(aux != NULL){
            if(aux->V == w){
                if(value < aux->min){
                    printf("%d %d %d->",v,w, aux->min);
                    aux->min = value;
                    printf("%d\n",value);
                    return;
                }    
            }
            aux = aux->next;
        }
}

Graph *CreateGraph(int **tabuleiro)