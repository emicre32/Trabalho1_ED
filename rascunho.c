#include <stdio.h>
#include <stdlib.h>


struct Casa
{
   int id_consumidor;
   int casa;
   float consumo;
   char nome_consumidor[100];
   struct Casa *proxc;
}

typedef struct Casa house; 

struct Rua
{
   int id_rua;
   char nome_rua[100];
   house *head_casa;
   struct Rua *proxr;

}

typedef struct Rua street;

struct Bairro
{
	int id_bairro;
	char nome_bairro[100];
	street *head_rua;
	struct Bairro *proxb;
}

typedef struct Bairro nhood;
