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
#include "Graph.h"
#include "Dijkstra.h"

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
    int number_of_lines = 1; /* Variavel auxiliar que contem o numero de celulas. */
    int count = 0; /* Variavel auxiliar que conta o numero de coordenadas lidas. */
    int dim[2]; /* Vetor que guarda as dimensoes do labirinto. */
    int def[2];  /* Vetor que guarda as coordenadas da celula da 2ª linha do ficheiro de entrada. */
    int linha; /* Numero de linhas dos labirintos. */
    int coluna; /* Numero de colunas dos labirintos. */
    int cell; /* Variavel auxiliar que vai guardar as celulas dos labirintos. */
    int no_allocation = 0; /* Flag que vai permitir saber se devemos ou nao alocar espaco para o nosso labirinto. */
    Graph *G;
    int different_cells = 0; /* Variavel que vai guardar o numero de salas diferentes do labirinto. */
    

    //extensionName(argv); 
    /* 
    Filename fica a apontar para a posicao de memoria que contem o nome do ficheiro de saida
    atraves da chamada a funcao getfilename. */
    char *filename = getfilename(argv);
 
    /*
    Acrescenta ao ficheiro de saida o "".sol1". */
    strcat(filename,".sol"); 
    /* 
    Condicao de erro para o ficheiro de entrada. */
    fp = fopen(argv[1],"r");
    if(fp == NULL){ 
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
                if(fscanf(fp,"%d %d",&def[0],&def[1]) != 2){
                    fclose(fp);
                    fclose(fp1);
                    free(filename);
                    return;
                }
                if(dim[0] <= 0 || dim[1] <= 0){
                    no_allocation = 1;
                }
                if(outside(def[0],def[1],dim) == 1){
                    no_allocation = 1;
                    fprintf(fp1,"-1\n\n\n");
                }
                
                break;
            case 3:
                if(fscanf(fp,"%d",&number_of_lines) != 1){
                    fclose(fp);
                    fclose(fp1);
                    free(filename);
                    return;
                }

                if(number_of_lines == 0){
                    no_allocation = 1;
                }

                if(no_allocation == 0){
                    tabuleiro = Allocate(dim[0],dim[1]);
                } 
                    
                break;
            default:
                if(fscanf(fp,"%d %d %d",&linha,&coluna,&cell) != 3){
                    fclose(fp);
                    fclose(fp1);
                    free(filename);
                    return;
                }   
                if(no_allocation == 0){
                    tabuleiro[linha - 1][coluna - 1] = cell;
                }
                break;
        }
        if(count == number_of_lines){
            int k = 0;
            if(number_of_lines == 0){
                fprintf(fp1,"0\n\n\n");
            }
            if(no_allocation == 0 && number_of_lines != 0 && tabuleiro[0][0] != 0 && k == 0){
                fprintf(fp1,"-1\n\n\n");
                k = 1;
            }
            if(no_allocation == 0 && number_of_lines != 0 && tabuleiro[def[0] - 1][def[1] - 1] != 0 && k == 0){
                fprintf(fp1,"-1\n\n\n");
                k = 1;
            }
            if(no_allocation == 0){
                FillBoard(tabuleiro,&different_cells,dim,number_of_lines);                
                if(different_cells == 1){
                    fprintf(fp1,"0\n\n\n");
                    k = 1;
                }
                if(k == 0){
                    G = CreateGraph(tabuleiro,dim,different_cells);
                    Dijkstra(G,different_cells,-2,tabuleiro[def[0] - 1][def[1] - 1],fp1);
                    FreeGraph(G,different_cells);
                }
                for(int k = 0;k < dim[0];k++){
                    free(tabuleiro[k]);
                }    
                    free(tabuleiro);
            }
            no_allocation = 0;
            number_of_lines = 1;
            count = 0;
            flag = 0;
            different_cells = 0;
        }else{
            flag++;
        }
        if(flag > 3){
            count++;
        }  
    }
    fclose(fp);
    fclose(fp1);
    free(filename);
}


/******************************************************************************
 * outside ()
 *
 * Argumentos: L   -> numero da linha dos labirintos.
 *             C   -> numero da coluna dos labirirtos.
 *             dim -> Ponteiro para a posicao de memoria onde esta a 
 *                          dimensao dos labirintos.
 * 
 * Retorna: 1 -> se uma celula esta fora do labirinto.
 *          0 -> se um celula esta dentro do labirinto.
 *
 * Descricao: Esta funcao permite saber se uma celula esta ou nao dentro do
 *            labirinto.
 *              
 *****************************************************************************/
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
 *             columns -> numero de colunas dos labirintos.
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
    if(argv[1] == NULL){
        exit(0);
    }

    for(a = argv[1]; *a != '\0'; a++, k++);
    b = (char*)calloc(sizeof(char), k + 2);
    for(a--; *a != '.';a--,k--);
    strncpy(b,argv[1],k - 1);
    return b;
}


/******************************************************************************
 * extensionName ()
 *
 * Argumentos: argv -> ponteiro que aponta para um vetor de strings que contém
 *                     os argumentos do terminal.
 * 
 * Retorna: (void).
 * 
 * Descricao: Esta funcao apenas serve para verificar se os ultimos 3 caracteres
 *            do ficheiro teste de entrada sao in1. Se nao for da-se um exit(0).
 *              
 *****************************************************************************/
void extensionName(char *argv[]){

    char *a = NULL;
    int k = 0;
    if(argv[1] == NULL){
        exit(0);
    }

    for(a = argv[1]; *a != '\0'; a++, k++);
    for(a--; *a != '.';a--,k--);
    a++;
    if(strcmp(a,"in") != 0){
        exit(0);
    }
    return;
}