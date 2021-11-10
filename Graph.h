/******************************************************************************
 * NOME
 *   Graph.h
 *
 * DESCRICAO
 *   Contem os cabecalhos das funcoes utilizadas no Graph.h. e a estrutura do 
 *   nosso grafo e dos vertices por que e composto.
 *
 ******************************************************************************/
#ifndef GRAPH
#define GRAPH

typedef struct node{
    int V; /* Vertice em causa. */
    int min;
    int linha; /*Linha da parede partida*/
    int coluna; /*Coluna da parede partida*/
    struct node *next;
}Node;

typedef struct graph{  
    int V; /* Numero total de vertices. */
    Node **adj; /* Vetor de lista de adjacencias. */

}Graph;


Graph* GraphInit(int V);
void GraphInsertE(Graph *G,int v_inicial,int v_final,int c,int d);
Node *New(int v,Node *next,int c,int d);
int Verify(Graph *G,int v,int w);
void ChangeMin(Graph *G,int v, int w, int value,int line,int column);
void FreeGraph(Graph *G,int different_cells);
void FillBoard(int **tabuleiro,int *different_cells,int *dim,int number_of_lines);
Graph *CreateGraph(int **tabuleiro,int *dim,int different_cells);
void WriteCoord(Graph **G,int vertice,int line,int column);

#endif