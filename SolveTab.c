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
void SolveTab(int **tabuleiro,char *mode,int *def,int *dim,FILE *fp1){

    /* 
    Condicao que verifica se as coordendas estao fora do labirinto, retornando -2 se sim. */
    if(outside(def[0],def[1],dim) == 1){
       fprintf(fp1,"-2\n\n");
       return;
    }

    /* 
    Condicao que permite resolver a variante de funcionamento A1. */
    if(strcmp(mode,"A1") == 0){
        fprintf(fp1,"%d\n\n",tabuleiro[def[0] - 1][def[1] - 1]);
    }

    /* 
    Condicao que permite resolver a variante de funcionamento A2. */
    if(strcmp(mode,"A2") == 0){

        /*
        Conjunto de condicoes que permite verificar se as celulas adjantes a celula em causa
        (celula a esquerda, direita, baixo e acima) estao dentro do labirinto e se sao brancas. */
        if((outside(def[0] - 1,def[1],dim) == 0 && tabuleiro[def[0] - 2][def[1] - 1] == 0)||
           (outside(def[0] + 1,def[1],dim) == 0 && tabuleiro[def[0]][def[1] - 1] == 0)    ||
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

        /*
        Conjunto de condicoes que permite verificar se as celulas adjantes a celula em causa
        (celula a esquerda, direita, baixo e acima) estao dentro do labirinto e se sao cinzentas. */
        if((outside(def[0] - 1,def[1],dim) == 0 && tabuleiro[def[0] - 2][def[1] - 1] > 0)||
           (outside(def[0] + 1,def[1],dim) == 0 && tabuleiro[def[0]][def[1] - 1] > 0)    ||
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

        /*
        Conjunto de condicoes que permite verificar se as celulas adjantes a celula em causa
        (celula a esquerda, direita, baixo e acima) estao dentro do labirinto e se sao pretas. */
        if((outside(def[0] - 1,def[1],dim) == 0 && tabuleiro[def[0] - 2][def[1] - 1] == -1)||
           (outside(def[0] + 1,def[1],dim) == 0 && tabuleiro[def[0]][def[1] - 1] == -1)    ||
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

        /* 
        Verifica, para as celulas encostadas à parte de cima do labirinto, se a celula
        abaixo da celula em causa é branca, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[0] - 2 < 0){
            if(tabuleiro[def[0]][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* 
        Verifica, para as celulas encostadas à parte de baixo do labirinto, se a celula
        acima da celula em causa é branca, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[0] + 1 > dim[0]){
            if(tabuleiro[def[0] - 2][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
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
        Verifica, para as celulas encostadas ao lado esquerdo do labirinto, se a celula
        a direita da celula em causa é branca, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[1] - 2 < 0){
            if(tabuleiro[def[0] - 1][def[1]] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* 
        Verifica, para as celulas encostadas ao lado direito do labirinto, se a celula
        a esquerda da celula em causa é branca, se sim entao a celula cinzenta e quebravel
        porque pode haver continuacao do caminho. */
        if(def[1] + 1 > dim[1]){
            if(tabuleiro[def[0] - 1][def[1] - 2] == 0){
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

}