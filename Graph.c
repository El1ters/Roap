/*******************************************************************************************
 * NOME
 *   Graph.c
 *
 * DESCRICAO
 *   Contem umas funçoes que permitem criar o nosso grafo (que ira corresponder a
 *   interligacao das diferentes salas do labirinto atraves de uma lista de adjacencias 
 *   juntamente com o numero total de arestas e vertices) e outras que ajudam a resolver
 *   o problema final (saber se e possivel ir de uma celula para a outra e se sim, qual o 
 *   menor caminho possivel).
 *
 *******************************************************************************************/
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "Graph.h"
#include "SolveTab.h"


/**********************************************************************************
 * GraphInit()
 *
 * Argumentos: V -> Inteiro correspondente ao numero de vertices do grafo. 
 * 
 * Retorna: G -> Ponteiro para o nosso grafo (que corresponde a nossa   lista de
 *               adjacencias + numero total de vertices + numero total de arestas).
 *
 * Descricao: Esta funcao serve para alocar o espaco necessario para o nosso 
 *            grafo e para inicializar o mesmo. 
 *               
 **********************************************************************************/
Graph* GraphInit(int V){
    int v;
    Graph *G = malloc(sizeof(Graph));
    if(G == NULL)
        exit(0);
    G->V = V;
    if((G->adj = (Node**)malloc(sizeof(Node*) * V)) == NULL)
        exit(0);
    for(v = 0; v < V;v++)
        G->adj[v] = NULL;

    return G;
}


/*************************************************************************************
 * GraphInsert()
 *
 * Argumentos: G         -> Ponteiro que aponta para o nosso grafo (que corresponde a 
 *                          nossa lista de adjacencias + numero total de vertices + 
 *                          numero total de arestas).
 *             v_inicial -> Inteiro correspondente ao valor de uma sala do nosso 
 *                          labirinto.
 *             v_final   -> Inteiro correspondente ao valor de uma sala do nosso
 *                          labirinto.  
 * 
 * Retorna: (void).
 *
 * Descricao: Esta funcao permite conetar uma sala adjacente a sua respetiva sala,
 *            na lista de adjacencias. 
 *               
 *************************************************************************************/
void GraphInsertE(Graph *G,int v_inicial,int v_final,int c,int d){
    G->adj[(v_inicial * -1) - 2] = New(v_final,G->adj[(v_inicial * -1) - 2],c,d);
    G->adj[(v_final *-1) - 2] = New(v_inicial,G->adj[(v_final *-1) - 2],c,d);
}


/*************************************************************************************
 * New()
 *
 * Argumentos: v    -> Inteiro correspondente ao vertice do nosso no.
 *             next -> Ponteiro para um no da nossa lista de adjacencias.
 * 
 * Retorna: x -> Ponteiro para a cabeca do no da nossa lista de adjacencias.
 *
 * Descricao: Esta funcao serve para alocar o espaco necessario para um no 
 *            da nossa lista de adjacencias e para inicializar o mesmo. 
 *               
 *************************************************************************************/
Node *New(int v,Node *next,int c,int d){
    Node *x;
    if((x = (Node*)malloc(sizeof(Node))) == NULL){
        exit(0);
    }
    x->V = v;
    x->min = __INT_MAX__;
    x->linha = c + 1;
    x->coluna = d + 1;
    x->next = next; 
    return x;
}


/*************************************************************************************
 * Verify()
 *
 * Argumentos: G -> Ponteiro que aponta para o nosso grafo (que corresponde a 
 *                  nossa lista de adjacencias + numero total de vertices + 
 *                  numero total de arestas).
 *             v -> Inteiro correspondente ao valor de uma sala do nosso 
 *                  labirinto.
 *             w -> Inteiro correspondente ao valor de uma sala do nosso 
 *                  labirinto.
 * 
 * Retorna: 1 -> Se duas salas nao estiverem ligadas.
 *          0 -> Se duas ja  salas estiverem ligadas.
 *
 * Descricao: Esta funcao serve para verificar se, na nossa lista de adjacencias, duas
 *            salas se encontram interligadas ou nao.
 *               
 *************************************************************************************/
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


/*************************************************************************************
 * ChangeMin()
 *
 * Argumentos: G     -> Ponteiro que aponta para o nosso grafo (que corresponde a 
 *                      nossa lista de adjacencias + numero total de vertices + 
 *                      numero total de arestas).
 *             v     -> Inteiro correspondente ao valor de uma sala do nosso 
 *                      labirinto.
 *             w     -> Inteiro correspondente ao valor de uma sala do nosso 
 *                      labirinto.
 *             value -> Inteiro que vai corresponder ao valor de menor custo entre duas
 *                      salas adjacentes.
 * 
 * Retorna: (void).
 *
 * Descricao: Esta funcao serve para ver qual e o caminho de menor custo entre duas 
 *            salas adjacentes.
 *               
 *************************************************************************************/
void ChangeMin(Graph *G,int v, int w, int value,int line,int column){
    Node *aux;
        aux = G->adj[(v * -1) - 2];
        while(aux != NULL){
            if(aux->V == w){
                if(value < aux->min){
                    aux->min = value;
                    aux->linha = line + 1;
                    aux->coluna = column + 1;
                    return;
                }    
            }
            aux = aux->next;
        }
}


/**********************************************************************************************
 * FreeGraph()
 *
 * Argumentos: G                -> Ponteiro que aponta para o nosso grafo (que corresponde a 
 *                                 nossa lista de adjacencias + numero total de vertices + 
 *                                 numero total de arestas).
 *             differente_cells -> Inteiro correspondente ao numero de salas diferentes do 
 *                                 nosso labirinto.
 *                  
 * Retorna: (void).
 *
 * Descricao: Esta funcao serve para libertar todo o espaco que tinha sido alocado para
 *            criar o nosso grafo (que corresponde a nossa lista de adjacencias + numero
 *            total de vertices + numero total de arestas).
 *               
 **********************************************************************************************/
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


/**********************************************************************************************
 * FillBoard()
 *
 * Argumentos: tabuleiro        -> Ponteiro para um array de inteiros que contem o
 *                                 labirinto.
 *             differente_cells -> Ponteiro para o numero de salas diferentes do 
 *                                 nosso labirinto.
 *             dim              -> Ponteiro para a posicao de memoria onde esta a 
 *                                 dimensao dos labirintos.
 *             number_of_lines  -> Inteiro correspondente ao numero total de celulas do 
 *                                 labirinto.
 *                  
 * 
 * Retorna: (void).
 *
 * Descricao: Esta funcao serve para dividir o nosso tabuleiro em salas.
 *    
 **********************************************************************************************/
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


/************************************************************************************
 * CreateGraph()
 *
 * Argumentos: tabuleiro        -> Ponteiro para um array de inteiros que contem o
 *                                 labirinto.
 *             dim              -> Ponteiro para a posicao de memoria onde esta a 
 *                                 dimensao dos labirintos.
 *             differente_cells -> Ponteiro para o numero de salas diferentes do 
 *                                 nosso labirinto.
 * 
 * Retorna: G -> Ponteiro que aponta para o nosso grafo (que corresponde a 
 *               nossa lista de adjacencias + numero total de vertices + 
 *               numero total de arestas).
 *
 * Descricao: Esta funcao permite, atraves de um conjunto de condicoes e chamadas 
 *            a outras funcoes criadas acima, criar o nosso grafo.
 *    
 ************************************************************************************/
Graph *CreateGraph(int **tabuleiro,int *dim,int different_cells){
    Graph *G = GraphInit(different_cells);
    int room_value[2] = {0,0};
    int f[2];
    int dont_create = 0;
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
                                    if(tabuleiro[c + 1][d] == tabuleiro[c - 1][d])
                                        dont_create = 1;
                                    if((G->adj[(room_value[0] *-1) - 2] == NULL || G->adj[(room_value[1] *-1) - 2] == NULL) && dont_create == 0){
                                        GraphInsertE(G,tabuleiro[c + 1][d],tabuleiro[c - 1][d],c,d);   
                                            G->adj[(tabuleiro[c + 1][d] * -1) -2]->min = tabuleiro[c][d];
                                            G->adj[(tabuleiro[c - 1][d] * -1) -2]->min = tabuleiro[c][d];
                                    }else{
                                        if((Verify(G,tabuleiro[c - 1][d],tabuleiro[c + 1][d]) == 1) && dont_create == 0){
                                            GraphInsertE(G,tabuleiro[c + 1][d],tabuleiro[c - 1][d],c,d);
                                            }                 
                                        }
                                        ChangeMin(G,tabuleiro[c - 1][d],tabuleiro[c + 1][d],tabuleiro[c][d],c,d);
                                        ChangeMin(G,tabuleiro[c + 1][d],tabuleiro[c - 1][d],tabuleiro[c][d],c,d);
                                    }  
                                }
                                dont_create = 0;
                        if(d + 1 < dim[1] && d - 1 >= 0){
                            room_value[0] = tabuleiro[c][d - 1];
                            room_value[1] = tabuleiro[c][d + 1];
                                if(tabuleiro[c][d + 1] < -1 && tabuleiro[c][d - 1] < -1){  
                                    if(tabuleiro[c][d + 1] == tabuleiro[c][d - 1])
                                        dont_create = 1;
                                    if((G->adj[(room_value[0] *-1) - 2] == NULL || G->adj[(room_value[1] *-1) - 2] == NULL) && dont_create == 0 ){
                                        GraphInsertE(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1],c,d);
                                        G->adj[(tabuleiro[c][d + 1] * -1) -2]->min = tabuleiro[c][d];
                                        G->adj[(tabuleiro[c][d - 1] * -1) -2]->min = tabuleiro[c][d];
                                    }else{
                                        if(Verify(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1]) == 1 && dont_create == 0){
                                            GraphInsertE(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1],c,d);
                                        }
                                    }
                                    ChangeMin(G,tabuleiro[c][d + 1],tabuleiro[c][d - 1],tabuleiro[c][d],c,d);
                                    ChangeMin(G,tabuleiro[c][d - 1],tabuleiro[c][d + 1],tabuleiro[c][d],c,d);
                                }
                                dont_create = 0;
                        }
                    }
            }
        }
    }
    return G;
}
