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
        printf("Bairro %s cadastrado com sucesso\n", novobairro->nome_bairro);
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

//FUNCAO QUE INSERE UM BAIRRO EM QUALQUER LUGAR DA LISTA DE BAIRROS
nhood *insere_bairro(nhood * head_bairro, int id, char *nome)
{
    //printf("%i\n", *head_bairro->proxb->id_bairro); 
    if(id < head_bairro->proxb->id_bairro) 
    {
        printf("Entrou\n");
        insereinicio_bairro(head_bairro, id, nome);
    }
    else 
    {   /* bairro_atual e bairro_anterior são ponteiros que percorrem a 
        lista até achar o lugar correto para inserir o bairro desejado */
        nhood *bairro_atual = head_bairro->proxb;
        nhood *bairro_anterior = head_bairro;
        printf("Entrou 2\n");
        printf("%d\n", bairro_atual->id_bairro );
        /*os ponteiros avançam na lista até achar um bairro que tenha
         um numero de id maior que o desejado*/
        //printf("%i\n", bairro_atual->proxb->id_bairro);
        while(id > bairro_atual->id_bairro)
        {
            if(bairro_atual->proxb == NULL) break;
            else
            {
                if(bairro_atual->proxb->id_bairro < id)
                {
                    bairro_anterior = bairro_atual;
                    bairro_atual = bairro_atual->proxb; 
                   continue;
                }
                else break;      
            }
        
        }
         printf("Entrou 4\n");
        /*se o bairro já esta cadastrado, a função é abortada*/
        if(id == bairro_atual->id_bairro)
        {
            printf("Esse bairro ja foi cadastrado!\n");
        } 
        else 
        {
            printf("Entrou 5\n");
            nhood *novo = aloca_bairro(id, nome);
            if(bairro_atual->proxb == NULL) //se for para inserir o novo bairro no fim da lista
            {
              bairro_atual->proxb = novo;  

            }
            else //se for para inserir no meio
            {
              nhood *aux;
              aux = bairro_atual->proxb;
              bairro_atual->proxb = novo;
              novo->proxb = aux;
            }
            return novo;
        }   

           
    }
    return 0;

}
// FIM DE FUNCOES PARA BAIRRO ----------------------------------------------------------------------------//

//FUNCOES PARA RUA---------------------------------------------------------------------------------------//
//FUNCOES PARA RUA ---------------------------------------------------------------------------------------//
//função que aloca um espaço para uma struct, se houver espaço na memória
street * aloca_rua(int id, char *nome)
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
        printf("Rua %s inserida com sucesso!\n", novarua->nome_rua );
        return(novarua);
    }
}



//Procura o bairro para inserir rua
nhood * procura_bairro(nhood * head_bairro, int idBairro)
{
    nhood *aux = head_bairro->proxb;
    while(idBairro != aux->id_bairro)
    {
        if (aux->proxb == NULL)
        {
          printf("Bairro não encontrado!\n");
          return (NULL);
        }
        aux = aux->proxb;
    }
    return aux;
}

// Inserir Rua no inicio da lista de ruas
street *insereinicio_rua(nhood *head_bairro, int idBairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(head_bairro, idBairro);
    if (bairro != NULL)
    {
        street *nova = aloca_rua(id, nome);
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
           street *nova = aloca_rua(id, nome);
           bairro->head_rua = nova;
           return nova;
        }
        else
        { printf("chegou aqui\n"); 
          if(id < bairro->head_rua->id_rua)
          {
             street *nova = insereinicio_rua(head_bairro, idBairro, id, nome);
             return nova;
          } 
          else 
          {   printf("chegou aqui1\n");
              street *rua_atual = bairro->head_rua;
              street *rua_anterior;
              printf("chegou aqui2\n");
        
             while(id > rua_atual->id_rua)
             {
                if(rua_atual->proxr == NULL) break;
                else
                {
                  if(rua_atual->proxr->id_rua < id)
                  {
                      rua_anterior = rua_atual;
                      rua_atual = rua_atual->proxr; 
                     continue;
                  }
                  else break;      
                }
             }
        
             if(id == rua_atual->id_rua)
             {
                 printf("Essa rua ja foi cadastrada!\n");
                 return NULL;
             } 
             else 
             {
                 street *nova = aloca_rua(id, nome);
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


