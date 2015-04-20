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

    // Alocações
    comando = (char*)malloc(9*sizeof(char));
    descr = (char*)malloc(60*sizeof(char));
    id1 = (int*)malloc(sizeof(int));
    id2 = (int*)malloc(sizeof(int));

    // Inicialização
    mapa = abrirMapa();
    head_bairro = inicia_bairro();

            

    //while(comando != EOF)    ~ ativar depois para ler todo o arquivo
    //{                         ~ por enquanto estou testando apenas com uma linha do arquivo teste

        fscanf(mapa, "%s", comando);  // rua, casa, bairro ou cidade

        // -----  RUA
        if (strcmp(comando, "rua") == 0)
            {
                fscanf(mapa, "%s", comando); // incluir, eliminar ou medir

                if (strcmp(comando, "incluir") == 0)
                {
                    fscanf(mapa, "%i", id1); // id bairro
                    fscanf(mapa, "%i", id2); // id rua  
                    fscanf(mapa, "%[^\n]", descr); // nome   
                    
                    head_bairro = insere_bairro(id1, "camburi");   // para testar o funcionamento
                    printf("%i, %s\n", *head_bairro->id_bairro, head_bairro->nome_bairro);

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

            // -----  RUA
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



    return 0;
}
