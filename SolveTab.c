#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void SolveTab(int **tabuleiro,char *mode,int *def,int *dim,FILE *fp1){
    if((def[0] <= 0 || def[0] > dim[0]) || (def[1] <= 0 || def[1] > dim[1])){
        fprintf(fp1,"-2\n\n");
        return;
    }

    if(strcmp(mode,"A1") == 0){
        fprintf(fp1,"%d\n\n",tabuleiro[def[0] - 1][def[1] - 1]);
    }
    if(strcmp(mode,"A2") == 0){
        int linha,coluna;
        for(linha = def[0] - 2; linha <= def[0]; linha++){
            for(coluna = def[1] - 2 ; coluna <= def[1]; coluna++){ 
                if((linha == (def[0] - 1)) && (coluna == (def[1] - 1))){
                    continue;
                }
                      
                if(linha < 0 || coluna < 0 || (linha > dim[0]) || (coluna > dim[1])){
                    continue;
                }
                
                if(tabuleiro[linha][coluna] == 0){
                    fprintf(fp1,"1\n\n");
                    return;
                }
            }
        }
        fprintf(fp1,"0\n\n");
        return;
    }

}