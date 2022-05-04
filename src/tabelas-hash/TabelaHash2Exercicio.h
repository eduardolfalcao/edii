#include <vector>
#include<iostream>
using namespace std;

template <typename K, typename V>
class Tupla {
	private:
		K chave;
		V valor;
		Tupla* prox;
	public:
		Tupla(K c, V v){
			chave = c;
			valor = v;
			prox = NULL;
		}

		K getChave() {
			return chave;
		}

		V getValor() {
			return valor;
		}

		Tupla* getProx() {
			return prox;
		}

		void setProx(Tupla* prox) {
			Tupla::prox = prox;
		}
};

template <typename Chave, typename Valor>
class TabelaHash2{
	
	private:
		Tupla<Chave, Valor>** tabela;
		
		//tamanho atual do array
		int qtdeBuckets;
		//qtdade de elementos já inseridos na tabela hash
		int qtdadeElementos;

		/**
		* Função para inserir a tupla <c,v> na tabela.
		* 1) É preciso calcular o código hash a partir da chave c.
		* 2) Depois, usamos qtdeBuckets para descobrir o índice 
		* dessa tupla, usando a operacao de modulo.
		* 3) Preste atenção na alocação de tupla quando há colisões. 
		* 4) A função hash às vezes retorna valores negativos: use abs() 
		* para evitar índices negativos.
		* 5) Como a implementacao eh in-place, se novoElemento for false,
		* o que indica que estamos reposicionando um elemento devido
		* ao aumento do array, podemos nos deparar com duas situações:
		*     Situação 1: o elemento foi mapeado para o mesmo bucket,
		*                 independente da mudança do array. Nesse caso,
		*                 não precisamos inseri-lo em um novo bucket.
		*     Situação 2: o elemento foi mapeado para outro bucket. 
		*                 Nesse caso, precisamos inseri-lo em um novo 
		*                 bucket.
		* IMPORTANTE: o retorno dessa funcao indica se um elemento
		*             foi reposicionado para um novo bucket. Esse valor
		*			  será utilizado na função para aumento do tamanho
		*			  do array. Perceba que esse retorno não é útil
		*			  para a função pública inserir(Chave c, Valor v)
		**/ 
		bool inserir(Chave c, Valor v, bool novoElemento) {
			//IMPLEMENTAR
		}

		/**
		* Função para aumentar o tamanho do array
		* 1) O tamanho do array (qtdeBuckets) deve ser multiplicado 
		* por 8 para que essa operação seja feita com pouca frequência.
		* 2) Reposicionar as tuplas, considerando que:
		*     2.1) mesmo mudando de tamanho, ela pode permanecer no 
		*	 mesmo bucket (posicao do array).
		*	 2.2) caso ela mude de posição, atente para a situação
		*		  da lista ligada, especialmente quando há colisões:
		*		2.2.1) esse elemento é o primeiro da lista ligada?
		*		talvez o ponteiro que fica no array precise ser 
		*		atualizado (para NULL, caso seja o único do bucket,
		*		ou para o elemento posterior, caso contrário)
		*		2.2.2) esse elemento está no meio da lista ligada?
		*		ajuste o ponteiro prox do elemento anterior ao elemento
		*		removido
		*	Dica: você precisará navegar com 2 variáveis auxiliares,
		*		  de modo que uma esteja sempre apontando para o 
		*		  elemento anterior.
		* 3) Não se esqueça de desalocar (delete) as tuplas que
		* você está inserindo em uma nova posição do array.
		**/
		void aumentaArray() {
			//IMPLEMENTAR
		}

	public:

		/**
		* Construtor
		* 1) Inicializar o array de tuplas com qtdeBuckets=8.
		* 2) Lembrar de setar todas as posições do vetor inicializado
		*    para NULL.
		* 3) Alocar o vetor no C-Style (calloc), para que depois 
		*    consigamos usar a função realloc para trabalhar com 
		*    o tamanho do vetor completamente in-place.
		**/ 
		TabelaHash2() {
			//IMPLEMENTAR
		}

		/**
		* Essa é a função pública que nos permite inserir
		* uma tupla <c,v> na tabela. 
		* 1) Aumentamos o array caso o load_factor >=1.
		* 2) Essa função pode reusar sua versão
		* sobrecarregada para inserir a tupla na tabela.
		* 3) Essa função também incrementa a quantidade de elementos
		* na tabela (variável qtdadeElementos).
		**/ 
		void inserir(Chave c, Valor v) {
			//IMPLEMENTAR
		}

		/**
		* Essa função retorna o fator de carga da Tabela Hash.
		**/
		double load_factor() {
			//IMPLEMENTAR
		}
		
		/**
		* Há apenas um valor associado a uma chave.
		* Essa função retorna esse valor, caso a chave exista.
		* Se a chave não existir a função retorna NULL.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/ 
		Valor getValor(Chave chave) {
			//IMPLEMENTAR	
		}

		/**
		* Essa função retorna true caso a chave exista,
		* false caso contrário.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
		bool contemChave(Chave chave) {
			//IMPLEMENTAR
		}

		/**
		* Essa função retorna um vetor com todas as chaves
		* já inseridas na tabela.
		**/
		vector<Chave> getChaves() {
			//IMPLEMENTAR
		}

		/**
		* Essa função desaloca os nós previamente alocados, e muda
		* o tamanho do array de tuplas para 8.
		**/
		void clear() {
			//IMPLEMENTAR
		}

		/**
		* Há apenas um nó associado com uma mesma chave.
		* Essa função remove esse nó da tabela, caso a chave exista.
		* Se a chave não existir a função não faz nada.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		* Dica: olhar algoritmo de remoção em lista ligada, pois
		* após a remoção de um nó a lista precisa permanecer íntegra,
		* ou seja, navegável.
		**/
		void remover(Chave chave) {
			//IMPLEMENTAR
		}

		/**
		* Essa função retorna a quantidade de elementos
		* que já foram inseridos na Tabela Hash.
		**/
		int size() {
			return qtdadeElementos;
		}

		/**
		* Essa função retorna o tamanho atual do
		* array usado para armazenar a Tabela Hash.
		**/
		int bucket_count() {
			return qtdeBuckets;
		}
};