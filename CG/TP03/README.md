GG_RAY_TRACER - README
=======================
Aluno: Gustavo Cavalieri Fernandes - 2010049092
Computação Gráfica 2014/2
------------------------------------

# introdução

	O objetivo desse trabalho foi a implementação de um ray tracer para
	o aprendizado de iluminação, reflexão e texturas.

------------------------------------

# compilação

	O programa pode ser compilado através do comando 'make' no diretório em que
	o arquivo 'makefile' se encontra ( 'Release/make ' ).
	
	exemplo compilação:
		cd Release
		make
	
	os comandos acima gerarão o executável TP03.
	
	para remover os arquivos de compilação podemos utilizar o comando:
		make clean
	
	bibliotecas necessárias:
	- g++ (sudo apt-get install g++)
	
	obs: O raytracer foi implementado em C++ nativo. Não foi utilizada nenhuma
	biblioteca do OpenGL.

------------------------------------

# execução

	quando compilado o 'makefile' ira gerar o executavel 'TP03' na pasta 'Release'.
	
	para a execução do raytracer devemos passar os seguintes parametros:
	
	./TP03 <ARQUIVO DE ENTRADA> <ARQUIVO DE SAIDA> (<LARGURA> <ALTURA>)

	se os parametros <LARGURA> e <ALTURA> não forem especificados, a imagem 
	será gerada com resolução padrão: 800 600

------------------------------------

# funcionalidades implementadas:

	1. Ray casting / Ray tracing
	
	2. Cores
	
	3. Reflexão de raios lançados
	
	4. Sombras
	
	5. Camera
	
	6. Iluminação (Várias fontes de luz)
	
	7. Padrões 'checked'
	
	8. Padrões solid
	
	9. Objetos: esfera e planos
	
	10. Temporizador
	
	
------------------------------------
