/******************************************************************************
 * NOME
 *   SolveTab.c
 *
 * DESCRICAO
 *   Contem a funcao SolveTab que permite resolver o problema inicial, ou seja,
 *   consoante os dados de entrada recebidos irá ser impressa a respetiva
 *   solucao no ficheiro de saida.
 *
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SolveTab.h"
#include "ReadFile.h"


/*
Estrutura que guarda coordenadas de celulas do labirinto. */
typedef struct Coord{
    int x;
    int y;
}Coord;


/******************************************************************************
 * SolveTab ()
 *
 * Argumentos: tabuleiro -> Um ponteiro para um array de inteiros que contem o
 *                          labirinto.
 *             mode      -> Ponteiro para as variantes de funcionamento.
 *             def       -> Ponteiro para as coordenadas da celula da 2ª linha
 *                          do ficheiro de entrada.
 *             dim       -> Ponteiro para a dimensao dos labirintos.
 *             fp1       -> Ponteiro para o ficheiro de saida onde sao escritas
 *                          as soluçoes ao problema.
 *  
 * Retorna: (void).
 *
 * Descricao: Esta funcao permite dar resposta ao problema inicial face as
 *            diferentes variantes de funcionamento.
 *     
 *****************************************************************************/
void SolveTab(int **tabuleiro,char *mode,int *def,int *sec,int *dim,FILE *fp1,int number_of_lines){

    /* 
    Condicao que permite resolver a variante de funcionamento A1. */
    if(strcmp(mode,"A1") == 0){
        fprintf(fp1,"%d\n\n",tabuleiro[def[0] - 1][def[1] - 1]);
    }

    if(strcmp(mode,"A2") == 0 || strcmp(mode,"A3") == 0 || strcmp(mode,"A4") == 0){
        for(int i = -2;i <= 0;i++){
            for(int k = -2;k <= 0;k++){
                if(i == k || i - 2 == k || i + 2 == k)
                    continue;

                if(outside(def[0] + i + 1,def[1] + k + 1,dim) == 1)
                    continue;
                    
                if((tabuleiro[def[0] + i][def[1] + k] == 0 && strcmp(mode,"A2") == 0) ||
                   (tabuleiro[def[0] + i][def[1] + k] == -1 && strcmp(mode,"A4") == 0) ||
                   (tabuleiro[def[0] + i][def[1] + k] > 0 && strcmp(mode,"A3") == 0)){
                           fprintf(fp1,"1\n\n");
                           return;
                   }
            }
        }
        fprintf(fp1,"0\n\n");
    }

    /* 
    Condicao que permite resolver a variante de funcionamento A5. */
    if(strcmp(mode,"A5") == 0){
        /* 
        Verifica se a celula em causa e preta ou branca, retornando -1 se sim. */
        if(tabuleiro[def[0] - 1][def[1] - 1] == 0 || tabuleiro[def[0] - 1][def[1] - 1] == -1){
            fprintf(fp1,"-1\n\n");
            return;
        }

        /* 
        Faz a verificao para as celulas dos cantos do labirinto, dado que estas nao se podem partir
        devido ao facto de nao poder haver continuacao do caminho. */
        if((def[0] - 2 < 0 && def[1] - 2 < 0)      ||
           (def[0] - 2 < 0 && def[1] + 1 > dim[1]) ||
           (def[0] + 1 > dim[0] && def[1] - 2 < 0) ||
           (def[0] + 1 > dim[0] && def[1] + 1 > dim[1])){
               fprintf(fp1,"0\n\n");
               return;
        }
        
        /*
        Verifica, para as celulas encostadas ao lado direito, em cima, em baixo e esquerda do labirinto, 
        se a celula a esquerda, em baixo, em cima e a direita, respetivamente da celula em causa sao brancas,
        se sim entao a celula cinzenta e quebravel porque pode haver continuacao do caminho. */
        if((outside(def[0] - 1,def[1],dim) == 1 && tabuleiro[def[0]][def[1] - 1] == 0)     ||
           (outside(def[0] + 1,def[1],dim) == 1 && tabuleiro[def[0] - 2][def[1] - 1] == 0) ||
           (outside(def[0],def[1] - 1,dim) == 1 && tabuleiro[def[0] - 1][def[1]] == 0)     ||
           (outside(def[0],def[1] + 1, dim) == 1 && tabuleiro[def[0] - 1][def[1] - 2] == 0)){
                fprintf(fp1,"1\n\n");
                return;
            }

        /* 
        Verifica, para as restantes celulas do labirinto, se as celulas abaixo e acima
        da celula em causa são brancas, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[0] - 2 >= 0 && def[0] < dim[0]){
            if(tabuleiro[def[0] - 2][def[1] - 1] == 0 && tabuleiro[def[0]][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
                
        /* 
        Verifica, para as restantes celulas do labirinto, se as celulas a esquerda e a
        direita da celula em causa são brancas, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[1] - 2 >= 0 && def[1] < dim[1]){
            if(tabuleiro[def[0] - 1][def[1] - 2] == 0 && tabuleiro[def[0] - 1][def[1]] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        fprintf(fp1,"0\n\n");
        return;
    }

    /* 
    Condicao que permite resolver a variante de funcionamento A6. */
    if(strcmp(mode,"A6") == 0){
        if(BFS(def,sec,tabuleiro,dim,number_of_lines) == 1){
            fprintf(fp1,"1\n\n");
        }else
            fprintf(fp1,"0\n\n");
    }

}

/******************************************************************************
 * BFS ()
 *
 * Argumentos: inicial   -> Um ponteiro que aponta para as coordenadas do ponto
 *                          de partida do labirinto. 
 *             final     -> Um ponteiro que aponta para as coordenadas do ponto
 *                          de chegada do labirinto. 
 *             tabuleiro -> Um ponteiro para um array de inteiros que contem o
 *                          labirinto.
 *             dim       -> Ponteiro para a posicao de memoria onde esta a 
 *                          dimensao dos labirintos.
 *           
 * Retorna: 1 -> se foi possivel encontrar uma ligacao entre o ponto de partida
 *               e o ponto de chegada.
 *          0 -> se nao foi possivel encontrar uma ligacao entre o ponto de partida
 *               e o ponto de chegada ou se as coordendas correspondentes a estes
 *               pontos sao paredes.
 *
 * Descricao: Esta funcao permite dar resposta a variedade de funcionamento A6.
 *            Esta funcao comeca por colocar num vetor de espera (chamado queue)
 *            a celula correspondente ao ponto de partida do labirinto, verificando
 *            se esta corresponde ou nao a celula do ponto de chegada do labirinto. 
 *            De seguida, se o programa verificar que a celula da queue nao corresponde 
 *            ao conjunto de chegada ira identificar todas as suas celulas adjacentes, 
 *            colocando-as na lista de espera (queue) e movendo a celula em causa para 
 *            um vetor que ira conter todas as celulas que ja foram visitadas.
 *            O programa ira, portanto, executar sucessivamente estas operacoes 
 *            (verificar celula a celula, colocando-as na queue, passando as ja 
 *            verificadas para o vetor de espera, verificando as adjancentes da celula 
 *            que esta em causa) ate chegar a celula correspondente ao ponto de chegada,
 *            se este exisitir. 
 *     
 *****************************************************************************/
int BFS(int *inicial,int *final,int **tabuleiro,int *dim,int number_of_lines){
    Coord queue[dim[0] * dim[1] - number_of_lines]; /* Inicializacao do vetor que correspondera a fila de espera. */
    int q_size = 1; /* Inicializacao do tamanho da fila de espera -> inicialmente ira conter apenas a celula do ponto de partida. */
    int **visited = (int**)calloc(sizeof(int*),dim[0]);  /*Indicacao do tamanho do vetor que ira conter as celulas ja verificdas.*/
    for(int i = 0; i < dim[0];i++)
        visited[i] = (int*)calloc(sizeof(int),dim[1]);
    

    Coord objective; /* Estrutura que vai guardar as coordendas da celula correspondente ao ponto de chegada do labirinto. */
    Coord current; /* Estrutura que vai guardar as coordendas da celula que esta as ser verificada na queue. */
    Coord start; /* Estrutura que vai guardar as coordendas da celula correspondente ao ponto de partida do labirinto. */
    
    start.x = inicial[0] - 1, start.y = inicial[1] - 1; /* Coloca-se na estrutura "start" a celula do ponto de partida. */
    objective.x = final[0] - 1, objective.y = final[1] - 1; /* Coloca-se na estrutura "objective" a celula do ponto de chegada. */

    /*
    Condicao que verifica se a coordenada do ponto de partida nao e branca, retornando logo 0 se nao for. */
    if(tabuleiro[start.x][start.y] != 0){
        for(int l = 0;l < dim[0];l++)
            free(visited[l]);  
        free(visited);
        return 0;
    }
    queue[0] = start; /* A lista de espera ira conter inicialmente a celula do ponto de partida. */
    visited[start.x][start.y] = 1; 

    /*
    Conjunto de operacoes explicadas no cabecalho da funcao que permitirao saber se ha ou nao ligacao da 
    celula de partida do labirinto ate a celula de chegada. */
    while(q_size > 0){
        current = queue[0];
        for(int i = 0; i < q_size - 1; i++){
            queue[i] = queue[i + 1];
        }
        q_size--;

        if(current.x == objective.x && current.y == objective.y){
            for(int l = 0;l < dim[0];l++)
                free(visited[l]);  
            free(visited);
            return 1;
        }

        Coord adj; /* Estrutura que vai guardar as coordendas das celulas adjacentes a celula em causa. */
        if(current.x - 1 >= 0 && visited[current.x - 1][current.y] == 0 && tabuleiro[current.x - 1][current.y] == 0){
            adj.y = current.y, adj.x = current.x - 1;
            queue[q_size] = adj;
            visited[current.x - 1][current.y] = 1;
            q_size++; 
        }

        
        if(current.x + 1 < dim[0] && visited[current.x + 1][current.y] == 0 && tabuleiro[current.x + 1][current.y] == 0){
            adj.x = current.x + 1, adj.y = current.y;
            queue[q_size] = adj;
            visited[current.x + 1][current.y] = 1;
            q_size++;
        }

        if(current.y - 1 >= 0 && visited[current.x][current.y - 1] == 0 && tabuleiro[current.x][current.y - 1] == 0){
            adj.x = current.x, adj.y = current.y - 1;
            queue[q_size] = adj;
            visited[current.x][current.y - 1] = 1;
            q_size++;
        }

        if(current.y + 1 < dim[1] && visited[current.x][current.y + 1] == 0 && tabuleiro[current.x][current.y + 1] == 0){
            adj.x = current.x, adj.y = current.y + 1;
            queue[q_size] = adj;
            visited[current.x][current.y + 1] = 1;
            q_size++;
        }

    }

    for(int l = 0;l < dim[0];l++)
        free(visited[l]);  
    free(visited);

    return 0;
}