#include "pch.h"
#include "../src/grafos/grafolistaadj.h"
using namespace std;

class GrafoListaAdjTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		delete(grafo);
	}

	virtual void SetUp() {
		grafo = new GrafoListaAdj();
	}

	GrafoListaAdj* grafo;
};

TEST_F(GrafoListaAdjTest, InsercaoVertice) {
	//verificando que nao ha vertices e arestas
	EXPECT_EQ(grafo->getVertices().size(), 0);
	EXPECT_EQ(grafo->getArestas().size(), 0);

	//verificando que ha 1 vertice e 1 lista de arestas (mesmo que vazia)
	grafo->inserirVertice("v1");
	EXPECT_EQ(grafo->getVertices().size(), 1);
	EXPECT_EQ(grafo->getArestas().size(), 1);

	//verificando que ha 2 vertices e 2 listas de arestas (mesmo que vazias)
	grafo->inserirVertice("v2");
	EXPECT_EQ(grafo->getVertices().size(), 2);
	EXPECT_EQ(grafo->getArestas().size(), 2);
}

TEST_F(GrafoListaAdjTest, InsercaoVerticeRepetido) {
	//verificando que apos inserir o mesmo vertice 2 vezes
	//havera apenas 1 vertice e 1 lista de arestas (mesmo que vazia)
	grafo->inserirVertice("v1");
	grafo->inserirVertice("v1");
	EXPECT_EQ(grafo->getVertices().size(), 1);
	EXPECT_EQ(grafo->getArestas().size(), 1);
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

TEST_F(GrafoListaAdjTest, InsercaoArestaNaoDirecionadaNaoPonderada) {
	inserirVertices(grafo,1,9);
	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v3", "v4");

	// verificando que v2 estah na lista de conexoes de v1
	// lembrando que os vizinhos de v1 estao no indice 0 da lista de arestas
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);	
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 1);  //peso eh 1

	// verificando que v1 estah na lista de conexoes de v2
	// lembrando que os vizinhos de v2 estao no indice 1 da lista de arestas
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);
	EXPECT_EQ(conexoesV2.at(0).first, 0);	//indice de v1 eh 0
	EXPECT_EQ(conexoesV2.at(0).second, 1);  //peso eh 1

	// verificando que v4 estah na lista de conexoes de v3
	// lembrando que os vizinhos de v3 estao no indice 2 da lista de arestas
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 1);  //peso eh 1

	// verificando que v3 estah na lista de conexoes de v4
	// lembrando que os vizinhos de v4 estao no indice 3 da lista de arestas
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);
	EXPECT_EQ(conexoesV4.at(0).first, 2);	//indice de v3 eh 1
	EXPECT_EQ(conexoesV4.at(0).second, 1);  //peso eh 1
}

TEST_F(GrafoListaAdjTest, InsercaoArestaNaoDirecionadaPonderada) {
	inserirVertices(grafo,1,9);
	grafo->inserirArestaNaoDirecionada("v1", "v2", 4);
	grafo->inserirArestaNaoDirecionada("v3", "v4", 9);

	// verificando que v2 estah na lista de conexoes de v1
	// lembrando que os vizinhos de v1 estao no indice 0 da lista de arestas
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 4);  //peso eh 4

	// verificando que v1 estah na lista de conexoes de v2
	// lembrando que os vizinhos de v2 estao no indice 1 da lista de arestas
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);	
	EXPECT_EQ(conexoesV2.at(0).first, 0);	//indice de v1 eh 0
	EXPECT_EQ(conexoesV2.at(0).second, 4);  //peso eh 4

	// verificando que v4 estah na lista de conexoes de v3
	// lembrando que os vizinhos de v3 estao no indice 2 da lista de arestas
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 9);  //peso eh 9

	// verificando que v3 estah na lista de conexoes de v4
	// lembrando que os vizinhos de v4 estao no indice 3 da lista de arestas
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);
	EXPECT_EQ(conexoesV4.at(0).first, 2);	//indice de v3 eh 1
	EXPECT_EQ(conexoesV4.at(0).second, 9);  //peso eh 9
}

TEST_F(GrafoListaAdjTest, InsercaoArestaDirecionadaNaoPonderada) {
	inserirVertices(grafo,1,9);
	grafo->inserirArestaDirecionada("v1", "v2");
	grafo->inserirArestaDirecionada("v3", "v4");

	// verificando que v2 estah na lista de conexoes de v1
	// lembrando que os vizinhos de v1 estao no indice 0 da lista de arestas
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 1);  //peso eh 1

	// verificando que v1 NAO estah na lista de conexoes de v2
	// lembrando que os vizinhos de v2 estao no indice 1 da lista de arestas
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);
	EXPECT_EQ(conexoesV2.size(),0);	//nao existe vertice nessa lista de conexoes

	// verificando que v4 estah na lista de conexoes de v3
	// lembrando que os vizinhos de v3 estao no indice 2 da lista de arestas
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 1);  //peso eh 1

	// verificando que v3 NAO estah na lista de conexoes de v4
	// lembrando que os vizinhos de v4 estao no indice 3 da lista de arestas
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);
	EXPECT_EQ(conexoesV4.size(), 0);	//nao existe vertice nessa lista de conexoes
}

TEST_F(GrafoListaAdjTest, InsercaoArestaDirecionadaPonderada) {
	inserirVertices(grafo,1,9);
	grafo->inserirArestaDirecionada("v1", "v2", 4);
	grafo->inserirArestaDirecionada("v3", "v4", 9);

	// verificando que v2 estah na lista de conexoes de v1
	// lembrando que os vizinhos de v1 estao no indice 0 da lista de arestas
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 4);  //peso eh 4

	// verificando que v1 NAO estah na lista de conexoes de v2
	// lembrando que os vizinhos de v2 estao no indice 1 da lista de arestas
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);
	EXPECT_EQ(conexoesV2.size(), 0);	//nao existe vertice nessa lista de conexoes

	// verificando que v4 estah na lista de conexoes de v3
	// lembrando que os vizinhos de v3 estao no indice 2 da lista de arestas
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 9);  //peso eh 9

	// verificando que v3 NAO estah na lista de conexoes de v4
	// lembrando que os vizinhos de v4 estao no indice 3 da lista de arestas
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);
	EXPECT_EQ(conexoesV4.size(), 0);	//nao existe vertice nessa lista de conexoes
}

TEST_F(GrafoListaAdjTest, SaoConectadosGrafoNaoDirecionado) {
	inserirVertices(grafo,1,9);
	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v3", "v4");

	EXPECT_TRUE(grafo->saoConectados("v1","v2"));
	EXPECT_TRUE(grafo->saoConectados("v2", "v1"));
	EXPECT_TRUE(grafo->saoConectados("v3", "v4"));
	EXPECT_TRUE(grafo->saoConectados("v4", "v3"));
}

TEST_F(GrafoListaAdjTest, SaoConectadosGrafoDirecionado) {
	inserirVertices(grafo,1,9);

	grafo->inserirArestaDirecionada("v1", "v2");
	grafo->inserirArestaDirecionada("v3", "v4");

	EXPECT_TRUE(grafo->saoConectados("v1", "v2"));
	EXPECT_FALSE(grafo->saoConectados("v2", "v1"));
	EXPECT_TRUE(grafo->saoConectados("v3", "v4"));
	EXPECT_FALSE(grafo->saoConectados("v4", "v3"));
}