#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "Dijkstra.h"

#define p(a) ((a*-1) - 2)

void Dijkstra(Graph *G,int different_cells,int start,int finish,FILE *fp1){
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
    }
    CreateVertice(-2,&head_queue);
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
                    if(st[p(aux_q->V)] == -1){
                        CreateVertice(aux_q->V,&head_queue);
                    }
                    dist[p(aux_q->V)] = temp;
                    st[p(aux_q->V)] = aux;                    
                }
              }               
            }
            
            if(aux == finish){
                int edge = 0;
                fprintf(fp1,"%d\n",dist[p(finish)]);
                for(int a = finish;a <= -2;a = st[p(a)]){
                    removed[edge] = a;
                    edge++;
                }
                edge--;
                if(dist[p(finish)] != 0)
                    fprintf(fp1,"%d\n",edge); 
                for(int b = edge; b >= 0;b--){
                    Node *aux = NULL;
                    aux = G->adj[p(removed[b])];
                    while(aux != NULL){
                        if(b - 1 >= 0 && aux->V == removed[b - 1]){
                            fprintf(fp1,"%d %d %d\n",aux->linha,aux->coluna,aux->min);
                            break;
                        }
                        aux = aux->next;
                    } 
                }
                fprintf(fp1,"\n\n"); 
                free(dist);
                free(st);
                free(removed);
                FreeQueue(&head_queue);
                return;        
            }
    }
    
    free(dist);
    free(st);
    free(removed);
    FreeQueue(&head_queue);
    fprintf(fp1,"-1\n\n\n");

}

void CreateVertice(int v,Queue **head){
    Queue *V = malloc(sizeof(Queue));
    V->vertice = v;
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

void FreeQueue(Queue **head){
    Queue* aux = *head;
    while(*head != NULL){
        aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}

