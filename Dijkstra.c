#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "Dijkstra.h"

#define p(a) ((a*-1) - 2)

void Dijkstra(Graph *G,int different_cells,int start,int finish){
    /*fazer alocaçao depois*/
    Queue *head_queue = NULL;
    Queue *current = NULL;
    Node *aux_q;
    int aux;
    int *dist = malloc(sizeof(int) * different_cells);
    int *st = malloc(sizeof(int) * different_cells);
    int *removed = malloc(sizeof(int) * different_cells);
    for(int i = different_cells - 1; i >=0 ;i--){
        dist[i] = __INT_MAX__;
        st[i] = -1;
        removed[i] = 0;
        CreateVertice(i,&head_queue);
    }
    dist[0] = 0;
    while(head_queue != NULL){
        current = PopFirst(&head_queue,dist);
        aux = current->vertice;
        removed[p(aux)] = 1;
        free(current);
            for(aux_q = G->adj[p(aux)];aux_q != NULL; aux_q = aux_q->next){
              if(removed[p(aux_q->V)] == 0){
                int temp = dist[p(aux)] + aux_q->min;
                if(temp < dist[p(aux_q->V)]){
                    dist[p(aux_q->V)] = temp;
                    st[p(aux_q->V)] = aux;
                }
              }               
            }
            
            if(aux == finish){
                printf("F%d |%d|\n",dist[p(finish)],finish);
                for(int a = st[p(finish)]; a <= -2; a = st[p(a)])
                    printf("%d\n",a);
            }
    }
    free(dist);
    free(st);
    free(removed);
}

void CreateVertice(int v,Queue **head){
    Queue *V = malloc(sizeof(Queue));
    V->vertice = p(v);
    if(head == NULL){
        *head = V;
    }else{
        V->next = *head;
        *head = V;
    }
}



Queue *PopFirst(Queue **head,int *dist){
    Queue *current = NULL;
    Queue *auxH = *head;
    Queue *auxT = (*head)->next;
    Queue *conect = NULL;
    int aux = 0;
    int min = __INT_MAX__;

    while(auxH != NULL){
        if(aux == 0){
            min = dist[p(auxH->vertice)];
            conect = NULL;
            aux = 1;
        }
        if(auxT != NULL && min > dist[p(auxT->vertice)] && aux != 0){
            min = dist[p(auxT->vertice)];
            conect = auxH;
        }
        auxH = auxH->next;
        if (auxT != NULL)
        {
            auxT = auxT->next;
        }
    }
    if(conect == NULL){
        current = *head;
        *head = (*head)->next;
    }else{
        current = conect->next;
        conect->next = current->next;
    }
    return current;
}

void print_queue(Queue* head){
    Queue *aux = head;

    while(aux != NULL){
        printf("%d->",aux->vertice);
        aux = aux->next;
    }
    printf("\n"); 
}

