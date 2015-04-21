// FUNCOES PARA RUA ----------------------------------------------------------------------------------------//
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
          return NULL;
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
        {  
          if(id < bairro->head_rua->id_rua)
          {
             street *nova = insereinicio_rua(head_bairro, idBairro, id, nome);
             return nova;
          } 
          else 
          {   
              street *rua_atual = bairro->head_rua;
              street *rua_anterior;
        
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

