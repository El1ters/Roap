/******************************************************************************
 * NOME
 *   ReadFile.c
 *
 * DESCRICAO
 *   Contem as funcoes que irao permitir ler os ficheiros de entrada 
 *   fornecidos, alocando espaço necessario para os guardar.
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
 * Argumentos: argv -> ponteiro que aponta para um vetor de strings que contém
 *                     os argumentos do terminal.
 *             
 * Retorna: (void).
 *
 * Descricao: Esta funçao vai ler os dados do ficheiro de entrada escolhido.
 *              
 *****************************************************************************/
void ReadFile(char **argv){
    FILE *fp,*fp1; /* Ficheiros de entrada e de saida, respetivamente. */
    int **tabuleiro = NULL; /* Vetor bidimensional que vai guardar os dados do fiheiro de entrada. */
    int flag = 1; /* Variavel auxiliar que permite saber que linha do ficheiro de entrada estamos a ler. */ 
    int number_of_lines = 100; /* Variavel auxiliar que contem o numero de celulas. */
    int count = 0; /* Variavel auxiliar que conta o numero de coordenadas lidas. */
    int dim[2]; /* Vetor que guarda as dimensoes do labirinto. */
    int def[2]; /* Vetor que guarda as coordenadas da celula da 2ª linha do ficheiro de entrada. */
    int linha; /* Numero de linhas dos labirintos. */
    int coluna; /* Numero de colunas dos labirintos. */
    int cell; /* Variavel auxiliar que vai guardar as celulas dos labirintos. */
    char mode[3]; /* Vetor que guarda o modo das variantes de funcionamento. */
    int sec[2] = {0,0};/* Inicializacao de um vetor que ira conter as coordendas do ponto de chegada do labirinto para a variedade de funcionamento A6. */
    int no_allocation = 0;

    /* 
    Filename fica a apontar para a posicao de memoria que contem o nome do ficheiro de saida
    atraves da chamada a funcao getfilename. */
    char *filename = getfilename(argv); 

    /*
    Acrescenta ao ficheiro de saida o "".sol1". */
    strcat(filename,".sol1");

    /* 
    Condicao de erro para o ficheiro de entrada. */
    if((fp = fopen(argv[2],"r")) == NULL){
        free(filename);
        exit(0);
    }
    /* 
    Condicao de erro para o ficheiro de saida. */
    if((fp1 = fopen(filename,"w")) == NULL){   
        exit(0);
    }

    /* 
    Leitura do ficheiro de entrada -> os cases permitem ler as 3 primeiras linhas do ficheiro;
                                   -> o default permite ler as restantes. */
    while(!feof(fp)){
        switch (flag){
            case 0:
                break;
            case 1:
                if(fscanf(fp,"%d %d",&dim[0],&dim[1]) != 2){
                    fclose(fp);
                    fclose(fp1);
                    free(filename);
                    return;
                }
                break;
            case 2:
                if(fscanf(fp,"%d %d %s",&def[0],&def[1],mode) != 3){
                    return;
                }
                if(outside(def[0],def[1],dim) == 1){
                    no_allocation = 1;
                    fprintf(fp1,"-2\n\n");
                }
                if(strcmp(mode,"A6") == 0){
                    if(fscanf(fp,"%d %d",&sec[0],&sec[1]) != 2){
                        return;
                    }
                    if(outside(sec[0],sec[1],dim) == 1){
                        if(outside(def[0],def[1],dim) == 1){
                            break;
                        }
                        no_allocation = 1;
                        fprintf(fp1,"-2\n\n");
                    }   
                }
                if(no_allocation == 0){
                    tabuleiro = Allocate(dim[0],dim[1]);
                } 
                break;
            case 3:
                if(fscanf(fp,"%d",&number_of_lines) != 1)
                    return;
                break;
            default:
                if(fscanf(fp,"%d %d %d",&linha,&coluna,&cell) != 3)
                    return;

                if(no_allocation == 0){
                    tabuleiro[linha - 1][coluna - 1] = cell;
                }
                break;
        }
        if(count == number_of_lines){
            flag = 0;
            if(no_allocation == 0){
                SolveTab(tabuleiro,mode,def,sec,dim,fp1);
                for(int k = 0;k < dim[0];k++){
                    free(tabuleiro[k]);
                } 
                    free(tabuleiro);
            }
            no_allocation = 0;
            count = 0;
        }else{
            flag++;
        }
        if(flag > 3){
            count++;
        }  
    }
}
int outside(int L,int C,int *dim){
    if((L <= 0 || L > dim[0]) || (C <= 0 || C > dim[1])){
        return 1;
    }
    return 0;
}
/******************************************************************************
 * **Allocate ()
 *
 * Argumentos: lines   -> numero de linhas dos labirintos.
 *             columns -> numero de colunas dos labirirntos.
 * 
 * Retorna: tab -> o labirinto com as dimensoes pedidas e com as celulas nas
 *                 coordenadas certas.
 *
 * Descricao: Esta funcao permite alocar o espaco necessario para gerar os 
 *            labirintos.
 *              
 *****************************************************************************/
int **Allocate(int lines, int columns){

    int **tab; 
    int i;

    tab = (int**)calloc(lines,sizeof(int*));
    if( tab == NULL){
        exit(0);
    }
    for(i = 0; i < lines; i++){
        tab[i] = (int*)calloc(columns,sizeof(int));
            if(tab[i] == NULL){
                exit(0); 
            }
    }
    return tab;    
}


/******************************************************************************
 * *getfilename ()
 *
 * Argumentos: argv -> ponteiro que aponta para um vetor de strings que contém
 *                     os argumentos do terminal.
 * 
 * Retorna: b -> b vai apontar para uma posicao de memoria onde se encontra a
 *               string correspondente ao nome que vai ser atribuido ao ficheiro
 *               de saida (que vai ser igual ao do ficheiro de entrada).  
 *
 * Descricao: Esta funcao permite que o ficheiro de saida tenha o mesmo nome
 *            que o ficheiro de entrada, mudando apenas a diretoria final
 *            (passa por exemplo de .in1 para .sol1 sendo que o que está
 *            a esquerda do ponto final e igual nos dois ficheiros). 
 *              
 *****************************************************************************/
char *getfilename(char *argv[]){

    char *a = NULL;
    char *b = NULL;
    int k = 0;
    if(argv[2] == NULL){
        return NULL;
    }
    for(a = argv[2]; *a != '\0'; a++, k++);
    b = (char*)calloc(sizeof(char), k + 2);
    for(a--; *a != '.';a--,k--);
    strncpy(b,argv[2],k - 1);
    return b;
}