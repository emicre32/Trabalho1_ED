#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes2.h"


int main() {

    // Variáveis
    FILE * mapa;
    char * comando, *descr;
    int id1, id2;
    //int i;
    int * pid1 = NULL;
    int * pid2 = NULL;
    nhood *head_bairro;
    nhood *aux;


    // Alocações
    aux = (nhood*)malloc(sizeof(nhood));
    comando = (char*)malloc(9*sizeof(char));
    descr = (char*)malloc(60*sizeof(char));
    pid1 = (int*)malloc(sizeof(int));
    pid2 = (int*)malloc(sizeof(int));


    // Inicialização
    mapa = abrirMapa();
    head_bairro = inicia_bairro(aux);

    //inserção do primeiro bairro (deletado no fim)
    id1 = 0;
    nhood* nulo = aloca_bairro(id1, "nulo");
    head_bairro->proxb = nulo;




    while(!feof(mapa))
    {
    //for(i=0; i<3; i++){
        fscanf(mapa, "%s", comando);  // rua, casa, bairro ou cidade
        // -----  RUA
        if (strcmp(comando, "rua") == 0)
            {
                fscanf(mapa, "%s", comando); // incluir, eliminar ou medir
                if (strcmp(comando, "incluir") == 0)
                {
                    fscanf(mapa, "%i", pid1); // id bairro
                    
                    id1 = *pid1;

                    insere_bairro(head_bairro, id1, "camburi");
                    insere_bairro(head_bairro, id1, "camburi");


                    fscanf(mapa, "%i", pid2); // id rua  
                    fscanf(mapa, "%[^\n]", descr); // nome 

                    id2 = *pid2;
                    insere_rua(head_bairro, id1, id2, descr);                     
                }

            }
            //fscanf(mapa, "%s", comando);  //     rua, casa, bairro ou cidade
            //fscanf(mapa, "%s", comando);
            //printf("%i\n", *comando);
            //printf("%c\n", *comando);
        }
    return 0;
}
            
 /*   
                else if (strcmp(comando, "eliminar") == 0)
                {
                    fscanf(mapa, "%i", pid1); // id bairro  
                    fscanf(mapa, "%i", pid1); // id rua  
                    // função <eliminar_rua> 
                }
                    else if (strcmp(comando, "medir") == 0)
                    {
                        fscanf(mapa, "%i", pid1); // id bairro  
                        fscanf(mapa, "%i", pid1); // id rua  
                        //função <medir_rua> 
                    }
                        else printf("Comando nao identificado.\n");
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
