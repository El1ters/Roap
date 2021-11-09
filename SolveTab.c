/******************************************************************************
 * NOME
 *   SolveTab.c
 *
 * DESCRICAO
 *   Contem umas funcoes que permitem resolver o problema inicial (ou seja,
 *   consoante os dados de entrada recebidos irá ser impressa a respetiva
 *   solucao no ficheiro de saida) e outras que contribuiem para a resolucao
 *   do problema final (BFS que divide o nosso labirinto em salas e Break que 
 *   verifica se uma dada celula cinzenta pode ou nao ser quebravel).
 *
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SolveTab.h"
#include "ReadFile.h"


/******************************************************************************
 * Break ()
 *
 * Argumentos: tabuleiro -> Um ponteiro para um array de inteiros que contem o
 *                          labirinto.
 *             def       -> Ponteiro para as coordenadas da celula da 2ª linha
 *                          do ficheiro de entrada.
 *             dim       -> Ponteiro para a dimensao dos labirintos.
 *  
 * Retorna: -1 -> Se as celulas nem se quer forem cinzentas (isto e, se forem
 *                brancas ou pretas).
 *           0 -> Se as nossas celulas cinzentas nao sao quebraveis.
 *           1 -> Se as nossas celulas cinzentas sao quebraveis.
 *
 * Descricao: Esta funcao serve apenas para indicar as celulas cinzentas que 
 *            sao quebraveis.
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


/****************************************************************************************
 * BFS ()
 *
 * Argumentos: inicial          -> Um ponteiro que aponta para as coordenadas do ponto
 *                                 de partida do labirinto. 
 *             tabuleiro        -> Um ponteiro para um array de inteiros que contem o
 *                                 labirinto.
 *             dim              -> Ponteiro para a posicao de memoria onde esta a 
 *                                 dimensao dos labirintos.
 *             number_of_lines  -> Inteiro correspondente ao numero total de celulas do 
 *                                 labirinto.
 *             value            -> Inteiro que vai corresponder ao valor de identificacao 
 *                                 de uma sala do labirinto
 *             queue            -> Ponteiro para uma estrutura do tipo Coord que guarda 
 *                                 coordenadas do labirinto.
 *           
 * Retorna: (void).
 *
 * Descricao: Esta funcao atribui um mesmo inteiro a todas as celulas de uma sala do 
 *            labirinto.
 *            Comeca-se por colocar num vetor de espera (chamado queue) a celula
 *            correspondente ao ponto de partida do labirinto, sendo-lhe atribuido um
 *            valor inteiro (value). 
 *            De seguida, o programa ira identificar todas as suas celulas adjacentes
 *            que pertencem a sua mesma sala, colocando-as na lista de espera (queue)
 *            para lhes ser atribuido o mesmo valor inteiro.
 *            Assim todas as celulas pertencentes a uma mesma sala vao possuir o mesmo
 *            valor, que sera diferente em relacao a celulas de outras salas, obtendo-se,
 *            assim, a divisao do labirinto em salas. 
 * 
 ***************************************************************************************/
void BFS(int *inicial,int **tabuleiro,int *dim,int number_of_lines,int value,Coord *queue){
    int q_size = 0;  /*Inicializacao do tamanho da fila de espera -> inicialmente ira conter apenas a celula do ponto de partida. */
    Coord current; /* Estrutura que vai guardar as coordendas da celula que esta as ser verificada na queue. */
    Coord start; /* Estrutura que vai guardar as coordendas da celula correspondente ao ponto de partida do labirinto. */

    start.x = inicial[0], start.y = inicial[1]; /* Coloca-se na estrutura "start" a celula do ponto de partida. */
    tabuleiro[start.x][start.y] = value; /* Atribui-se um valor a nossa celula do ponto de partida, valor esse que ira ser igual para 
                                            todas as celulas da mesma sala. */

    queue[q_size++] = start; /* A lista de espera ira conter inicialmente a celula do ponto de partida. */
    
    /*
    Conjunto de operacoes explicadas no cabecalho da funcao que permitirao atribuir o mesmo valor a todas as celulas de uma mesma sala. */
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

