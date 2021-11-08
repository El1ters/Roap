#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "Graph.h"
#include "SolveTab.h"

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
    x->min = __INT_MAX__;
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
                    aux->min = value;
                    return;
                }    
            }
            aux = aux->next;
        }
}
void FreeGraph(Graph *G,int different_cells){
    Node *aux;
    for(int i = 0; i < different_cells; i++){
        while(G->adj[i] != NULL){
            aux = G->adj[i];
            G->adj[i] = G->adj[i]->next;
            free(aux);
        }
    }
    free(G->adj);
    free(G);
}

void FillBoard(int **tabuleiro,int *different_cells,int *dim,int number_of_lines){
    Coord *queue = malloc((dim[0] * dim[1] - number_of_lines) * sizeof(queue));
    int sub = -2;
    int f[2] = {0,0};
    for(int a = 0;a < dim[0];a++){
        for(int b = 0;b < dim[1];b++){
            if(tabuleiro[a][b] == 0){
                f[0] = a;
                f[1] = b;
                BFS(f,tabuleiro,dim,number_of_lines,sub,queue);
                sub--;
                (*different_cells)++;
            }
        }
    }
    free(queue);
}

Graph *CreateGraph(int **tabuleiro,int *dim,int different_cells){
    Graph *G = GraphInit(different_cells);
    int room_value[2] = {0,0};
    int f[2];
    for(int c = 0;c < dim[0];c++){
        for(int d = 0; d < dim[1];d++){
            if(tabuleiro[c][d] > -1){
                f[0] = c;
                f[1] = d;
                    if(Break(tabuleiro,f,dim) == 1){
                        if(c + 1 < dim[0] && c - 1 >= 0){
                            room_value[0] =  tabuleiro[c + 1][d];
                            room_value[1] = tabuleiro[c - 1][d];
                                if(tabuleiro[c + 1][d] < -1 && tabuleiro[c - 1][d] < -1){    
                                    if(G->adj[(room_value[0] *-1) - 2] == NULL || G->adj[(room_value[1] *-1) - 2] == NULL ){
                                        GraphInsertE(G,tabuleiro[c + 1][d],tabuleiro[c - 1][d]);   
                                            G->adj[(tabuleiro[c + 1][d] * -1) -2]->min = tabuleiro[c][d];
                                            G->adj[(tabuleiro[c - 1][d] * -1) -2]->min = tabuleiro[c][d];
                                    }else{
                                        if(Verify(G,tabuleiro[c - 1][d],tabuleiro[c + 1][d]) == 1){
                                            GraphInsertE(G,tabuleiro[c + 1][d],tabuleiro[c - 1][d]);
                                            }                 
                                        }
                                        ChangeMin(G,tabuleiro[c - 1][d],tabuleiro[c + 1][d],tabuleiro[c][d]);
                                        ChangeMin(G,tabuleiro[c + 1][d],tabuleiro[c - 1][d],tabuleiro[c][d]);
                                    }  
                                }
                        if(d + 1 < dim[1] && d - 1 >= 0){
                            room_value[0] = tabuleiro[c][d - 1];
                            room_value[1] = tabuleiro[c][d + 1];
                                if(tabuleiro[c][d + 1] < -1 && tabuleiro[c][d - 1] < -1){  
                                    if(G->adj[(room_value[0] *-1) - 2] == NULL || G->adj[(room_value[1] *-1) - 2] == NULL ){
                                        GraphInsertE(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1]);
                                        G->adj[(tabuleiro[c][d + 1] * -1) -2]->min = tabuleiro[c][d];
                                        G->adj[(tabuleiro[c][d - 1] * -1) -2]->min = tabuleiro[c][d];
                                    }else{
                                        if(Verify(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1]) == 1){
                                            GraphInsertE(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1]);
                                        }
                                    }
                                    ChangeMin(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1],tabuleiro[c][d]);
                                    ChangeMin(G,tabuleiro[c][d - 1],tabuleiro[c][d + 1],tabuleiro[c][d]); 
                                }  
                        }
                    }
            }
        }
    }
    return G;
}