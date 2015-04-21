#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes2.h"


int main() {

    // Variáveis
    FILE * mapa;
    char * comando, *descr;
    int * id1 = NULL, *id2 = NULL;
    nhood *head_bairro;
    nhood *aux;

    int i;

    // Alocações
    comando = (char*)malloc(9*sizeof(char));
    descr = (char*)malloc(60*sizeof(char));
    id1 = (int*)malloc(sizeof(int));
    id2 = (int*)malloc(sizeof(int));

    // Inicialização
    mapa = abrirMapa();
    head_bairro = inicia_bairro(aux);


            

    //while(comando != EOF)
    //{
    for(i=0; i<2; i++){
        fscanf(mapa, "%s", comando);  // rua, casa, bairro ou cidade
        printf("%s\n", comando);
        // -----  RUA
        if (strcmp(comando, "rua") == 0)
            {
                fscanf(mapa, "%s", comando); // incluir, eliminar ou medir

                if (strcmp(comando, "incluir") == 0)
                {
                    fscanf(mapa, "%i", id1); // id bairro
                    printf("%i\n", *id1);

                    insere_bairro(head_bairro, id1, "goiabeiras");
                    
                    fscanf(mapa, "%i", id2); // id rua  
                    fscanf(mapa, "%[^\n]", descr); // nome   

                    
                    /* função <incluir_rua> */
                }
            
    
                else if (strcmp(comando, "eliminar") == 0)
                {
                    fscanf(mapa, "%i", id1); // id bairro  
                    fscanf(mapa, "%i", id2); // id rua  

                    /* função <eliminar_rua> */
                }
                    else if (strcmp(comando, "medir") == 0)
                    {
                        fscanf(mapa, "%i", id1); // id bairro  
                        fscanf(mapa, "%i", id2); // id rua  

                        /* função <medir_rua> */
                    }
                        else printf("Comando nao identificado.\n");

            }

            // -----  CASA
            else if (strcmp(comando, "casa") == 0)
            {

                fscanf(mapa, "%s", comando); //incluir, consumir, medir  

                if (strcmp(comando, "incluir") == 0)
                {
                    fscanf(mapa, "%i", id1); //id bairro  
                    fscanf(mapa, "%i", id2); // id rua   
                    fscanf(mapa, "%i", id1); //id consumidor  
                    fscanf(mapa, "%i", id2); // num casa
                    fscanf(mapa, "%i", id2); // consumo
                    fscanf(mapa, "%[^\n]", descr);  // nome consumidor 

                    /* função <incluir_casa> */
                }

                else if (strcmp(comando, "eliminar") == 0)
                {
                    fscanf(mapa, "%i", id1); //id bairro  
                    fscanf(mapa, "%i", id2); // id rua   
                    fscanf(mapa, "%i", id1); //id casa  

                    /* função <eliminar_rua> */
                }

                    else if (strcmp(comando, "consumir") == 0)
                    {
                        fscanf(mapa, "%i", id1); //id bairro  
                        fscanf(mapa, "%i", id2); // id rua   
                        fscanf(mapa, "%i", id1); //id casa  
                        fscanf(mapa, "%i", id2); //consumo

                        /* função <consumir_rua> */
                    }
                        else if (strcmp(comando, "medir") == 0)
                        {
                            fscanf(mapa, "%i", id1); //id bairro  
                            fscanf(mapa, "%i", id2); // id rua   
                            fscanf(mapa, "%i", id1); //id casa  

                            /* função <medir_rua> */
                        }
                else printf("Comando nao identificado.\n");
            }

                // -----  BAIRRO
                else if (strcmp(comando, "bairro") == 0)
                {
                    fscanf(mapa, "%s", comando); // incluir, medir

                    if (strcmp(comando, "incluir"))
                    {
                        fscanf(mapa, "%i", id1); // id  
                        fscanf(mapa, "%[^\n]", descr); // nome

                        /* função <incluir_bairro> */
                    }

                        else if (strcmp(comando, "medir") == 0)
                        {
                            fscanf(mapa, "%i", id1); // id bairro 

                            /* função <medir_bairro> */
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

                            /* função <medir_cidade> */
                        }
                            else printf("Comando nao identificado.\n");
                    }

                        else printf("Comando nao identificado.\n");

            }

    return 0;
}