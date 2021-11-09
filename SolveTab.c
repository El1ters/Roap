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
int Break(int **tabuleiro,int *def,int *dim){
        /* 
        Verifica se a celula em causa e preta ou branca, retornando -1 se sim. */
        if(tabuleiro[def[0]][def[1]] < -1 || tabuleiro[def[0]][def[1]] == -1){
            return -1;
        }

        /* 
        Faz a verificao para as celulas dos cantos do labirinto, dado que estas nao se podem partir
        devido ao facto de nao poder haver continuacao do caminho. */
        if((def[0] - 1 < 0 && def[1] - 1 < 0)      ||
           (def[0] - 1 < 0 && def[1] + 1 >= dim[1]) ||
           (def[0] + 1 >= dim[0] && def[1] - 1 < 0) ||
           (def[0] + 1 >= dim[0] && def[1] + 1 >= dim[1])){
               return 0;
        }
        
        /*
        Verifica, para as celulas encostadas ao lado direito, em cima, em baixo e esquerda do labirinto, 
        se a celula a esquerda, em baixo, em cima e a direita, respetivamente da celula em causa sao brancas,
        se sim entao a celula cinzenta e quebravel porque pode haver continuacao do caminho. */
        if((def[0] - 1 < 0 && tabuleiro[def[0] + 1][def[1]] < -1) ||
           (def[0] + 1 >= dim[0] && tabuleiro[def[0] - 1][def[1]] < -1) ||
           (def[1] - 1 < 0 &&  tabuleiro[def[0]][def[1] + 1] < -1) ||
           (def[1] + 1 >= dim[1] && tabuleiro[def[0]][def[1] - 1] < -1)){
                return 1;
            }

        /* 
        Verifica, para as restantes celulas do labirinto, se as celulas abaixo e acima
        da celula em causa são brancas, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[0] - 1 >= 0 && def[0] + 1 < dim[0]){
            if(tabuleiro[def[0] - 1][def[1]] <= 0 &&
               tabuleiro[def[0] - 1][def[1]] != -1 &&
               tabuleiro[def[0] + 1][def[1]] != -1 &&
               tabuleiro[def[0] + 1][def[1]] <= 0){
                return 1;
            }
        }
                
        /* 
        Verifica, para as restantes celulas do labirinto, se as celulas a esquerda e a
        direita da celula em causa são brancas, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[1] - 1 >= 0 && def[1] + 1 < dim[1]){
            if(tabuleiro[def[0]][def[1] - 1] <= 0 &&
               tabuleiro[def[0]][def[1] - 1] != -1 &&
               tabuleiro[def[0]][def[1] + 1] != -1 &&
               tabuleiro[def[0]][def[1] + 1] <= 0){
                return 1;
            }
        }
        return 0;
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
 *            se esta exisitir. 
 *     
 *****************************************************************************/


void BFS(int *inicial,int **tabuleiro,int *dim,int number_of_lines,int value,Coord *queue){
    int q_size = 0;  /*Inicializacao do tamanho da fila de espera -> inicialmente ira conter apenas a celula do ponto de partida. */
    Coord current; /* Estrutura que vai guardar as coordendas da celula que esta as ser verificada na queue. */
    Coord start; /* Estrutura que vai guardar as coordendas da celula correspondente ao ponto de partida do labirinto. */

    start.x = inicial[0], start.y = inicial[1]; /* Coloca-se na estrutura "start" a celula do ponto de partida. */
    tabuleiro[start.x][start.y] = value;

    queue[q_size++] = start; /* A lista de espera ira conter inicialmente a celula do ponto de partida. */
    
    /*
    Conjunto de operacoes explicadas no cabecalho da funcao que permitirao saber se ha ou nao ligacao da 
    celula de partida do labirinto ate a celula de chegada. */
    while(q_size > 0){
        current = queue[--q_size];
        Coord adj; /* Estrutura que vai guardar as coordendas das celulas adjacentes a celula em causa. */
        if(current.x - 1 >= 0 && tabuleiro[current.x - 1][current.y] == 0){
            adj.y = current.y, adj.x = current.x - 1;
            queue[q_size++] = adj;
            tabuleiro[current.x - 1][current.y] = value;            
        } 
        
        if(current.x + 1 < dim[0] && tabuleiro[current.x + 1][current.y] == 0){
            adj.x = current.x + 1, adj.y = current.y;
            queue[q_size++] = adj;
            tabuleiro[current.x + 1][current.y] = value;
        }
        if(current.y - 1 >= 0 && tabuleiro[current.x][current.y - 1] == 0){
            adj.x = current.x, adj.y = current.y - 1;
            queue[q_size++] = adj;
            tabuleiro[current.x][current.y - 1] = value;
        }

        if(current.y + 1 < dim[1] && tabuleiro[current.x][current.y + 1] == 0){
            adj.x = current.x, adj.y = current.y + 1;
            queue[q_size++] = adj;
            tabuleiro[current.x][current.y + 1] = value;
        }
    }
}

