/******************************************************************************
 * NOME
 *   ReadFile.h
 *
 * DESCRICAO
 *   Contem os cabecalhos das funcoes utilizadas no ReadFile.h.
 *
 ******************************************************************************/
#ifndef READFILE
#define READFILE

void ReadFile();
int **Allocate(int lines, int columns);
char *getfile(char *argv[]);

#endif