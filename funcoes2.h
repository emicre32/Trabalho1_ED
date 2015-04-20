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


//Função que cria a head da lista de bairros
void incia_bairro()
{
    nhood *head_bairro = (nhood*) alloc(sizeof(struct Bairro)); 
    head_bairro->proxb = NULL;
}

// FUNÇÃO QUE ALOCA UM ESPAÇO DE MEMORIA PARA UM BAIRRO, SE HOUVER MEMORIA
nhood *aloca_bairro(int id, char *nome)
{
    int pos=0;

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
        printf("Bairro %s cadastrado coom sucesso\n", novobairro->nome_bairro);
        return novobairro;
    }
    
}

//FUNCAO QUE INSERE UM BAIRRO NO INICIO DA LISTA DE BAIRROS
nhood *insereinicio_bairro(int id, char *nome)
{
    
     nhood *novo = aloca_bairro(id, nome);
     nhood *old_primeiro = head_bairro->proxb; //armazenando o endereço do primeiro bairro

     head_bairro->proxb = novo; //colocando o bairro desejado no primeiro lugar da lista
     novo->proxb = old_primeiro;
     return novo;

}

//FUNCAO QUE INSERE UM BAIRRO EM QUALQUER LUGAR DA LISTA DE BAIRROS
nhood *insere_bairro(int id, char *nome)
{

    if(id < head_bairro->proxb->id_bairro)
    {
        insereinicio_bairro(id, nome);
        return novo;
    } 
    else 
    {   /* bairro_atual e bairro_anteior são ponteiros que percorrem a 
        lista até achar o lugar correto para inserir o bairro desejado*/
        nhood *bairro_atual = head_bairro->proxb;
        nhood *bairro_anterior = head_bairro;
        nhood *novo = aloca_bairro(id, nome);
        /*os ponteiros avançam na lista até achar um bairro que tenham
         um numero de id maior que o desejado*/
        while(id > bairro_atual->id_bairro)
        {
            bairro_anterior = bairro_atual;
            bairro_atual = bairro_atual->proxb;
        }
        /*se o bairro já esta cadastrado, a função é abortada*/
        if(id == bairro_atual->id_bairro)
        {
            printf("Esse bairro ja foi cadastrado!\n");
            break;
        } 
        else 
        {
            bairro_anterior->proxb = novo;
            novo->proxb = bairro_atual;
            return novo;
        }   

    }   
}

street aloca_rua(int idBairro, int id, char *nome)


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
