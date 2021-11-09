#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "SolveTab.h"

static Coord *gP;
static int gN;

void Init(int pSize){
    gP = (Coord*)malloc(pSize * sizeof(Coord));
    gN = 0;
}

void Push(Coord pI){
    gP[gN++] = pI;
    printf("%d\n",gN);
}

int IsEmpty(){
    if(gN == 0)
        return 1;
    return 0;    
}
Coord Pop(){
    return gP[gN--];
}
