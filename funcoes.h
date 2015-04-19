#include <stdio.h>
#include <stdlib.h>


struct Casa
{
    int id_consumidor;
    int casa;
    float consumo;
    char *nome_consumidor;
    struct Casa *proxc;
}

typedef struct Casa house;

struct Rua
{
    int id_rua;
    char *nome_rua;
    house *head_casa;
    struct Rua *proxr;
    
}

typedef struct Rua street;

struct Bairro
{
    int id_bairro;
    char *nome_bairro;
    street *head_rua;
    struct Bairro *proxb;
}

typedef struct Bairro nhood;


//ALOCA MEMORIA PARA BAIRRO SE HOUVER MEMORIA DISPONIVEL
nhood aloca_bairro()
{
    nhood *novobairro = (nhood*) malloc(sizeof(struct Bairro));
    if(!novo)
    {
        printf("ERROR: NAO HA MEMORIA DISPONIVEl!\n");
        exit(1);
    }
    else
    {
        printf("Bairro cadastrado coom sucesso\n");
    }

}

// INSERE BAIRRO NA CIDADE
nhood insere_bairro(int id, char *nome)
{
    nhood *novobairro = (nhood*) malloc(sizeof(struct Bairro)); 
    if(!novobairro)
    {
        printf("ERROR: NAO HA MEMORIA DISPONIVEl!\n");
        exit(1);
    }
    else
    {
        novobairro->id_bairro = (int*) malloc(sizeof(int));
        novobairro->id_bairro = id;
        novobairro->nome_bairro = (char*) malloc( strlen(nome)+1*sizeof(char) );
        strcpy (novobairro->nome_bairro, nome);
        novobairro->head_rua = NULL;
        novobairro->proxb = NULL;
        printf("Bairro %s cadastrado coom sucesso\n", novobairro->nome_bairro);
        return novo_bairro;
    }
    
}


//VERIFICA SE O BAIRRO TEM RUAS CADASTRADAS OU ESTA VAZIO
int bairro_vazio(nhood *BAIRRO)
{
    if(BAIRRO->head_rua == NULL) 
    {
        printf("Ainda nao ha nenhuma rua cadastrada nesse bairro.\n");
        return true;
    }
    else return false;
}


// SOCORRRRRORROROROROROROROOOOOOOOO
street insere_rua(nhood *bairro, int id, char *nome)
{
    street *novarua = (street*) malloc(sizeof(struct Rua));
    if(!novarua)
    {
        printf("ERROR: NAO HA MEMORIA DISPONIVEL");
        exit(1);
    }
    else
    {
        bairro->
    }
}




