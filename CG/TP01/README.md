OPEN GALAXIAN - README
=======================
Aluno: Gustavo Cavalieri Fernandes - 2010049092
------------------------------------

# introdução

	O objetivo desse trabalho foi a implementação de um video game simples
	para o aprofundamento dos conceitos de 'opengl' e o tratamento de eventos.

------------------------------------

# compilação

	O jogo pode ser compilado através do comando 'make' no diretório em que
	o arquivo 'makefile' se encontra.
	
	bibliotecas necessárias:
	- opengl
	- glut (sudo apt-get install freeglut3-dev)

------------------------------------

# execução

	quando compilado o 'makefile' ira gerar o executavel 'galaxian' na pasta 'out'.
	
	para a execução do jogo devemos passar os seguintes parametros:
	
	./galaxian <LARGURA DA TELA> <ALTURA DA TELA>

	se nenhum parametro for especificado o jogo sera iniciado com as proporções padrões: 800 600

------------------------------------

# comandos

	teclado:
		'r' - reinicia jogo
		'esc' - sai do jogo
		
	mouse:
		'botão esquerdo' - dispara misseis
		'botão do meio' - modo depuração
		'botão direito' - pausa

------------------------------------

# principais decisões tomadas

## inimigos e IA
	Os inimigos são gerenciados pelo controlador de objetos ('objectController.c).
	A cada frame o controlador percorre a lista de inimigos para atualizar 
	posição e variáveis de cada alien. Durante essa iteração o inimigo possui
	uma determinada chance de atirar e tentar um ataque mais agressivo caso
	o número limite de inimigos realizando ataques agressivos não tenha sido
	atingido.

## waves
	Quando todas as naves inimigas são destruidas uma nova esquadra inimiga
	mais agressiva é criada. Essa nova esquadra contém o dobro do numero de inimigos
	da wave anterior e um numero maior de inimigos individuais pode iniciar um
	ataque mais agressivo.
	Por motivos de demonstração o jogo possui apenas três waves. Ao derrotar a terceira
	wave o jogador ganha o jogo.
	
## colisões
	Para detectar colisões foi utilizado os conceitos de 'bounding box':
	https://en.wikipedia.org/wiki/Minimum_bounding_rectangle
	O algoritmo de determinar orientação de pontos no espaço 2d também foi
	implementado para testar outros tipos de colisão.
	
## bombas e mísseis
	Assim como os inimigos as bombas e mísseis são gerenciadas pelo controlador
	de objetos ('objectController.c') através do uso de uma lista encadeada.
	A cada frame as variáveis de cada bala são atualizadas e é verificado se a 
	bala não está mais na área da tela, o que implica que ela deve ser removida da lista.

------------------------------------
