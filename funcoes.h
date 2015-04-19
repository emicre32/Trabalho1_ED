typedef struct rua_bairro {
	int id;
	char nome;
	struct tipoRB * prox;
} TipoRB;

typedef struct moradias {
	int id_consumidor;
	int id_casa;
	int consumo;
	char consumidor;
	struct moradias * prox;
} Casa;
