#include "pch.h"
#include "../src/grafos/grafonavegacaoexercicioalunos.h"
using namespace std;

class GrafoListaAdjNavegacaoTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		delete(grafo);
	}

	virtual void SetUp() {
		grafo = new GrafoListaAdj();
	}

	GrafoListaAdj* grafo;
};

/* Funcao auxiliar para construir o seguinte grafo nao ponderado:
 * https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-tad-rotulado-laco.png
 */
void construirGrafoNaoPonderadoNaoDirecionado(GrafoListaAdj* grafo) {
	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v1", "v3");
	grafo->inserirArestaNaoDirecionada("v2", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v5");
	grafo->inserirArestaNaoDirecionada("v4", "v6");
	grafo->inserirArestaNaoDirecionada("v4", "v7");
	grafo->inserirArestaNaoDirecionada("v5", "v9");
	grafo->inserirArestaNaoDirecionada("v6", "v8");
	grafo->inserirArestaNaoDirecionada("v8", "v9");
	grafo->inserirArestaNaoDirecionada("v9", "v9");
}

/* Funcao auxiliar para construir o seguinte grafo direcionado nao ponderado:
 * https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-tad-direcionado-testes-unidade.png
 */
void construirGrafoNaoPonderadoDirecionado(GrafoListaAdj* grafo) {
	grafo->inserirArestaDirecionada("v1", "v2");
	grafo->inserirArestaDirecionada("v1", "v3");
	grafo->inserirArestaDirecionada("v2", "v4");
	grafo->inserirArestaDirecionada("v3", "v5");
	grafo->inserirArestaDirecionada("v4", "v3");
	grafo->inserirArestaDirecionada("v5", "v9");
	grafo->inserirArestaDirecionada("v6", "v4");
	grafo->inserirArestaDirecionada("v6", "v8");
	grafo->inserirArestaDirecionada("v7", "v4");
	//v8 nao tem arestas partindo dele
	grafo->inserirArestaDirecionada("v9", "v8");
	grafo->inserirArestaDirecionada("v9", "v9");
	
}

/* Funcao auxiliar para adicionar vertices em uma sequencia.
 * Sao adicionados no seguinte formato: "v1", "v2", ...
 */
void inserirVertices(GrafoListaAdj* grafo, int ini, int fim) {
	for (int i = ini; i <= fim; i++) {
		string rotulo;
		std::stringstream sstm;
		sstm << "v" << i;
		rotulo = sstm.str();
		grafo->inserirVertice(rotulo);
	}
}

TEST_F(GrafoListaAdjNavegacaoTest, haCaminho) {
	//inserimos de v1 a v10, e v10 ficarah desconectado do componente principal
	inserirVertices(grafo,1,10);	
	construirGrafoNaoPonderadoDirecionado(grafo);		
		
	EXPECT_TRUE(grafo->haCaminho("v1","v2"));
	EXPECT_TRUE(grafo->haCaminho("v1","v4"));
	EXPECT_TRUE(grafo->haCaminho("v6", "v9"));
	EXPECT_TRUE(grafo->haCaminho("v9", "v9"));

	//note que v10 nao estah conectado	
	//logo, não existe caminhos chegando ou partindo de v10
	//embora nao exista v10 no grafo da url descrita, nos adicionamos v10 (linha 50)
	EXPECT_FALSE(grafo->haCaminho("v1","v10"));
	EXPECT_FALSE(grafo->haCaminho("v2", "v1"));
	EXPECT_FALSE(grafo->haCaminho("v1", "v1"));
	EXPECT_FALSE(grafo->haCaminho("v6", "v7"));
	EXPECT_FALSE(grafo->haCaminho("v10","v5"));
}

TEST_F(GrafoListaAdjNavegacaoTest, colorirGrafo1Comp) {
	//inserimos de v1 aa v9
	//esse grafo tem apenas um componente
	inserirVertices(grafo,1,9);
	construirGrafoNaoPonderadoNaoDirecionado(grafo);
	
	EXPECT_EQ(grafo->colorir(), 1);
	for (int i = 1; i <= 8; i++) {
		//depois de colorir o grafo, todos os rotulos 
		//dos vertices devem estar iguais
		EXPECT_EQ(grafo->getVertices().at(i - 1), grafo->getVertices().at(i));
	}
}

/* Funcao auxiliar para construir o seguinte grafo grafo de 5 componentes:
 * https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-nao-conectado-dfs.png
 * Segue uma img do grafo depois de ser colorido:
 * https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-nao-conectado-dfs-colorido.png
 */
void construirGrafoCom5Componentes(GrafoListaAdj* grafo) {
	//comp1
	grafo->inserirArestaNaoDirecionada("v0", "v4");
	grafo->inserirArestaNaoDirecionada("v0", "v8");
	grafo->inserirArestaNaoDirecionada("v0", "v13");
	grafo->inserirArestaNaoDirecionada("v0", "v14");

	//comp2
	grafo->inserirArestaNaoDirecionada("v1", "v5");
	grafo->inserirArestaNaoDirecionada("v5", "v16");
	grafo->inserirArestaNaoDirecionada("v5", "v17");

	//comp3
	grafo->inserirArestaNaoDirecionada("v3", "v9");
	grafo->inserirArestaNaoDirecionada("v9", "v2");
	grafo->inserirArestaNaoDirecionada("v15", "v9");
	grafo->inserirArestaNaoDirecionada("v15", "v2");
	grafo->inserirArestaNaoDirecionada("v15", "v10");

	//comp4
	grafo->inserirArestaNaoDirecionada("v6", "v7");
	grafo->inserirArestaNaoDirecionada("v6", "v11");
	grafo->inserirArestaNaoDirecionada("v7", "v11");

	//comp5: vértice "v12" (sem arestas)
}

TEST_F(GrafoListaAdjNavegacaoTest, colorirGrafo5Comp) {
	inserirVertices(grafo, 0, 17);
	construirGrafoCom5Componentes(grafo);	

	//verifico que o grafo tem 5 componentes
	EXPECT_EQ(grafo->colorir(), 5);

	//verifico que os vertices 0, 4, 8, 13, e 14 pertencem ao mesmo componente
	//por isso, depois da coloracao, esses vertices possuirao o mesmo rotulo
	string corComp1 = grafo->getVertices().at(0);
	EXPECT_EQ(grafo->getVertices().at(4), corComp1);
	EXPECT_EQ(grafo->getVertices().at(8), corComp1);
	EXPECT_EQ(grafo->getVertices().at(13), corComp1);
	EXPECT_EQ(grafo->getVertices().at(14), corComp1);

	//verifico que os vertices 1, 5, 16, e 17 pertencem ao mesmo componente
	//por isso, depois da coloracao, esses vertices possuirao o mesmo rotulo
	string corComp2 = grafo->getVertices().at(1);
	EXPECT_EQ(grafo->getVertices().at(5), corComp2);
	EXPECT_EQ(grafo->getVertices().at(16), corComp2);
	EXPECT_EQ(grafo->getVertices().at(17), corComp2);

	//verifico que os vertices 2, 3, 9, 10, e 15 pertencem ao mesmo componente
	//por isso, depois da coloracao, esses vertices possuirao o mesmo rotulo
	string corComp3 = grafo->getVertices().at(3);
	EXPECT_EQ(grafo->getVertices().at(9), corComp3);
	EXPECT_EQ(grafo->getVertices().at(15), corComp3);
	EXPECT_EQ(grafo->getVertices().at(2), corComp3);
	EXPECT_EQ(grafo->getVertices().at(10), corComp3);

	//verifico que os vertices 6, 7, e 11 pertencem ao mesmo componente
	//por isso, depois da coloracao, esses vertices possuirao o mesmo rotulo
	string corComp4 = grafo->getVertices().at(6);
	EXPECT_EQ(grafo->getVertices().at(7), corComp4);
	EXPECT_EQ(grafo->getVertices().at(11), corComp4);

	//verifico que o vertice 12 possui rotulo diferente dos rotulos
	//dos vertices que estao nos componentes 1, 2, 3, e 4
	EXPECT_NE(grafo->getVertices().at(12), corComp1);
	EXPECT_NE(grafo->getVertices().at(12), corComp2);
	EXPECT_NE(grafo->getVertices().at(12), corComp3);
	EXPECT_NE(grafo->getVertices().at(12), corComp4);
}

TEST_F(GrafoListaAdjNavegacaoTest, bfsGrafo1CompNaoPonderado) {
	inserirVertices(grafo, 1, 9);
	construirGrafoNaoPonderadoNaoDirecionado(grafo);

	int* distancias = grafo->bfs("v1");
	EXPECT_EQ(distancias[0], 0);
	EXPECT_EQ(distancias[1], 1);
	EXPECT_EQ(distancias[2], 1);
	EXPECT_EQ(distancias[3], 2);
	EXPECT_EQ(distancias[4], 2);
	EXPECT_EQ(distancias[5], 3);
	EXPECT_EQ(distancias[6], 3);
	EXPECT_EQ(distancias[7], 4);
	EXPECT_EQ(distancias[8], 3);
	free(distancias);

	distancias = grafo->bfs("v2");
	EXPECT_EQ(distancias[0], 1);
	EXPECT_EQ(distancias[1], 0);
	EXPECT_EQ(distancias[2], 2);
	EXPECT_EQ(distancias[3], 1);
	EXPECT_EQ(distancias[4], 3);
	EXPECT_EQ(distancias[5], 2);
	EXPECT_EQ(distancias[6], 2);
	EXPECT_EQ(distancias[7], 3);
	EXPECT_EQ(distancias[8], 4);
	free(distancias);
}

TEST_F(GrafoListaAdjNavegacaoTest, bfsGrafo5CompNaoPonderado) {
	inserirVertices(grafo, 0, 17);
	construirGrafoCom5Componentes(grafo);

	int* distancias = grafo->bfs("v0");
	EXPECT_EQ(distancias[0], 0);
	EXPECT_EQ(distancias[1], 0);
	EXPECT_EQ(distancias[2], 0);
	EXPECT_EQ(distancias[3], 0);
	EXPECT_EQ(distancias[4], 1);
	EXPECT_EQ(distancias[5], 0);
	EXPECT_EQ(distancias[6], 0);
	EXPECT_EQ(distancias[7], 0);
	EXPECT_EQ(distancias[8], 1);
	EXPECT_EQ(distancias[9], 0);
	EXPECT_EQ(distancias[10], 0);
	EXPECT_EQ(distancias[11], 0);
	EXPECT_EQ(distancias[12], 0);
	EXPECT_EQ(distancias[13], 1);
	EXPECT_EQ(distancias[14], 1);
	EXPECT_EQ(distancias[15], 0);
	EXPECT_EQ(distancias[16], 0);
	EXPECT_EQ(distancias[17], 0);
	free(distancias);

	distancias = grafo->bfs("v1");
	EXPECT_EQ(distancias[0], 0);
	EXPECT_EQ(distancias[1], 0);
	EXPECT_EQ(distancias[2], 0);
	EXPECT_EQ(distancias[3], 0);
	EXPECT_EQ(distancias[4], 0);
	EXPECT_EQ(distancias[5], 1);
	EXPECT_EQ(distancias[6], 0);
	EXPECT_EQ(distancias[7], 0);
	EXPECT_EQ(distancias[8], 0);
	EXPECT_EQ(distancias[9], 0);
	EXPECT_EQ(distancias[10], 0);
	EXPECT_EQ(distancias[11], 0);
	EXPECT_EQ(distancias[12], 0);
	EXPECT_EQ(distancias[13], 0);
	EXPECT_EQ(distancias[14], 0);
	EXPECT_EQ(distancias[15], 0);
	EXPECT_EQ(distancias[16], 2);
	EXPECT_EQ(distancias[17], 2);
	free(distancias);

	distancias = grafo->bfs("v11");
	EXPECT_EQ(distancias[0], 0);
	EXPECT_EQ(distancias[1], 0);
	EXPECT_EQ(distancias[2], 0);
	EXPECT_EQ(distancias[3], 0);
	EXPECT_EQ(distancias[4], 0);
	EXPECT_EQ(distancias[5], 0);
	EXPECT_EQ(distancias[6], 1);
	EXPECT_EQ(distancias[7], 1);
	EXPECT_EQ(distancias[8], 0);
	EXPECT_EQ(distancias[9], 0);
	EXPECT_EQ(distancias[10], 0);
	EXPECT_EQ(distancias[11], 0);
	EXPECT_EQ(distancias[12], 0);
	EXPECT_EQ(distancias[13], 0);
	EXPECT_EQ(distancias[14], 0);
	EXPECT_EQ(distancias[15], 0);
	EXPECT_EQ(distancias[16], 0);
	EXPECT_EQ(distancias[17], 0);
	free(distancias);

	distancias = grafo->bfs("v3");
	EXPECT_EQ(distancias[0], 0);
	EXPECT_EQ(distancias[1], 0);
	EXPECT_EQ(distancias[2], 2);
	EXPECT_EQ(distancias[3], 0);
	EXPECT_EQ(distancias[4], 0);
	EXPECT_EQ(distancias[5], 0);
	EXPECT_EQ(distancias[6], 0);
	EXPECT_EQ(distancias[7], 0);
	EXPECT_EQ(distancias[8], 0);
	EXPECT_EQ(distancias[9], 1);
	EXPECT_EQ(distancias[10], 3);
	EXPECT_EQ(distancias[11], 0);
	EXPECT_EQ(distancias[12], 0);
	EXPECT_EQ(distancias[13], 0);
	EXPECT_EQ(distancias[14], 0);
	EXPECT_EQ(distancias[15], 2);
	EXPECT_EQ(distancias[16], 0);
	EXPECT_EQ(distancias[17], 0);
	free(distancias);
}