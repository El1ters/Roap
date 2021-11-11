/******************************************************************************
 * NOME
 *   ReadFile.h
 *
 * DESCRICAO
 *   Contem os cabecalhos das funcoes utilizadas no ReadFile.c.
 *
 ******************************************************************************/
#ifndef READFILE
#define READFILE

void ReadFile();
int **Allocate(int lines, int columns);
char *getfilename(char *argv[]);
int outside(int L,int C,int *dim);
void extensionName(char *argv[]);

#endif