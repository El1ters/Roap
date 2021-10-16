/******************************************************************************
 * NOME
 *   ReadFile.c
 *
 * DESCRICAO
 *   Implementa funcoes que irao permitir ler os ficheiros de entrada fornecidos,
 *   alocando espaço necessario para os guardar.
 *   
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ReadFile.h"
#include "SolveTab.h"

/******************************************************************************
 * ReadFile ()
 *
 * Argumentos: argv - ponteiro que aponta para um vetor de strings que contém os argumentos do terminal.
 *             
 * Retorna: (void)
 *
 * Descricao: Esta funçao vai ler os dados do ficheiro de entrada escolhido.
 *              
 *****************************************************************************/
void ReadFile(char **argv){
    FILE *fp,*fp1; /* Ficheiro de entrada e de saida, respetivamente */
    int **tabuleiro = NULL; /* Vetor bidimensional que vai guardar os dados do fiheiro de entrada */
    int flag = 1; /* Variavel auxiliar que permite saber que linha do ficheiro de entrada estamos a ler */ 
    int number_of_lines = 100; /* Variavel auxiliar que contem o numero de celulas */
    int count = 0; /* Variavel auxiliar que conta o numero de coordenadas lidas */
    int dim[2]; /* Vetor que guarda as dimensoes do labirinto */
    int def[2]; /* Vetor que guarda as coordenadas da celula da 2ª linha do ficheiro de entrada */
    int linha; /* Numero de linhas dos labirintos */
    int coluna; /* Numero de colunas dos labirintos */
    int cell; /* Variavel auxiliar que vai guardar as celulas dos labirintos */
    char mode[3]; /* Vetor que guarda o modo das variantes de funcionamento */

    /* Condicao de erro para o ficheiro de entrada */
    if((fp = fopen(argv[1],"r")) == NULL){
        printf("could not open the file");
        exit(EXIT_FAILURE);
    }
    /* Condicao de erro para o ficheiro de saida */
    if((fp1 = fopen("teste.sol","w")) == NULL){
        printf("could not open the file");
        exit(EXIT_FAILURE);
    }

    /* Leitura do ficheiro de entrada -> os cases permitem ler as 3 primeiras linhas do ficheiro;
                                      -> o default permite ler as restantes. 
    */
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

/******************************************************************************
 * **Allocate ()
 *
 * Argumentos: lines   - numero de linhas dos labirintos.
 *             columns - numero de colunas dos labirirntos.
 * 
 * Retorna: tab - o labirinto com as dimensoes pedidas e com as celulas nas coordenadas certas.
 *
 * Descricao: esta funcao permite alocar o espaco necessario para gerar os labirintos.
 *              
 *****************************************************************************/
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

char *getfile(char *argv[]){
    char *a = argv[1], *b = NULL;
    int k = 0;
    b = (char*)calloc(sizeof(char),strlen(argv[1]));
    for(a = argv[1]; *a != '\0'; a++, k++);
    for(a--; *a != '.';a--,k--);
    strncpy(b,argv[1],k-1);
    return b;
}