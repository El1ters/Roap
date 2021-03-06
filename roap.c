/************************************************************************************
 * NOME
 *   roap.c
 *
 * DESCRICAO
 *   Contem as funçoes que permitem a resolucao do problema final (ver se existe
 *   caminho de uma celula inicial para uma celula final e se sim indicar qual o
 *   caminho de menor custo).
 *
 ************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ReadFile.h"
#include "SolveTab.h"



/******************************************************************************
 * main ()
 *
 * Argumentos: argc -> Contador do numero de argumentos inseridos no terminal.
 *             argv -> Ponteiro que aponta para um vetor de strings que contém 
 *                     os argumentos do terminal. 
 * 
 * Retorna: 0 quando o programa termina.
 *              
 *****************************************************************************/
int main(int argc,char **argv){
    ReadFile(argv);
    return 0;
}

