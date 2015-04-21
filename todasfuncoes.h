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


nhood * inicia_bairro()
{
    nhood *bairro = (nhood*) malloc(sizeof(struct Bairro)); 
    bairro->proxb = NULL;

    return(bairro);
}

// FUNÇÃO QUE ALOCA UM ESPAÇO DE MEMORIA PARA UM BAIRRO, SE HOUVER MEMORIA
nhood * aloca_bairro(int *id, char *nome)
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
void insereinicio_bairro(nhood * head_bairro, int * id, char *nome)
{
    nhood *novo = (nhood*) malloc(sizeof(struct Bairro));
    nhood *old_primeiro = (nhood*) malloc(sizeof(struct Bairro));

    novo = aloca_bairro(id, nome);
    old_primeiro = head_bairro->proxb; //armazenando o endereço do primeiro bairro

    head_bairro->proxb = novo; //colocando o bairro desejado no primeiro lugar da lista
    novo->proxb = old_primeiro;
}


//FUNCAO QUE INSERE UM BAIRRO EM QUALQUER LUGAR DA LISTA DE BAIRROS
nhood *insere_bairro(nhood * head_bairro, int *id, char *nome)
{

    if(id < head_bairro->proxb->id_bairro) 
    {
        
        insereinicio_bairro(head_bairro, id, nome);

    }
    else 
    {   //printf("aqui\n");
        /* bairro_atual e bairro_anterior são ponteiros que percorrem a 
        lista até achar o lugar correto para inserir o bairro desejado */
        printf("chegou1\n");
        nhood *bairro_atual = head_bairro->proxb;
        nhood *bairro_anterior = head_bairro;
        nhood *novo = aloca_bairro(id, nome); 
        /*os ponteiros avançam na lista até achar um bairro que tenha
         um numero de id maior que o desejado*/
        while(id > bairro_atual->id_bairro)
        {
            bairro_anterior = bairro_atual;
            bairro_atual = bairro_atual->proxb;
        }
        //se o bairro já esta cadastrado, a função é abortada//
        if(id != bairro_atual->id_bairro)
        {
            printf("Esse bairro ja foi cadastrado!\n");
        } 
        else 
        {
            nhood *novo = aloca_bairro(id, nome);
            bairro_anterior->proxb = novo;
            novo->proxb = bairro_atual;
            return novo;
        }   

    }   
    return 0;
}
// FIM DE FUNCOES PARA BAIRRO ----------------------------------------------------------------------------//







/* Não testadas a partir daqui



// FUNCOES PARA RUA ----------------------------------------------------------------------------------------//


//função que aloca um espaço para uma struct, se houver espaço na memória
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
        novarua->proxr = NULL;
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
    // se for o último elemento da lista de bairros e id_bairro não for igual ao procurado, o bairro não está na lista
    if(aux->proxb == NULL && aux->id_bairro != idBairro)
    {
        printf("Bairro não encontrado!\n");
        bairro = NULL;
        break;
    }
    else return aux;

}


// Inserir Rua no inicio da lista de ruas
street *insereinicio_rua(int idBairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(idBairro);
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

//função que insere uma rua em qualquer lugar da lista de ruas de um bairro
street *insere_rua(int idBairro, int id, char *nome)
{
    nhood *bairro = procura_bairro(idBairro);
    if(bairro != NULL)
    {
        if(id < bairro->head_rua->proxr->id_rua)
        {
           return insereinicio_rua(idBairro, id, nome);
        } 
        else 
        {   
           street *rua_atual = bairro->head_rua->proxr;
           street *rua_anterior = bairro->head_rua;
        
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
               break;
           } 
           else 
           {
               street *nova = aloca_rua(id, nome);
               if(rua_atual->proxr == NULL) //se for para inserir a nova rua no fim da lista
               {
                 rua_atual->proxb = nova;  

               }               
               else
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
    else return NULL;
    
}

//tamanho de uma lista de ruas num bairro
int tamanho_rua(int idbairro)
{
    int tam_rua=0;
    nhood *bairro = procura_bairro(idbairro);
    if(bairro != NULL)
    {   street *aux = bairro->head_rua->proxr;
       while(aux->proxr != NULL)
       {
           tam_rua++;
           aux = aux.proxr;
       }
       return tam_rua;
    }
    else return NULL;
}


street *retirainicio_rua(int idBairro, int id)
{
    nhood *bairro = procura_bairro(idBairro);
    
    if(bairro != NULL)
    {
        if(bairro->head_rua = NULL);
        {
           printf("Nao ha ruas cadastradas nesse bairro!\n");
           return NULL;
        }
        else
        {
            street *aux = bairro->head_rua->proxr;
            bairro->head_rua->proxr = aux->proxr;
            printf("Rua %d retirada com sucesso!\n", id );
            return aux;
        }
    }
    else return NULL;    
}

int *retira_rua(int idBairro, int id)
{
    nhood *bairro = procura_bairro(idBairro);
    if(bairro != NULL)
    { 
        int tam = tamanho_rua(idBairro);
        if(tam == 0)
        {
           printf("Nao ha ruas cadastradas nesse bairro!\n");
           return NULL
        }
        else
        {
          if(id == bairro->head_rua->proxr)
          {
            retirainicio_rua(idBairro, id);
          }      
          else
          {
            street *atual = bairro->head_rua->proxr;
            street *anterior = bairro->head_rua;
 
            for(int = 0; i < tam; i++)
            { 
               if(atual->id_rua == id) break;
               else
               {
                 anterior = atual;
                 atual = atual->proxr;
                 continue;
               }
            }
            if(atual->id_rua == id)
            {   
               printf("Rua %d retirada com sucesso!\n", id );
               anterior->proxr = atual->proxr;
               free(atual);
               return 0;
            }
            else
            {
               printf("Rua nao encontrada!\n");
               return 0;
            }
          } 
        }
        else return NULL;

    
}




// FIM DE FUNCOES PARA RUA ---------------------------------------------------------------------------------------//











// FUNCOES PARA CASA ----------------------------------------------------------------------------------------------//

street aloca_casa(int idconsumidor, int casa, float consumo, char *consumidor)
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
        novacasa->proxc = NULL;
        printf("Casa %d inserida com sucesso!\n", novacasa->casa );
        return novacasa;       
    }
    
}

street procura_rua(int idRua, int idBairro)
{
    
    nhood *bairro = procura_bairro(idBairro);
    if( bairro != NULL)
    {
        street *aux = bairro->head_rua->proxr;
        while(idRua != aux->id_rua)
        {
           aux = aux->proxr;
        }
        if(aux->proxr == NULL && aux->id_rua != idRua)
        {
           printf("Rua não encontrada!\n");
           return NULL;
           break;
        }
        else return aux;
    }
    else return NULL;    

}

house *insereinicio_casa(int idbairro, int idrua, int idconsumidor, int casa, float consumo, char *consumidor)
{
    street *rua = procura_rua(idrua, idbairro);
    if(rua != NULL)
    {
        house *nova = aloca_casa(idconsumidor, casa, consumo, consumidor);
        house *old_primeira = rua->head_casa->proxc; //armazenando o endereço da primeira casa

        rua->head_casa->proxc = nova; //colocando o bairro desejado no primeiro lugar da lista
        nova->proxc = old_primeira;
        return nova;
    }
    else return NULL;    
}

house *insere_casa(int idbairro, int idrua, int idconsumidor, int casa, float consumo, char *consumidor)
{
    street *rua = procura_rua(idrua, idbairro);
    if(rua != NULL)
    {
        if(casa < rua->head_casa->proxc->id_casa)
        {
           return insereinicio_casa(idbairro, idrua, idconsumidor, casa, consumo, consumidor)
        } 
        else 
        {   
           house *casa_atual = rua->head_casa->proxc;
           house *casa_anterior = rua->head_casa;
           street *nova = aloca_casa(idconsumidor, casa, consumo, consumidor);
        
           while(casa > casa_atual->id_casa)
           {
               casa_anterior = casa_atual;
               casa_atual = casa_atual->proxc;
           }
        
           if(id == casa_atual->id_casa)
           {
               printf("Essa casa ja foi cadastrada!\n");
               break;
           } 
           else 
           {
               casa_anterior->proxc = nova;
               nova->proxc = casa_atual;
               return nova;
           } 
        }

    }
    else return NULL;        

        
}

int *retirainicio_casa(int idbairro, int idrua, int idcasa)
{
    street *rua = procura_rua(idrua, idbairro);
    if(rua->head_casa = NULL);
    {
        printf("Nao ha casas cadastradas nessa rua!\n");
        return 0;
    }
    else
    {
         house *aux = rua->head_casa->proxc;
         rua->head_casa->proxc = aux->proxc;
         printf("Casa %d retirada com sucesso!\n", idcasa );
         return 0;

    }
}


int tamanho_casa(int idbairro, int idrua)
{
    int tam_casa=0;
    street *rua = procura_rua(idrua, idbairro);
    if(rua != NULL)
    {
        house *aux = rua->head_casa->proxc;
        while(aux->proxr != NULL)
        {
           tam_casa++;
           aux = aux.proxc;
        }
        return tam_casa;
    } 
    else return NULL;   
}



int *retira_casa(int idbairro, int idrua, int idcasa)
{
    street *rua = procura_rua(idrua, idbairro);
    if(rua != NULL)
    {    
       int tam = tamanho_casa(idbairro, idrua);
       if(tam == 0)
       {
           printf("Nao ha casas cadastradas nessa rua!\n");
           return 0;
       }
       else
       {
          if(idcasa == rua->head_casa->proxc)
          {
              retirainicio_casa(idbairro, idrua, idcasa);
          }      
          else
          {
              house *atual = rua->head_casa->proxc;
              house *anterior = rua->head_casa;
 
              for(int = 0; i < tam; i++)
              { 
                 if(atual->id_casa == idcasa) break;
                 else
                 {
                   anterior = atual;
                   atual = atual->proxc;
                   continue;
                 }
              }
              if(atual->id_casa == idcasa)
              {   
                 printf("Casa %d retirada com sucesso!\n", idcasa );
                 anterior->proxc = atual->proxc;
                 free(atual);
                 return 0;
              
              }
              else
              {
                 printf("Casa nao encontrada!\n");
                 return 0;
              }
           } 
       }
    }
    else return NULL;   
    
}

house procura_casa(int idbairro, int idrua, int idcasa)
{
    street *rua = procura_rua(idrua, idbairro);
    if(rua != NULL)
    {    
        house *aux = rua->head_casa->proxc;
        while(idcasa != aux->id_casa)
        {
           aux = aux->proxr;
        }
        if(aux->proxc == NULL && aux->id_casa != idcasa)
        {
           printf("Casa não encontrada!\n");
           break;
           return NULL;
        }
        else return aux;
    }
    else return NULL;    
}



// FIM DE FUNCOES PARA CASA--------------------------------------------------------------------------------------//








// FUNCOES CONSUMO ----------------------------------------------------------------------------------------------//

float medir_casa(int idbairro, int idrua, int idcasa)
{
    float consumo_medir;
    house *casa = procura_casa(idbairro, idrua, idcasa);
    if( casa != NULL)
    {
        consumo_medir = casa->consumo;
        return consumo_medir;
    }
    else return NULL;    
}

int inserir_consumo(int idbairro, int idrua, int idcasa, float consumo)
{
    house *casa = procura_casa(idbairro, idrua, idcasa);
    if (casa != NULL) 
    {    
        casa->consumo =+ consumo;
        return 0;
    }  
    else return NULL;  
}

float medir_rua(int idbairro, int idrua)
{
    float consumo_rua=0;
    street *rua = procura_rua(idrua, idbairro);
    if(rua != NULL)
    {  
      house *aux = rua->head_casa->proxc;
      while(aux->proxc != NULL)
      {
          consumo_rua =+ aux->consumo;
          aux = aux->proxc;
      }
      return consumo_rua;
    }
    else return NULL; 

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

Não testadas até aqui */
