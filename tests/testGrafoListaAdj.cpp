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
	EXPECT_EQ(grafo->getVertices().size(), 0);
	EXPECT_EQ(grafo->getArestas().size(), 0);
	grafo->inserirVertice("v1");
	EXPECT_EQ(grafo->getVertices().size(), 1);
	EXPECT_EQ(grafo->getArestas().size(), 1);
	grafo->inserirVertice("v2");
	EXPECT_EQ(grafo->getVertices().size(), 2);
	EXPECT_EQ(grafo->getArestas().size(), 2);
}

TEST_F(GrafoListaAdjTest, InsercaoVerticeRepetido) {
	EXPECT_EQ(grafo->getVertices().size(), 0);
	EXPECT_EQ(grafo->getArestas().size(), 0);
	grafo->inserirVertice("v1");
	EXPECT_EQ(grafo->getVertices().size(), 1);
	EXPECT_EQ(grafo->getArestas().size(), 1);
	grafo->inserirVertice("v1");
	EXPECT_EQ(grafo->getVertices().size(), 1);
	EXPECT_EQ(grafo->getArestas().size(), 1);
}

void inserirVertices(GrafoListaAdj* grafoNaoPonderado) {
	for (int i = 1; i <= 9; i++) {
		string rotulo;
		std::stringstream sstm;
		sstm << "v" << i;
		rotulo = sstm.str();
		grafoNaoPonderado->inserirVertice(rotulo);
	}
}

TEST_F(GrafoListaAdjTest, InsercaoArestaNaoDirecionadaNaoPonderada) {
	inserirVertices(grafo);
	EXPECT_EQ(grafo->getVertices().size(), 9);
	EXPECT_EQ(grafo->getArestas().size(), 9);

	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v3", "v4");

	/* verificando se v2 estah na lista de conexoes de v1 */
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);	//v1 estah no indice 0
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 0);  //peso eh 0

	/* verificando se v1 estah na lista de conexoes de v2 */
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);	//v2 estah no indice 1
	EXPECT_EQ(conexoesV2.at(0).first, 0);	//indice de v1 eh 0
	EXPECT_EQ(conexoesV2.at(0).second, 0);  //peso eh 0

	/* verificando se v4 estah na lista de conexoes de v3 */
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);	//v3 estah no indice 2
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 0);  //peso eh 0

	/* verificando se v3 estah na lista de conexoes de v4 */
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);	//v4 estah no indice 3
	EXPECT_EQ(conexoesV4.at(0).first, 2);	//indice de v3 eh 1
	EXPECT_EQ(conexoesV4.at(0).second, 0);  //peso eh 0
}

TEST_F(GrafoListaAdjTest, InsercaoArestaNaoDirecionadaPonderada) {
	inserirVertices(grafo);
	grafo->inserirArestaNaoDirecionada("v1", "v2", 4);
	grafo->inserirArestaNaoDirecionada("v3", "v4", 9);

	/* verificando se v2 estah na lista de conexoes de v1 */
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);	//v1 estah no indice 0
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 4);  //peso eh 4

	/* verificando se v1 estah na lista de conexoes de v2 */
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);	//v2 estah no indice 1
	EXPECT_EQ(conexoesV2.at(0).first, 0);	//indice de v1 eh 0
	EXPECT_EQ(conexoesV2.at(0).second, 4);  //peso eh 4

	/* verificando se v4 estah na lista de conexoes de v3 */
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);	//v3 estah no indice 2
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 9);  //peso eh 9

	/* verificando se v3 estah na lista de conexoes de v4 */
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);	//v4 estah no indice 3
	EXPECT_EQ(conexoesV4.at(0).first, 2);	//indice de v3 eh 1
	EXPECT_EQ(conexoesV4.at(0).second, 9);  //peso eh 9
}

TEST_F(GrafoListaAdjTest, InsercaoArestaDirecionadaNaoPonderada) {
	inserirVertices(grafo);

	grafo->inserirArestaDirecionada("v1", "v2");
	grafo->inserirArestaDirecionada("v3", "v4");

	/* verificando se v2 estah na lista de conexoes de v1 */
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);	//v1 estah no indice 0
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 0);  //peso eh 0

	/* verificando se v1 NAO estah na lista de conexoes de v2 */
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);	//v2 estah no indice 1
	EXPECT_EQ(conexoesV2.size(),0);	//nao existe vertice nessa lista de conexoes

	/* verificando se v4 estah na lista de conexoes de v3 */
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);	//v3 estah no indice 2
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 0);  //peso eh 0

	/* verificando se v3 NAO estah na lista de conexoes de v4 */
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);	//v4 estah no indice 3
	EXPECT_EQ(conexoesV4.size(), 0);	//nao existe vertice nessa lista de conexoes
}

TEST_F(GrafoListaAdjTest, InsercaoArestaDirecionadaPonderada) {
	inserirVertices(grafo);

	grafo->inserirArestaDirecionada("v1", "v2", 4);
	grafo->inserirArestaDirecionada("v3", "v4", 9);

	/* verificando se v2 estah na lista de conexoes de v1 */
	vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0);	//v1 estah no indice 0
	EXPECT_EQ(conexoesV1.at(0).first, 1);	//indice de v2 eh 1
	EXPECT_EQ(conexoesV1.at(0).second, 4);  //peso eh 4

	/* verificando se v1 NAO estah na lista de conexoes de v2 */
	vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1);	//v2 estah no indice 1
	EXPECT_EQ(conexoesV2.size(), 0);	//nao existe vertice nessa lista de conexoes

	/* verificando se v4 estah na lista de conexoes de v3 */
	vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2);	//v3 estah no indice 2
	EXPECT_EQ(conexoesV3.at(0).first, 3);	//indice de v4 eh 3
	EXPECT_EQ(conexoesV3.at(0).second, 9);  //peso eh 9

	/* verificando se v3 NAO estah na lista de conexoes de v4 */
	vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3);	//v4 estah no indice 3
	EXPECT_EQ(conexoesV4.size(), 0);	//nao existe vertice nessa lista de conexoes
}

TEST_F(GrafoListaAdjTest, SaoConectadosGrafoNaoDirecionado) {
	inserirVertices(grafo);

	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v3", "v4");

	EXPECT_TRUE(grafo->saoConectados("v1","v2"));
	EXPECT_TRUE(grafo->saoConectados("v2", "v1"));
	EXPECT_TRUE(grafo->saoConectados("v3", "v4"));
	EXPECT_TRUE(grafo->saoConectados("v4", "v3"));
}

TEST_F(GrafoListaAdjTest, SaoConectadosGrafoDirecionado) {
	inserirVertices(grafo);

	grafo->inserirArestaDirecionada("v1", "v2");
	grafo->inserirArestaDirecionada("v3", "v4");

	EXPECT_TRUE(grafo->saoConectados("v1", "v2"));
	EXPECT_FALSE(grafo->saoConectados("v2", "v1"));
	EXPECT_TRUE(grafo->saoConectados("v3", "v4"));
	EXPECT_FALSE(grafo->saoConectados("v4", "v3"));
}

/*TEST_F(GrafoListaAdjTest, dfs) {
	inserirVertices(grafo);
	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v1", "v3");
	grafo->inserirArestaNaoDirecionada("v2", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v5");
	grafo->inserirArestaNaoDirecionada("v4", "v6");
	grafo->inserirArestaNaoDirecionada("v4", "v7");
	//grafo->inserirArestaNaoDirecionada("v5", "v9");
	grafo->inserirArestaNaoDirecionada("v6", "v8");
	//grafo->inserirArestaNaoDirecionada("v8", "v9");

	vector<int> indicesVerticesVisitados;
	grafo->dfs("v1", &indicesVerticesVisitados);
	//for (int i = 0; i < indicesVerticesVisitados.size(); i++)
	//	cout << "Rótulo visitado: " << grafo->getVertices().at(i) << endl;

}*/

TEST_F(GrafoListaAdjTest, haCaminho) {
	inserirVertices(grafo);
	grafo->inserirArestaNaoDirecionada("v1", "v2");
	grafo->inserirArestaNaoDirecionada("v1", "v3");
	grafo->inserirArestaNaoDirecionada("v2", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v4");
	grafo->inserirArestaNaoDirecionada("v3", "v5");
	grafo->inserirArestaNaoDirecionada("v4", "v6");
	grafo->inserirArestaNaoDirecionada("v5", "v9");
	grafo->inserirArestaNaoDirecionada("v6", "v8");
	grafo->inserirArestaNaoDirecionada("v8", "v9");

	EXPECT_TRUE(grafo->haCaminho("v1","v1"));
	EXPECT_TRUE(grafo->haCaminho("v1","v2"));
	EXPECT_TRUE(grafo->haCaminho("v1","v9"));

	EXPECT_FALSE(grafo->haCaminho("v1","v7"));
	EXPECT_FALSE(grafo->haCaminho("v7","v5"));
}
