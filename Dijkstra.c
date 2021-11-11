/******************************************************************************
 * NOME
 *   Dijkstra.c
 *
 * DESCRICAO
 *   Contem as funcoes que permitem encontrar o caminho de menor custo entre o 
 *   ponto de partida do labirinto e a ponto de chegada.
 *
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "Dijkstra.h"

#define p(a) ((a*-1) - 2)


/*********************************************************************************************************
 * Dijkstra ()
 *
 * Argumentos: G                -> Ponteiro que aponta para o nosso grafo (que corresponde a 
 *                                 nossa lista de adjacencias + numero total de vertices + 
 *                                 numero total de arestas).
 *             differente_cells -> Inteiro correspondente ao numero de salas diferentes do 
 *                                 nosso labirinto.
 *             start            -> Inteiro correspondente ao valor da celula de partida do 
 *                                 labirinto.
 *             finish           -> Inteiro correspondente ao valor da celula de chegada do 
 *                                 labirinto.
 *             fp1              -> Ponteiro para o ficheiro de saida.
 *
 * Retorna: (void).
 *
 * Descricao: Esta funcao vai encontrar o caminho minimo entre a celula de partida do 
 *            labirinto e a celula de chegada do mesmo, recorrendo para isso ao algoritmo
 *            Dijkstra. Este algoritmo comeca por olhar para a celula de partida do labirinto,
 *            verificando todas as suas celulas adjacentes e adicionando-as a uma lista de espera
 *            (queue).
 *            Posteriormente, o algoritmo ira analisar todos os custos para as suas adjacentes 
 *            avancando para a celula para a qual o custo for menor, verificando as adjacentes para
 *            essa mesma celula, colocando-as na queue e verificando para qual delas o caminho e de
 *            menor custo, repetindo assim o processo consecutivamente ate se chegar a celula final.
 *            Ao longo deste processo, vai-se obtendo, portanto, um conjunto de valores de menores custos
 *            entre diferentes vertices, valores esses que serao guardados num vetor chamado dist
 *            que vai sendo atualizado em cada vertice para o valor do caminho de menor custo entre 
 *            si e a celula inicial.
 *            E de notar tambem que a medida que os vertices vao sendo verificados vao passar da lista
 *            de espera (queue) para um vetor chamado removed de modo a que se evite "perder tempo" a 
 *            verificar o mesmo vertice mais que uma vez.
 *            Criou-se ao mesmo um vetor chamado st que faz com que nao se perca o rumo ao caminho de
 *            menor custo total, ou seja, este vetor vai conter para cada vertice o vertice que o precede,
 *            conseguindo assim a ligacao de menor custo entre a celula final e inicial.  
 *     
 *********************************************************************************************************/
void Dijkstra(Graph *G,int different_cells,int start,int finish,FILE *fp1){

  
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


/**********************************************************************************************
 * CreateVertice()
 *
 * Argumentos: v    -> Inteiro correspondente ao valor numerico que identifica uma sala.
 *             head -> Ponteiro para um array de estruturas correspondentes aos nos da nossa 
 *                     lista de espera utilizada no algoritmo Dijkstra.
 *                  
 * Retorna: (void).
 *
 * Descricao: Esta funcao permite a criacao de um vertice do nosso grafo.
 *               
 **********************************************************************************************/
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


/**********************************************************************************************
 * PopFirst()
 *
 * Argumentos: head -> Ponteiro para um array de estruturas correspondentes aos nos da nossa 
 *                     lista de espera utilizada no algoritmo Dijkstra.
 *             dist -> Ponteiro para um inteiro correspondente ao caminho de menor custo entre
 *                      dois vertices do nosso grafo (entre duas salas).
 *                  
 * Retorna: current ->
 *
 * Descricao: 
 *               
 **********************************************************************************************/
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


/**********************************************************************************************
 * FreeQueue()
 *
 * Argumentos: head -> Ponteiro para um array de estruturas correspondentes aos nos da nossa 
 *                     lista de espera utilizada no algoritmo Dijkstra.
 *                  
 * Retorna: (void).
 *
 * Descricao: Esta funcao serve para libertar o espaco que tinha sido alocado para a nossa lista
 *            de espera do algoritmo Dijkstra.
 *               
 **********************************************************************************************/
void FreeQueue(Queue **head){
    Queue* aux = *head;
    while(*head != NULL){
        aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}

