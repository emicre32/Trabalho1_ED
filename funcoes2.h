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
    int *id_bairro;
    char *nome_bairro;
    street *head_rua;
    struct Bairro *proxb;
} nhood;






// FUNÇÃO PARA ABRIR O ARQUIVO FONTE ---------------------------------------------------------------------------//
FILE * abrirMapa()
{
    char * nome;
    FILE * arq;

    nome = (char*)malloc(30*sizeof(char));

    while(1)
    {
    printf("Digite o nome do arquivo fonte: \n");
    scanf("%s", nome);

    arq = fopen(nome, "r");

    if (arq == NULL) printf("O arquivo nao foi encontrado.\n");
        else break;
    }

    free(nome);

    return(arq);
}







// FUNCOES PARA BAIRRO ---------------------------------------------------------------------------//


//Função que cria a head da lista de bairros
nhood * inicia_bairro()
{
    nhood *head_bairro = (nhood*) malloc(sizeof(struct Bairro)); 
    head_bairro->proxb = NULL;

    return(head_bairro);
}

// FUNÇÃO QUE ALOCA UM ESPAÇO DE MEMORIA PARA UM BAIRRO, SE HOUVER MEMORIA
nhood * insere_bairro(int *id, char *nome)
{
    nhood *novobairro = (nhood*) malloc(sizeof(struct Bairro)); 

    if(!novobairro)
    {
        printf("ERROR: NAO HA MEMORIA DISPONIVEl!\n");
        exit(1);
    }
    else
    {
        novobairro->id_bairro = (int*)malloc(sizeof(int));
        novobairro->id_bairro = id;
        novobairro->nome_bairro = (char*) malloc( strlen(nome)+1*sizeof(char) );
        strcpy (novobairro->nome_bairro, nome);
        novobairro->head_rua = NULL;
        novobairro->proxb = NULL;
        printf("Bairro %s cadastrado com sucesso\n", novobairro->nome_bairro);
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
        return insereinicio_bairro(id, nome);
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

// FIM DE FUNCOES PARA BAIRRO ----------------------------------------------------------------------------//











// FUNCOES PARA RUA ----------------------------------------------------------------------------------------//

street aloca_rua(int id, char *nome)
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
        novarua->head_casa = NULL;
        printf("Rua %s inserida com sucesso!\n", novarua->nome_rua );
        return(novarua);
        
    }
    
}


//Procura o bairro para inserir rua
nhood procura_bairro(int idBairro)
{
    nhood *aux = head_bairro->proxb;
    while(idBairro != aux->id_bairro)
    {
        aux = aux->proxb;
    }
    if(aux->proxb == NULL)
    {
        printf("Bairro não encontrado!\n");
        break;
    }
    else return aux;

}


// Inserir Rua no inicio da lista de ruas
street *insereinicio_rua(int idBairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(idBairro);
    street *nova = aloca_rua(id, nome);
    street *old_primeira = bairro->head_rua->proxr; //armazenando o endereço da primeira rua

    bairro->head_rua->proxr = nova; //colocando o bairro desejado no primeiro lugar da lista
    nova->proxr = old_primeira;
    return nova;
}

street *insere_rua(int idBairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(idBairro);
    if(bairro->id < bairro->head_rua->proxr->id_bairro)
    {
        return insereinicio_rua(idBairro, id, nome);
    } 
    else 
    {   
        street *rua_atual = bairro->head_rua->proxr;
        street *rua_anterior = bairro->head_rua;
        street *nova = aloca_rua(id, nome);
        
        while(id > rua_atual->id_rua)
        {
            rua_anterior = rua_atual;
            rua_atual = rua_atual->proxr;
        }
        
        if(id == rua_atual->id_rua)
        {
            printf("Esse rua ja foi cadastrada!\n");
            break;
        } 
        else 
        {
            rua_anterior->proxr = nova;
            nova->proxr = rua_atual;
            return nova;
        }   

    }   
}

// FIM DE FUNCOES PARA RUA ---------------------------------------------------------------------------------------//











// FUNCOES PARA CASA ----------------------------------------------------------------------------------------------//

street aloca_casa(int idconsumidor, int casa, float consumo, char *nome)
{
    house *novacasa = (house*) malloc(sizeof(struct Casa));
    if(!novacasa)
    {
        printf("ERROR: NAO HA MEMORIA DISPONIVEL");
        exit(1);
    }
    else
    {
        novacasa->id_consumidor = idconsumidor;
        novacasa->nome_consumidor = (char*)malloc(strlen(nome)+1*sizeof(char));
        strcpy(novacasa->nome_consumidor, nome);
        novacasa->consumo = consumo;
        printf("Casa %d inserida com sucesso!\n", novacasa->casa );
        return novacasa;       
    }
    
}

street procura_rua(int idRua, int idBairro)
{
    
    nhood *bairro = procura_bairro(int idBairro);
    street *aux = bairro->head_rua->proxr;
    while(idRua != aux->id_rua)
    {
        aux = aux->proxr;
    }
    if(aux->proxr == NULL)
    {
        printf("Rua não encontrada!\n");
        break;
    }
    else return aux;

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
