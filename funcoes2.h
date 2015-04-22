#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



// FUNCOES PARA BAIRRO ---------------------------------------------------------------------------//


//Função que cria a head da lista de bairros
nhood * inicia_bairro(nhood *bairro)
{
    bairro = (nhood*) malloc(sizeof(struct Bairro)); 
    bairro->proxb = NULL;

    return(bairro);
}

// FUNÇÃO QUE ALOCA UM ESPAÇO DE MEMORIA PARA UM BAIRRO, SE HOUVER MEMORIA
nhood * aloca_bairro(int id, char *nome)
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
        //printf("Bairro %s cadastrado com sucesso\n", novobairro->nome_bairro);
        return novobairro;
    }
    
}


//FUNCAO QUE INSERE UM BAIRRO NO INICIO DA LISTA DE BAIRROS
void insereinicio_bairro(nhood * head_bairro, int id, char *nome)
{
    nhood *novo = (nhood*) malloc(sizeof(struct Bairro));
    nhood *old_primeiro = (nhood*) malloc(sizeof(struct Bairro));

    novo = aloca_bairro(id, nome);
    old_primeiro = head_bairro->proxb; //armazenando o endereço do primeiro bairro

    head_bairro->proxb = novo; //colocando o bairro desejado no primeiro lugar da lista
    novo->proxb = old_primeiro;
}

//Procura o bairro para inserir rua
nhood * procura_bairro(nhood * head_bairro, int idBairro)
{
    nhood *aux = head_bairro->proxb;
    while(idBairro != aux->id_bairro)
    {
        if (aux->proxb == NULL) return NULL;
        aux = aux->proxb;
    }
    return aux;
}

//FUNCAO QUE INSERE UM BAIRRO EM QUALQUER LUGAR DA LISTA DE BAIRROS
void insere_bairro(nhood * head_bairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(head_bairro, id);
    
    if(bairro == NULL)
    {
        if (id > head_bairro->proxb->id_bairro)
        {
            nhood *bairro_atual;
            nhood *bairro_anterior;

            bairro_atual = (nhood*)malloc(sizeof(nhood));
            bairro_anterior = (nhood*)malloc(sizeof(nhood));

            while(id > bairro_atual->id_bairro)
            {
                bairro_anterior = bairro_atual;
                bairro_atual = bairro_atual->proxb;
                if (bairro_atual == NULL) break;
            }

            nhood *novo;
            novo = aloca_bairro(id, nome);

            bairro_anterior->proxb = novo;
            novo->proxb = bairro_atual;

            if (bairro_atual != NULL) bairro_atual->proxb = NULL;
        }

        else insereinicio_bairro(head_bairro, id, nome);

    }

}


// FIM DE FUNCOES PARA BAIRRO ----------------------------------------------------------------------------//







// FUNCOES PARA RUA ----------------------------------------------------------------------------------------//
//função que aloca um espaço para uma struct, se houver espaço na memória
street * aloca_rua(int idBairro, int id, char *nome)
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
        novarua->proxr = NULL;
        printf("Rua incluida com sucesso! Bairro id: %i Rua id: %i Rua nome '%s'\n", idBairro, id, novarua->nome_rua );
        return(novarua);
    }
}





// Inserir Rua no inicio da lista de ruas
street *insereinicio_rua(nhood *head_bairro, int idBairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(head_bairro, idBairro);
    if (bairro != NULL)
    {
        street *nova = aloca_rua(idBairro, id, nome);
        street *old_primeira = bairro->head_rua->proxr; //armazenando o endereço da primeira rua

        bairro->head_rua->proxr = nova; //colocando o bairro desejado no primeiro lugar da lista
        nova->proxr = old_primeira;
        return nova;
    }
    else return NULL;

}


street *insere_rua(nhood * head_bairro, int idBairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(head_bairro, idBairro);
    
    if(bairro != NULL)
    {
        if(bairro->head_rua == NULL)
        {
           street *nova = aloca_rua(idBairro, id, nome);
           bairro->head_rua = nova;
           return nova;
        }
        else
        {  
          if(id < bairro->head_rua->id_rua)
          {
             street *nova = insereinicio_rua(head_bairro, idBairro, id, nome);
             return nova;
          } 
          else 
          {   
              street *rua_atual = bairro->head_rua;
              
        
             while(id > rua_atual->id_rua)
             {
                if(rua_atual->proxr == NULL) break;
                else
                {
                  if(rua_atual->proxr->id_rua < id)
                  {
                      street *rua_anterior;
                      rua_anterior = rua_atual;
                      rua_atual = rua_atual->proxr; 
                     continue;
                  }
                  else break;      
                }
             }
             printf("atual: %d  id:%d\n", rua_atual->id_rua, id );
             if(id == rua_atual->id_rua)
             {
                 printf("Essa rua ja foi cadastrada!\n");
                 return NULL;
             } 
             else 
             {
                 street *nova = aloca_rua(idBairro, id, nome);
                 if(rua_atual->proxr == NULL) //se for para inserir o novo bairro no fim da lista
                 {
                    rua_atual->proxr = nova;  
                 }
                 else //se for para inserir no meio
                 {
                    street *aux;
                    aux = rua_atual->proxr;
                    rua_atual->proxr = nova;
                    nova->proxr = aux;
                 }
                 return nova;
             }   
           }
        }   
    } 
    else return NULL;
    
}


void retira_rua(nhood *head_bairro, int idBairro, int id)
{
    nhood *bairro = procura_bairro(head_bairro, idBairro);
    printf("Oi\n");
    if(bairro != NULL)
    { 
        if (bairro->head_rua == NULL) printf("Não há ruas cadastradas neste bairro!\n");
        else 
        {
          street *proxima;
          street *anterior;

          anterior = bairro->head_rua;
          proxima = bairro->head_rua->proxr;

          while (proxima->id_rua != id)
            {
              anterior = proxima;
              proxima = proxima->proxr;
              printf("Oi2\n");
            }

          if (proxima == NULL) printf("Rua não encontrada!\n");
          else {
            anterior = proxima->proxr;
            free(proxima);
            printf("Rua retirada com sucesso!\n");
          }
        }
          
      }
} 
