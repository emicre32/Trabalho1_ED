#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes2.h"


int main() {

    // Variáveis
    FILE * mapa;
    char * comando, *descr;
    int id1, id2, id3, id4;
    float id5;
    int * pid1 = NULL;
    int * pid2 = NULL;
    int * pid3 = NULL;
    int * pid4 = NULL;
    float * pid5 = NULL;

    nhood *head_bairro;
    nhood *aux;
    int answer = 1;

    // Alocações
    aux = (nhood*)malloc(sizeof(nhood));
    comando = (char*)malloc(9*sizeof(char));
    descr = (char*)malloc(60*sizeof(char));
    pid1 = (int*)malloc(sizeof(int));
    pid2 = (int*)malloc(sizeof(int));
    pid3 = (int*)malloc(sizeof(int));
    pid4 = (int*)malloc(sizeof(int));
    pid5 = (float*)malloc(sizeof(float));


    // Inicialização
    head_bairro = inicia_bairro(aux);

    //inserção do primeiro bairro (deletado no fim)
    id1 = 0;
    nhood* nulo = aloca_bairro(id1, "nulo");
    head_bairro->proxb = nulo;

    //Inserção dos bairros
    while (answer == 1){
        printf("Digite o id e o respectivo nome dos bairros:    <id, nome>\n");
        scanf("%i, %[^\n]", &id1, descr);
        insere_bairro(head_bairro, id1, descr);
        printf("Deseja adicionar mais um bairro? <1> Sim   <qualquer número> Não\n");
        scanf("%i", &answer);
    }


    // Inicialização do arquivo
    mapa = abrirMapa();


    while(!feof(mapa))
    {
        fscanf(mapa, "%s", comando);  // rua, casa, bairro ou cidade
       //printf("COMANDO DA VEZ: %s\n", comando);
        // -----  RUA
        if (strcmp(comando, "rua") == 0)
        {
            fscanf(mapa, "%s", comando); // incluir, eliminar ou medir
            
            if (strcmp(comando, "incluir") == 0)
            {
                fscanf(mapa, "%i", pid1); // id bairro
                id1 = *pid1;
                fscanf(mapa, "%i", pid2); // id rua  
                //fscanf(mapa, " "%[^\n]"", descr); // nome 
                fscanf(mapa, " \"%[^\"\n]", descr); // nome
                fgetc(mapa);
                id2 = *pid2;
                insere_rua(head_bairro, id1, id2, descr);                     
            }

            else if (strcmp(comando, "eliminar") == 0)
            {
                fscanf(mapa, "%i", pid1); // id bairro  
                fscanf(mapa, "%i", pid2); // id rua  
                
                id1 = *pid1;
                id2 = *pid2;

                retira_rua(head_bairro, id1, id2);
            }
            else if (strcmp(comando, "medir") == 0)
                 {
                    fscanf(mapa, "%i", pid1); // id bairro  
                    fscanf(mapa, "%i", pid1); // id rua 
                    id1 = *pid1;
                    id2 = *pid2;
                    medir_rua(head_bairro, id1, id2);
                 }
                 else printf("Comando nao identificadoaqui.\n");
        }
        else if (strcmp(comando, "casa") == 0)
             {
                fscanf(mapa, "%s", comando); //incluir, consumir, medir  
                if (strcmp(comando, "incluir") == 0)
                {
                    fscanf(mapa, "%i", pid1); //id bairro  
                    fscanf(mapa, "%i", pid2); // id rua   
                    fscanf(mapa, "%i", pid3); //id consumidor  
                    fscanf(mapa, "%i", pid4); // num casa
                    fscanf(mapa, "%f", pid5); // consumo
                    fscanf(mapa, "%[^\n]", descr);  // nome consumidor 
                    id1 = *pid1;
                    id2 = *pid2;
                    id3 = *pid3;
                    id4 = *pid4;
                    id5 = *pid5;
                    insere_casa(head_bairro, id1, id2 , id3, id4, id5, descr);
                }
                else if (strcmp(comando, "eliminar") == 0)
                     {
                         fscanf(mapa, "%i", pid1); //id bairro  
                         fscanf(mapa, "%i", pid2); // id rua   
                         fscanf(mapa, "%i", pid3); //id casa 
                         id1 = *pid1;
                         id2 = *pid2;
                         id3 = *pid3;                     
                         retira_casa(head_bairro, id1, id2, id3);
                     }
                     else if (strcmp(comando, "consumir") == 0)
                          {
                            fscanf(mapa, "%i", pid1); //id bairro  
                            fscanf(mapa, "%i", pid2); // id rua   
                            fscanf(mapa, "%i", pid3); //id casa 
                            fscanf(mapa, "%f", pid5); //consumo
                            id1 = *pid1;
                            id2 = *pid2;
                            id3 = *pid3;
                            id5 = *pid5; //float
                            inserir_consumo(head_bairro, id1, id2, id3, id5);
                          }
                         else if (strcmp(comando, "medir") == 0)
                              {
                                fscanf(mapa, "%i", pid1); //id bairro  
                                fscanf(mapa, "%i", pid2); // id rua   
                                fscanf(mapa, "%i", pid3); //id casa 
                                id1 = *pid1;
                                id2 = *pid2;
                                id3 = *pid3; 
                                medir_casa(head_bairro, id1, id2, id3);
                              }
                              else printf("Comando nao identificadohere.\n");
             } 
             else if (strcmp(comando, "bairro") == 0)
                  {
                    fscanf(mapa, "%s", comando); // incluir, medir
                    if (strcmp(comando, "incluir"))
                    {
                      fscanf(mapa, "%i", pid1); // id  
                      fscanf(mapa, "%[^\n]", descr); // nome
                      // função <incluir_bairro> //
                    }
                    else if (strcmp(comando, "medir") == 0)
                         {
                            fscanf(mapa, "%i", pid1); // id bairro 
                            // função <medir_bairro> //
                         }
                         else printf("Comando nao identificadohere2.\n");
                  } 
                  else printf("Comando nao identificadohere3.\n"); 
    
    }//while

    return 0;
}
            
 /*   

            }
            // -----  CASA
            else if (strcmp(comando, "casa") == 0)
            {
                fscanf(mapa, "%s", comando); //incluir, consumir, medir  
                if (strcmp(comando, "incluir") == 0)
                {
                    fscanf(mapa, "%i", pid1); //id bairro  
                    fscanf(mapa, "%i", pid1); // id rua   
                    fscanf(mapa, "%i", pid1); //id consumidor  
                    fscanf(mapa, "%i", pid1); // num casa
                    fscanf(mapa, "%i", pid1); // consumo
                    fscanf(mapa, "%[^\n]", descr);  // nome consumidor 
                    // função <incluir_casa> //
                }
                else if (strcmp(comando, "eliminar") == 0)
                {
                    fscanf(mapa, "%i", pid1); //id bairro  
                    fscanf(mapa, "%i", pid1); // id rua   
                    fscanf(mapa, "%i", pid1); //id casa  
                    //função <eliminar_rua> //
                }
                    else if (strcmp(comando, "consumir") == 0)
                    {
                        fscanf(mapa, "%i", pid1); //id bairro  
                        fscanf(mapa, "%i", pid1); // id rua   
                        fscanf(mapa, "%i", pid1); //id casa  
                        fscanf(mapa, "%i", pid1); //consumo
                        //função <consumir_rua> //
                    }
                        else if (strcmp(comando, "medir") == 0)
                        {
                            fscanf(mapa, "%i", pid1); //id bairro  
                            fscanf(mapa, "%i", pid1); // id rua   
                            fscanf(mapa, "%i", pid1); //id casa  
                            // função <medir_rua> //
                        }
                else printf("Comando nao identificado.\n");
            }
                // -----  BAIRRO
                else if (strcmp(comando, "bairro") == 0)
                {
                    fscanf(mapa, "%s", comando); // incluir, medir
                    if (strcmp(comando, "incluir"))
                    {
                        fscanf(mapa, "%i", pid1); // id  
                        fscanf(mapa, "%[^\n]", descr); // nome
                        // função <incluir_bairro> //
                    }
                        else if (strcmp(comando, "medir") == 0)
                        {
                            fscanf(mapa, "%i", pid1); // id bairro 
                            // função <medir_bairro> //
                        }
                            else printf("Comando nao identificado.\n");
                }
                    // -----  CIDADE
                    else if (strcmp(comando, "cidade") == 0)
                    {
                        fscanf(mapa, "%s", comando); // medir
                        if (strcmp(comando, "medir") == 0)
                        {
                            printf("%s\n", comando);
                            // função <medir_cidade> //
                        }
                            else printf("Comando nao identificado.\n");
                    }
                        else printf("Comando nao identificado.\n");
            }

    return 0;
}   */
