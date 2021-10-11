#include <stdio.h>
#include <stdlib.h>
#include "roap.h"
#include "ReadFile.h"


int main(int argc,char **argv){
    SetCoordinates(argv);
    return 0;
}

void SetCoordinates(char **argv){
    ReadFile(argv);
}
