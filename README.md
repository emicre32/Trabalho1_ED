# Trabalho1_ED

_Cidade_ 

	[ ] medir consumo (NO PARAMETERS REQUIRED)

_Bairro_ (id, Nome)

	[ x ] [inicialização] incluir na cidade
		>> id, nome


_Rua_ (id, Nome)

	[ x ] incluir 
		>> id bairro, id rua, nome

	[ x ] eliminar do bairro 
		>> id bairro, id rua

	[ ] medir 
		>> id bairro, id rua


_Casa_ (id do consumidor, número da casa, consumo, nome do consumidor)

	[ ] incluir 
		>> id bairro, id rua, id consumidor, num da casa, consumo, nome do consumidor
	
	[ ] eliminar da rua
	
	[ ] consumir 
		>> id bairro, id rua, id casa, consumo
	
	[ ] medir 
		>> id bairro, id rua, id casa
