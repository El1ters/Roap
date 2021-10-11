#include <stdlib.h>
#include <stdio.h>
#include "ReadFile.h"
#include "SolveTab.h"

void ReadFile(char **argv){
    FILE *fp,*fp1;
    int **tabuleiro = NULL;
    int flag = 1, number_of_lines = 100, count = 0, dim[2],def[2],linha,coluna,cell;
    char mode[3];  

    if((fp = fopen(argv[1],"r")) == NULL){
        printf("could not open the file");
        exit(EXIT_FAILURE);
    }

    if((fp1 = fopen("teste.sol","w")) == NULL){
        printf("could not open the file");
        exit(EXIT_FAILURE);
    }

    while(!feof(fp)){
        switch (flag){
            case 0:
                break;
            case 1:
                if(fscanf(fp,"%d %d",&dim[0],&dim[1]) != 2){
                    fclose(fp);
                    fclose(fp1);
                    return;
                }else{
                    tabuleiro = Allocate(dim[0],dim[1]);
                }
                break;
            case 2:
                if(fscanf(fp,"%d %d %s",&def[0],&def[1],mode) != 3)
                    return;
                break;
            case 3:
                if(fscanf(fp,"%d",&number_of_lines) != 1)
                    return;
                break;
            default:
                if(fscanf(fp,"%d %d %d",&linha,&coluna,&cell) != 3)
                    return;
                tabuleiro[linha - 1][coluna - 1] = cell;
                break;
        }
        if(count == number_of_lines){
            flag = 0;
            SolveTab(tabuleiro,mode,def,dim,fp1);
            for(int k = 0;k < linha;k++){
                free(tabuleiro[k]);
            } 
                free(tabuleiro);
            count = 0;
        }else{
            flag++;
        }
        if(flag > 3){
            count++;
        }  
    }
}

int **Allocate(int lines, int columns){
    int **tab;
    int i;
    tab = (int**)calloc(lines,sizeof(int*));
    if( tab == NULL){
        printf("allocation not possible\n");/*substituir por fprintf*/
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < lines;i++){
        tab[i] = (int*)calloc(columns,sizeof(int));
            if(tab[i] == NULL){
                printf("allocation not possible\n");/*substituir por fprintf*/
                exit(EXIT_FAILURE); 
            }
    }
    return tab;    
}