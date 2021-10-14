/******************************************************************************
 * NOME
 *   roap.c
 *
 * DESCRICAO
 *   Implementa funcoes para...
 *
 * COMENTARIOS
 *   ....
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "roap.h"
#include "ReadFile.h"

/******************************************************************************
 * main ()
 *
 * Argumentos: argc   - ...
 *             **argv - ...
 * Retorna: 0
 * Efeitos colaterais: nenhum
 *
 * Descricao: ...
 *              
 *              
 *              
 *              
 * 
 *****************************************************************************/
int main(int argc,char **argv){
    SetCoordinates(argv);
    return 0;
}


/******************************************************************************
 * SetCoordinates ()
 *
 * Argumentos: **argv - ...
 *             
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
void SetCoordinates(char **argv){
    ReadFile(argv);
}
