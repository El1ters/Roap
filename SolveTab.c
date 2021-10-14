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
 * Argumentos: **tabuleiro - ...
 *             *mode       - ...
 *             *def        - ...
 *             *dim        - ...
 *             *fp1        - ...
 * Retorna: (void)
 * Efeitos colaterais: ...
 *
 * Descricao: ...
 *              
 *              
 *              
 *              
 * 
 *****************************************************************************/
void SolveTab(int **tabuleiro,char *mode,int *def,int *dim,FILE *fp1){
    if((def[0] <= 0 || def[0] > dim[0]) || (def[1] <= 0 || def[1] > dim[1])){
        fprintf(fp1,"-2\n\n");
        return;
    }

    if(strcmp(mode,"A1") == 0){
        fprintf(fp1,"%d\n\n",tabuleiro[def[0] - 1][def[1] - 1]);
    }

    if(strcmp(mode,"A2") == 0){
        if(def[0] - 2 >= 0){
            if(tabuleiro[def[0] - 2][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[0] + 1 <= dim[0]){
            if(tabuleiro[def[0]][def[1] - 1] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[1] - 2 >= 0){
            if(tabuleiro[def[0] - 1][def[1] - 2] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[1] + 1 <= dim[1]){
            if(tabuleiro[def[0] - 1][def[1]] == 0){
                fprintf(fp1,"1\n\n");
                return;
            }  
        }
            
        fprintf(fp1,"0\n\n");
        return;
    }

    if(strcmp(mode,"A3") == 0){
         if(def[0] - 2 >= 0){
            if(tabuleiro[def[0] - 2][def[1] - 1] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[0] + 1 <= dim[0]){
            if(tabuleiro[def[0]][def[1] - 1] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[1] - 2 >= 0){
            if(tabuleiro[def[0] - 1][def[1] - 2] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[1] + 1 <= dim[1]){
            if(tabuleiro[def[0] - 1][def[1]] > 0){
                fprintf(fp1,"1\n\n");
                return;
            }  
        }
        fprintf(fp1,"0\n\n");
        return;
    }

    if(strcmp(mode,"A4") == 0){
         if(def[0] - 2 >= 0){
            if(tabuleiro[def[0] - 2][def[1] - 1] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[0] + 1 <= dim[0]){
            if(tabuleiro[def[0]][def[1] - 1] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[1] - 2 >= 0){
            if(tabuleiro[def[0] - 1][def[1] - 2] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }
        }
        if(def[1] + 1 <= dim[1]){
            if(tabuleiro[def[0] - 1][def[1]] == -1){
                fprintf(fp1,"1\n\n");
                return;
            }  
        }
        fprintf(fp1,"0\n\n");
        return;
    }
    if(strcmp(mode,"A5") == 0){
        if(tabuleiro[def[0] - 1][def[1] - 1 == 0 || tabuleiro[def[0] - 1]][def[1] - 1] == -1){
            fprintf(fp1,"-1\n\n");
        }
    }

}
