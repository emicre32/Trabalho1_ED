#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Casa
{
    int id_consumidor;
    int id_casa;
    float consumo;
    char *nome_consumidor;
    struct house *proxc;
} house;


typedef struct Rua
{
    int id_rua;
    char *nome_rua;
    house *head_casa;
    struct Rua *proxr;
    
} street;
    

typedef struct Bairro
{
    int id_bairro;
    char *nome_bairro;
    street *head_rua;
    struct Bairro *proxb;
} nhood;


// INSERE BAIRRO NA CIDADE
nhood * insere_bairro(int id, char *nome)
{
    nhood *novobairro = (nhood*) malloc(sizeof(struct Bairro)); 
    if(!novobairro)
    {
        printf("ERROR: NAO HA MEMORIA DISPONIVEl!\n");
        exit(1);
    }
    else
    {
        novobairro->id_bairro = id;
        novobairro->nome_bairro = (char*) malloc( strlen(nome)+1*sizeof(char) );
        strcpy (novobairro->nome_bairro, nome);
        novobairro->head_rua = NULL;
        novobairro->proxb = NULL;
        printf("Bairro %s cadastrado coom sucesso\n", novobairro->nome_bairro);
        return novobairro;
    }
    
}

// Inserir Rua
street * insere_rua(int idBairro, int id, char *nome)
{
    street *novarua = (street*) malloc(sizeof(struct Rua));
    if(!novarua)
    {
        printf("ERROR: NAO HA MEMORIA DISPONIVEL");
        exit(1);
    }
    else
    {
        novarua->id_rua = id;
        novarua->nome_rua = (char*)malloc(strlen(nome)+1*sizeof(char));
        strcpy(novarua->nome_rua, nome);
        novarua->proxr = NULL;            
        }
    return(novarua);
}

FILE * abrirMapa()
{
    char nome[15];
    FILE * arq;

    printf("Digite o nome do arquivo fonte: \n");
    gets(nome);
    //nome = (char*)malloc(strlen(nome)+1*sizeof(char));

    arq = fopen(nome, "r");

    return(arq);
}
