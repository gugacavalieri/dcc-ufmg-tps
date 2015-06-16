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

# Prova 02
### Bancos de dados geográficos

## Métodos de Acesso
* O SGBD utiliza o método de acesso aos dados que parece ser o mais adequado para a solução de cada operação
* Otimização heurística: Características estruturais da tabela e índices
* Otimização baseada em custos: Cálculos aproximados do custo da consulta
* Indice: Maneira rápida de buscar dados em uma tabela.
* Métodos tradicionais: Chaves alfabéticas ou numéricas simples
* Dados espaciais: Multidimensionais
* Métodos de acesso espaciais = Indices espaciais: Estruturas de dados auxiliares para garantir a eficiência de consultas espaciais. Ao contrário de índices tradicionais, estes são obrigatórios.
* Métodos de acesso espaciais: Filtragem da consulta para determinar um subconjunto de objetos que podem atender as especificações da consulta -> Executada com rapidez (Candidatos x Falso Candidatos)


## Tipos de índices espaciais
* Grid File: Baseado em hashing. Adequado para conjunto de pontos. Hashing em duas dimensões.
* K-d Tree: Indexa chaves formadas por k atributos. Cada nível da árvore corresponde a uma das dimensões. (i.e níveis pares indexam 'x', níveis impares indexam 'y')
* Quad-tree: Arvore em que cada nó possui quatro folhas. Folhas equivalem a divisão de um quadrado em 4 quadrantes.
* Tiling: Divisão em camadas de quadrados
* R-Tree: Indexa objetos pelo seu retangulo envolvente mínimo. Cada bloco de armazenamento pode conter um número variável de retângulos. Aumento de objetos causa subdivisões nos blocos e redução causa fusões de blocos
* Exitem diversas variações da R-tree visando o aumento da eficiência desta.

## Processamento de consultas
* Nem sempre o otimizador conseguirá melhor desempenho apenas escolhendo os métodos de acesso e a ordem de execução
* Tuning: Processo de melhoramento do desempenho de um gerenciador de banco de dados
* Tuning envolve várias variáveis: SO, hardware, etc
* Exemplos de tuning: I/O, SGBD, Consultas (plano de execução).

## Padrões OGC e Serviços Web Geoespaciais
* O OGC idealizou uma arquitetura para acesso distribuido a dados geo-espaciais -> Serviços Web OGC
* Service Oriented Architecture (SOA): Funções implementadas e usadas pelas aplicações são definidas sob a forma de serviçõs
* Serviço deve funcionar de forma independente de outros serviços. Deve possuir interface bem definida. Deve aceitar uma ou mais requisições devolvendo uma ou mais respostas. Quem invoca não conhece a implementação. 
* Padrões para a invocação do serviço evoluíram a partir de padrões como RPC. Processo de comunicação entre cliente e servidor.
* Existem mais de 30 padrões OGC relacionados a serviços e seus componentes.

## Serviços Web OGC

### Web Map Service (WMS)

* Web Map Service (WMS): Recupera mapas prontos em formato de imagem. Mapas construídos no servidor
* GetCapabilities: Retorna um documento XML descrevendo as interfaces suportadas
* GetMap: Cliente solicita um mapa indicando componentes do **GetCapabilities** para compo-lo.
* WMS: Sem um mecanismo de **Tiling** e **Cache**, tende a ser pesado e com limitações de escalabilidade. 
* Servidores **WMS**: MapServer, GeoServer
* Clientes **WMS**: QuantumGIS, OpenJUMP, uDig, etc...

### Web Feature Service (WFS)

* Acesso a features -> objetos geográficos completos (atributos, geometria)
* Features transportados em GML
* GetCapabilities, GetFeature
* Servidores: GeoServer, MapServer
* Clientes: uDig, Gaia, OpenLayers

### OGC e ISO
* Os padrões OGC e ISO foram unidos.
* Na prática ambos os padrões são a mesma coisa
