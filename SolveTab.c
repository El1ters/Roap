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
void SolveTab(int **tabuleiro,char *mode,int *def,int *sec,int *dim,FILE *fp1){

    /* 
    Condicao que permite resolver a variante de funcionamento A1. */
    if(strcmp(mode,"A1") == 0){
        fprintf(fp1,"%d\n\n",tabuleiro[def[0] - 1][def[1] - 1]);
    }

    /* 
    Condicao que permite resolver a variante de funcionamento A2. */
    if(strcmp(mode,"A2") == 0){
        if((outside(def[0] - 1,def[1],dim) == 0 && tabuleiro[def[0] - 2][def[1] - 1] == 0)||
           (outside(def[0] + 1,def[1],dim) == 0 && tabuleiro[def[0]][def[1] - 1] == 0) ||
           (outside(def[0],def[1] - 1,dim) == 0 && tabuleiro[def[0] - 1][def[1] - 2] == 0)||
           (outside(def[0],def[1] + 1, dim) == 0 && tabuleiro[def[0] - 1][def[1]] == 0)){
                fprintf(fp1,"1\n\n");
                return;
            }
        fprintf(fp1,"0\n\n");
        return;
    }

    /* 
    Condicao que permite resolver a variante de funcionamento A3. */
    if(strcmp(mode,"A3") == 0){
        if((outside(def[0] - 1,def[1],dim) == 0 && tabuleiro[def[0] - 2][def[1] - 1] > 0)||
           (outside(def[0] + 1,def[1],dim) == 0 && tabuleiro[def[0]][def[1] - 1] > 0) ||
           (outside(def[0],def[1] - 1,dim) == 0 && tabuleiro[def[0] - 1][def[1] - 2] > 0)||
           (outside(def[0],def[1] + 1, dim) == 0 && tabuleiro[def[0] - 1][def[1]] > 0)){
                fprintf(fp1,"1\n\n");
                return;
            }
        fprintf(fp1,"0\n\n");
        return;            
    }

    /* 
    Condicao que permite resolver a variante de funcionamento A4. */
    if(strcmp(mode,"A4") == 0){
        if((outside(def[0] - 1,def[1],dim) == 0 && tabuleiro[def[0] - 2][def[1] - 1] == -1)||
           (outside(def[0] + 1,def[1],dim) == 0 && tabuleiro[def[0]][def[1] - 1] == -1) ||
           (outside(def[0],def[1] - 1,dim) == 0 && tabuleiro[def[0] - 1][def[1] - 2] == -1)||
           (outside(def[0],def[1] + 1, dim) == 0 && tabuleiro[def[0] - 1][def[1]] == -1)){
                fprintf(fp1,"1\n\n");
                return;
            }
        fprintf(fp1,"0\n\n");
        return;            
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
        
        /*Verifica, para as celulas encostadas ao lado direito,em cima, em baixo e esquerda do labirinto, se a celula
        a esquerda da celula em causa é branca, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if((outside(def[0] - 1,def[1],dim) == 1 && outside(def[0] + 1,def[1],dim) == 0 && tabuleiro[def[0]][def[1] - 1] == 0)||
           (outside(def[0] + 1,def[1],dim) == 1 && outside(def[0] - 1,def[1],dim) == 0 && tabuleiro[def[0] - 2][def[1] - 1] == 0) ||
           (outside(def[0],def[1] - 1,dim) == 1 && outside(def[0],def[1] + 1,dim) == 0 && tabuleiro[def[0] - 1][def[1]] == 0)||
           (outside(def[0],def[1] + 1, dim) == 1 && outside(def[0],def[1] - 1,dim) == 0 && tabuleiro[def[0] - 1][def[1] - 2] == 0)){
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
    if( strcmp(mode,"A6") == 0){
        if(BFS(def,sec,tabuleiro,dim) == 1){
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
 *             dim       -> Ponteiro para a dimensao dos labirintos.
 *           
 * Retorna: 1 -> se foi possivel encontrar uma ligacao entre o ponto de partida
 *               e o ponto de chegada.
 *          0 -> se nao foi possivel encontrar uma ligacao entre o ponto de partida
 *               e o ponto de chegada ou se as coordendas correspondentes a estes
 *               pontos sao paredes.
 *
 * Descricao: Esta funcao permite dar resposta a variedade de funcionamento A6.
 *     
 *****************************************************************************/
int BFS(int *inicial,int *final,int **tabuleiro,int *dim){
    Coord queue[dim[0] * dim[1]];
    int q_size = 1;
    int visited[dim[0]][dim[1]];
    memset(visited,0,sizeof(visited));
    Coord objective;
    Coord current;
    Coord start;
    
    start.x = inicial[0] - 1, start.y = inicial[1] - 1;
    objective.x = final[0] - 1, objective.y = final[1] - 1;

    if(tabuleiro[start.x][start.y] != 0 || tabuleiro[objective.x][objective.y] != 0){
        return 0;
    }
    queue[0] = start;
    visited[start.x][start.y] = 1;
    while(q_size > 0){
        current = queue[0];
        for(int i = 0; i < q_size - 1; i++){
            queue[i] = queue[i + 1];
        }
        q_size--;

        if(current.x == objective.x && current.y == objective.y){
            return 1;
        }

        Coord adj;
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
    return 0;
}