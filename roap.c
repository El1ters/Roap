/******************************************************************************
 * NOME
 *   roap.c
 *
 * DESCRICAO
 *   Contem as funcoes que permitem a resolucao do problema pedido (ler dados
 *   do ficheiro de entrada e de acordo com as diferentes formas de
 *   funcionamento escrever a solucao num ficheiro de saida).
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roap.h"
#include "ReadFile.h"

/******************************************************************************
 * main ()
 *
 * Argumentos: argc -> contador do numero de argumentos inseridos no terminal.
 *             argv -> ponteiro que aponta para um vetor de strings que contém 
 *                     os argumentos do terminal. 
 * 
 * Retorna: 0 quando o programa termina.
 *              
 *****************************************************************************/
int main(int argc,char **argv){
    if(strcmp(argv[1],"-s") == 0){
        ReadFile(argv);
    }
    return 0;
}