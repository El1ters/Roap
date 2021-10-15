/******************************************************************************
 * NOME
 *   SolveTab.c
 *
 * DESCRICAO
 *   Implementa funcoes para...
 *
 * COMENTARIOS
 *   ....
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/******************************************************************************
 * SolveTab ()
 *
 * Argumentos: tabuleiro - Um ponteiro para um array de inteiros que contem o labirinto.
 *             mode      - Ponteiro para as variantes de funcionamento.
 *             def       - Ponteiro para as coordenadas da celula da 2ª linha do ficheiro de entrada.
 *             dim       - Ponteiro para a dimensao dos labirintos.
 *             fp1       - Ponteiro para o ficheiro de saida onde sao escritas as soluçoes ao problema.
 * Retorna: (void)
 *
 * Descricao: Esta funcao permite dar resposta ao problema inicial face as diferentes variantes
 *            de funcionamento.
 *     
 *****************************************************************************/
void SolveTab(int **tabuleiro,char *mode,int *def,int *dim,FILE *fp1){

    /* Condicao que verifica se as coordendas estao fora do labirinto, se sim retorna -2 */
    if((def[0] <= 0 || def[0] > dim[0]) || (def[1] <= 0 || def[1] > dim[1])){
        fprintf(fp1,"-2\n\n");
        return;
    }

    /* Condicao que permite resolver a variante de funcionamento A1 */
    if(strcmp(mode,"A1") == 0){
        fprintf(fp1,"%d\n\n",tabuleiro[def[0] - 1][def[1] - 1]);
    }

    /* Condicao que permite resolver a variante de funcionamento A2 */
    if(strcmp(mode,"A2") == 0){

        /* Verifica se a celula a esquerda da celula em causa esta no tabuleiro e se é branca */
        if(def[0] - 2 >= 0){
            if(tabuleiro[def[0] - 2][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula a direita da celula em causa esta no tabuleiro e se é branca */
        if(def[0] <= dim[0]){
            if(tabuleiro[def[0]][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula acima da celula em causa esta no tabuleiro e se é branca */
        if(def[1] - 2 >= 0){
            if(tabuleiro[def[0] - 1][def[1] - 2] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula abaixo da celula em causa esta no tabuleiro e se é branca */
        if(def[1] <= dim[1]){
            if(tabuleiro[def[0] - 1][def[1]] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }  
        }
            
        fprintf(fp1,"0\n\n");
        return;
    }

    /* Condicao que permite resolver a variante de funcionamento A3 */
    if(strcmp(mode,"A3") == 0){

        /* Verifica se a celula a esquerda da celula em causa esta no tabuleiro e se é cinzenta */
         if(def[0] - 2 >= 0){
            if(tabuleiro[def[0] - 2][def[1] - 1] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula a direita da celula em causa esta no tabuleiro e se é cinzenta */
        if(def[0] < dim[0]){
            if(tabuleiro[def[0]][def[1] - 1] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula acima da celula em causa esta no tabuleiro e se é cinzenta */
        if(def[1] - 2 >= 0){
            if(tabuleiro[def[0] - 1][def[1] - 2] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula abaixo da celula em causa esta no tabuleiro e se é cinzenta */
        if(def[1] < dim[1]){
            if(tabuleiro[def[0] - 1][def[1]] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }  
        }
        fprintf(fp1,"0\n\n");
        return;
    }

    /* Condicao que permite resolver a variante de funcionamento A4 */
    if(strcmp(mode,"A4") == 0){

        /* Verifica se a celula a esquerda da celula em causa esta no tabuleiro e se é preta */
         if(def[0] - 2 >= 0){
            if(tabuleiro[def[0] - 2][def[1] - 1] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula a direita da celula em causa esta no tabuleiro e se é preta */
        if(def[0] < dim[0]){
            if(tabuleiro[def[0]][def[1] - 1] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula acima da celula em causa esta no tabuleiro e se é preta */
        if(def[1] - 2 >= 0){
            if(tabuleiro[def[0] - 1][def[1] - 2] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula abaixo da celula em causa esta no tabuleiro e se é preta */
        if(def[1] < dim[1]){
            if(tabuleiro[def[0] - 1][def[1]] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }  
        }
        fprintf(fp1,"0\n\n");
        return;
    }

    /* Condicao que permite resolver a variante de funcionamento A5 */
    if(strcmp(mode,"A5") == 0){

        /* Verifica se a celula em causa e preta ou branca, retornando -1 se sim */
        if(tabuleiro[def[0] - 1][def[1] - 1] == 0 || tabuleiro[def[0] - 1][def[1] - 1] == -1){
            fprintf(fp1,"-1\n\n");
            return;
        }

        /* Verifica se a celula a direita da celula em causa esta no labirinto e é branca, se sim 
        entao a celula cinzenta e quebravel porque pode haver continuicao do caminho */
        if(def[0] - 2 < 0){
            if(tabuleiro[def[0]][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula a esquerda da celula em causa esta no labirinto e é branca, se sim 
        entao a celula cinzenta e quebravel porque pode haver continuicao do caminho */
        if(def[0] > dim[0]){
            if(tabuleiro[def[0] - 2][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        /* Verifica se a celula a esquerda da celula em causa esta no labirinto e é branca, se sim 
        entao a celula cinzenta e quebravel porque pode haver continuicao do caminho */
        if(def[0] - 2 >= 0 && def[0] < dim[0]){
            printf("def[0]-2:%d def[1]-1:%d def[0]:%d\n",def[0] - 2,def[1] - 1,def[0]);
            if(tabuleiro[def[0] - 2][def[1] - 1] == 0 && tabuleiro[def[0]][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        if(def[1] - 2 < 0){
            if(tabuleiro[def[0] - 1][def[1]] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }

        if(def[1] > dim[1]){
            if(tabuleiro[def[0] - 1][def[1] - 2] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        
        if(def[1] - 2 >= 0 && def[1] < dim[1]){
            if(tabuleiro[def[0] - 1][def[1] - 2] == 0 && tabuleiro[def[0] - 1][def[1]] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
    }

}