#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes2.h"


int main() {

    FILE * mapa;
    char palavra[5];

    mapa = abrirMapa();

    fscanf(mapa, "%s", palavra);
    printf("%s\n", palavra);
    fscanf(mapa, "%s", palavra);
    printf("%s\n", palavra);


    return 0;
}
