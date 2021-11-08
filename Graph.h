#ifndef GRAPH
#define GRAPH

typedef struct node{
    int V; /*o vertice em causa*/
    int min;
    struct node *next;
}Node;

typedef struct graph{  
    int V; /*nº total de vertices*/
    int E; /*nº total de arestas*/
    Node **adj;/*vetor de lista de adjacencias*/

}Graph;

/*Declaração de funções*/
Graph* GraphInit(int V);
void GraphInsertE(Graph *G,int v_inicial,int v_final);
Node *New(int v,Node *next);
int Verify(Graph *G,int v,int w);
void ChangeMin(Graph *G,int v, int w, int value);
void FreeGraph(Graph *G,int different_cells);
void FillBoard(int **tabuleiro,int *different_cells,int *dim,int number_of_lines);
Graph *CreateGraph(int **tabuleiro,int *dim,int different_cells);

#endif