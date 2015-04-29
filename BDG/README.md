# Banco de Dados Geográficos
----------------------------

## Conceitos Iniciais

* Modelo OMT-G: Contém recursos para modelar aplicações geográficas, incluindo classes de objetos, relacionamentos convencionais e espaciais.
* Representação: Codificação da geometria de objetos espaciais
* Visualização: Aspecto visual. Conversão da representação para um modelo visual. Aparência gráfica (cor, tipo de linha, simbologia, etc)
* SIG x Cartografia: SIG se preocupa mais com a representação enquanto cartografia da ênfase maior na apresentação e na legibilidade
* SIG x Cargografia: Precisão do dado x precisão do resultado impresso
* Representar um objeto do mundo real é um processo difícil que requer muita abstração. Muitas vezes discretização e amostragem são utilizados para aproximas o resultado
* A complexidade de uma representação depende do propósito da aplicação

## Alternativas de representação

### Geo-objetos
* Ponto
* Linha
* Polígono
* Nó de Rede
* Arco unidirecional
* Arco bidirecional

### Geocampos
* Isolinhas
* Tesselação
* Subdivisão Planar
* Rede triangular
* Amostras

## Generalização e agregação:

				  .			 			 /\
 /\				 / \					/xx\
/__\			/___\	 	  		   /xxxx\
Uma opção	   Uma opção  			Sobreposição
Not Null 	  Pode ser Nulo	      (terminal -> Onibus e Metro)


______/\|------------|
      \/| Classe     | Agregação: Uma classe não faz sentido sem a outra (i.e Quadra e Lote)
		|------------|


## Diagramas de apresentação

Utiliza as classes do modelo OMT-G para demonstrar como o objeto deve ser apresentado na camada de apresentação. 
Por exemplo temos uma classe Quadra (Polígono) sendo representada através dos atributos: Linha = Continua; Cor = Vermelho;

## Topologia e Relacionamentos Espaciais

* A linguagem natural eh ambígua. Limitada em expressividade. i.e: linha cruza poligono? Ambíguo e pode ser visualizado em vários cenários
* Relacionamentos espaciais: posicionamento relativo entre objetos
* Matriz de interseção: Identificar os casos de posicionamento relativo dos objetos.
* Matriz de 6 e 9 interseções. A matriz de nove interseções surgiu para cobrir as limitações da matriz de 4.
* Disputa das amebas: 9 possíveis combinações: A disjunto B, A encontra B, A sobrepoe B, A encoberto B, A esta contido em B, A encobre B, A contem B, A igual a B
* Relacionamentos Direcionais: Futuros estudos para determinar a posição de um objeto em relação ao outro (i.e Ao norte, ao sudoeste ..)
* PostGIS: Extensão do PostgreSQL com diversas funções geográficas implementadas para determinar relacionamentos espaciais e topologia

## Projeto Lógico e restições de Integridade

* O modelo OMT-G deve ser transformado para um modelo lógico que possua um conjunto de relações, atributos e restrições de integridade
* As únicas representaçãoes geográficas disponíveis no esquema lógico OR são: Ponto, Linha, Polígono, Tesselação(GeoRaster).
* Restrições: Regras para garantir a integridade do banco em qualquer operação
* Em bancos espaciais existem restrições extras: Topológicas, geométricas e semânticas

### Restrições Geo espaciais
**GEOCAMPOS**
* R1: Preenchimento do Plano 
* R2: Isolinhas
* R3: Tesselação
* R4: Subdivisão planar
* R5: Triangulação
* R6: Rede arco-nó
* R7: Rede Arco-Arco
* R8: Agregação espacial
* R9: Linhas
* R10: Poligonos Simples
* R11: Regiões Poligonais
* RT: Topológicas
