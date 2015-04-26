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
    struct Casa *proxc;
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
        if (aux->proxb == NULL) 
        {  
          return NULL;
          break;
        }  
        else
        {
          aux = aux->proxb;
        }
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

            bairro_atual = head_bairro->proxb;
            bairro_anterior = head_bairro;

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
        
             if(id == rua_atual->id_rua)
             {
                 printf("ERRO: Rua nao incluida. Bairro id: %i Rua id: %i Rua nome '%s'\n", idBairro, id, nome);
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
    if(bairro != NULL)
    { 
        if (bairro->head_rua == NULL) printf("Não há ruas cadastradas neste bairro!\n");
        else 
        {
          street *proxima;
          street *anterior;

          anterior = NULL;
          proxima = bairro->head_rua;


          while (proxima->id_rua != id)
            {
              anterior = proxima;
              proxima = proxima->proxr;

              if(proxima->id_rua == id)
              {
                //anterior = proxima->proxr;
                //free(proxima);
                //printf("Rua removida com sucesso. Bairro id: %i Rua id: %i\n", idBairro, id);
                break;
              }
              else if (proxima->proxr == NULL)
                    {
                      printf("Bairro vazio ou rua com ID=%i não encontrado.\nERRO: Rua nao removida. Bairro id: %i Rua id: %i\n", id, idBairro, id);
                      break;
                    }
            }
         
          if(proxima->id_rua == id)
          {
            
            anterior = proxima->proxr;
            proxima->id_rua = 0;
            free(proxima);
            printf("Rua removida com sucesso. Bairro id: %i Rua id: %i\n", idBairro, id);

          }

        }
    }
    else printf("Bairro vazio ou rua com ID=%i não encontrado.\nERRO: Rua nao removida. Bairro id: %i Rua id: %i\n", id, idBairro, id);
} 


//FIM DE FUNCOES PARA RUA--------------------------------------------------------------------------------------//



//FUNCOES PARA CASA--------------------------------------------------------------------------------------------//
house *aloca_casa(int idbairro, int idrua, int idconsumidor, int casa, float consumo, char *consumidor)
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
        novacasa->nome_consumidor = (char*)malloc(strlen(consumidor)+1*sizeof(char));
        strcpy(novacasa->nome_consumidor, consumidor);
        novacasa->consumo = consumo;
        novacasa->proxc = NULL;
        novacasa->id_casa = casa;
        printf("Casa incluida com sucesso. Bairro id: %d Rua id: %d Casa id: %d Casa nr: %d Consumidor nome '%s'\n", idbairro, idrua, idconsumidor, casa, consumidor );
        return novacasa;       
    }
    
}

street *procura_rua(nhood *head_bairro, int idRua, int idBairro)
{
    
    nhood *bairro = procura_bairro(head_bairro, idBairro);
    if( bairro != NULL)
    {
        street *aux = bairro->head_rua;
        while(idRua != aux->id_rua)
        {
           aux = aux->proxr;
        }
        if(aux->proxr == NULL && aux->id_rua != idRua)
        {
           printf("Rua não encontrada!\n");
           return NULL;
        }
        else return aux;
    }
    else return NULL;    

}

house *insereinicio_casa(nhood *head_bairro, int idbairro, int idrua, int idconsumidor, int casa, float consumo, char *consumidor)
{
    street *rua = procura_rua(head_bairro, idrua, idbairro);
    if(rua != NULL)
    {
        house *nova = aloca_casa(idbairro, idrua, idconsumidor, casa, consumo, consumidor);
        house *old_primeira;
        old_primeira = rua->head_casa->proxc; //armazenando o endereço da primeira casa

        rua->head_casa->proxc = nova; //colocando o bairro desejado no primeiro lugar da lista
        nova->proxc = old_primeira;
        return nova;
    }
    else return NULL;    
}

house *insere_casa(nhood *head_bairro, int idbairro, int idrua, int idconsumidor, int casa, float consumo, char *consumidor)
{

    street *rua = procura_rua(head_bairro, idrua, idbairro);
    if(rua != NULL)
    {
        if(rua->head_casa == NULL)
        {
           house *nova = aloca_casa(idbairro, idrua, idconsumidor, casa, consumo, consumidor);
           rua->head_casa = nova;
           return nova;
        } 
        else
        {
           if(casa < rua->head_casa->id_casa)
           {
              return insereinicio_casa(head_bairro, idbairro, idrua, idconsumidor, casa, consumo, consumidor);
           } 
           else 
           {   
              house *casa_atual = rua->head_casa;
              house *nova;
        
              while(casa > casa_atual->id_casa)
              {
                if(casa_atual->proxc == NULL) break;
                else
                {
                  if(casa_atual->proxc->id_casa < casa)
                  {
                      house *casa_anterior;
                      casa_anterior = casa_atual;
                      casa_atual = casa_atual->proxc; 
                     continue;
                  }
                  else break;      
                }
              }
        
              if(casa == casa_atual->id_casa)
              {
                  printf("Essa casa ja foi cadastrada!\n");
                  return NULL;
              } 
              else 
              {
                 house *nova = aloca_casa(idbairro, idrua, idconsumidor, casa, consumo, consumidor);
                 if(casa_atual->proxc == NULL) //se for para inserir o novo bairro no fim da lista
                 {
                    casa_atual->proxc = nova;  
                 }
                 else //se for para inserir no meio
                 {
                    house *aux;
                    aux = casa_atual->proxc;
                    casa_atual->proxc = nova;
                    nova->proxc = aux;
                 }
                 return nova;
             }  
          }
        }

    }
    else return NULL;        

        
}

int *retirainicio_casa(nhood *head_bairro, int idbairro, int idrua, int idcasa)
{
    street *rua = procura_rua(head_bairro, idrua, idbairro);
    if(rua->head_casa == NULL)
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


void retira_casa(nhood *head_bairro, int idBairro, int idrua, int idconsumidor)
{    
    street *rua = procura_rua(head_bairro, idrua, idBairro);
    if(rua != NULL)
    { 
        if (rua->head_casa == NULL) printf("Nao ha casas cadastradas nesta rua!\n");
        else 
        {
          house *proxima;
          house *anterior;

          anterior = NULL;
          proxima = rua->head_casa;


          while (proxima->id_consumidor != idconsumidor)
          {
              anterior = proxima;
              proxima = proxima->proxc;

              if(proxima->id_consumidor == idconsumidor)
              {
                break;
              }
              else if (proxima->proxc == NULL)
                    {
                      printf("Consumidor com ID=%i não encontrado.\nERRO: Casa nao removida. Bairro id: %i Rua id: %i\n", idconsumidor, idBairro, idrua);
                      break;
                    }
            }
         
          if(proxima->id_consumidor == idconsumidor)
          {
            
            anterior = proxima->proxc;
            proxima->id_consumidor = 0;
            free(proxima);
            printf("Casa removida com sucesso. Consumidor id: %i Bairro id: %i Rua id: %i\n", idconsumidor, idBairro, idrua);

          }

        }
    }
    else printf("Consumidor com ID=%i não encontrado.\nERRO: Casa nao removida. Bairro id: %i Rua id: %i\n", idconsumidor, idBairro, idrua);
} 

//FIM DE FUNCOES PARA CASA---------------------------------------------------------------------------------------------------------------------//


//FUNCOES PARA MEDIR CONSUMO------------------------------------------------------------------------------------------------------------------//
float medir_rua(nhood *head_bairro, int idbairro, int idrua)
{
    float consumo_rua=0;
    street *rua = procura_rua(head_bairro, idrua, idbairro);
    if(rua != NULL)
    {  
      house *aux = rua->head_casa->proxc;
      while(aux->proxc != NULL)
      {
          consumo_rua += aux->consumo;
          aux = aux->proxc;
      }
      return consumo_rua;
    }
    else return 0; 

} 

house *procura_casa(nhood *head_bairro, int idbairro, int idrua, int idcasa)
{
    street *rua = procura_rua(head_bairro, idrua, idbairro);
    if(rua != NULL)
    {    
        if(rua->head_casa == NULL) 
        {
           printf("Casa não encontrada!\n");
           return NULL;
        }
        else
        {  
          house *aux = rua->head_casa;
          while(idcasa != aux->id_consumidor)
          {
            aux = aux->proxc;
          }
          if(aux->proxc == NULL && aux->id_consumidor != idcasa)
          {
             printf("Casa não encontrada!\n");
             return NULL;
          }
          else return aux;
        } 
    }
    else return NULL;    
}


float medir_casa(nhood *head_bairro, int idbairro, int idrua, int idcasa)
{
    float consumo_medir;
    house *casa = procura_casa(head_bairro, idbairro, idrua, idcasa);
    if( casa != NULL)
    {
        consumo_medir = casa->consumo;
        return consumo_medir;
    }
    else return 1;    
}

int inserir_consumo(nhood *head_bairro, int idbairro, int idrua, int idcasa, float consumo)
{
    house *casa = procura_casa(head_bairro, idbairro, idrua, idcasa);
    if (casa != NULL) 
    {    
        casa->consumo += consumo;
        return 0;
    }  
    else return 1;
}

float medir_bairro(nhood *head_bairro, int idbairro)
{
    float consumo_medir=0;
    nhood *bairro = procura_bairro(head_bairro, idbairro);
    if(bairro!= NULL)
    {
       if(bairro->head_rua != NULL)
       {
          street *rua = bairro->head_rua;
          
          while(rua->proxr != NULL)
          {
             int idrua = rua->id_rua;
             consumo_medir += medir_rua(head_bairro, idbairro, idrua );
             rua = rua->proxr;
          }
          printf("O consumo total desse bairro e %f\n", consumo_medir );
          return consumo_medir;
       }
       else
       {
        printf("Nao ha ruas nesse bairro!\n");
        return 0;
       }
    }
    else return 0;
}



