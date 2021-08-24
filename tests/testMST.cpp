#include "pch.h"
#include "../src/grafos/grafomst.h"
using namespace std;

class MSTTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		delete(grafo);
	}

	virtual void SetUp() {
		grafo = new GrafoListaAdj();
	}

	GrafoListaAdj* grafo;
};

/* Funcao auxiliar para inserir uma sequencia de vertices comecando
 * em ini e terminando em fim. Ex: v1, v2, v3, ..., v9.
 */
void inserirVertices(GrafoListaAdj* grafo, int ini, int fim) {
	for (int i = ini; i <= fim; i++) {
		string rotulo;
		stringstream sstm;
		sstm << "v" << i;
		rotulo = sstm.str();
		grafo->inserirVertice(rotulo);
	}
}

int somaArestasMST(GrafoListaAdj* grafoMST) {
	int pesoArestas = 0;
	cout << "Tamanho: " << to_string(grafoMST->getArestas().size()) << endl;
	for (int vOrigem = 0; vOrigem < grafoMST->getArestas().size(); vOrigem++) {
		cout << "Qtdade de Arestas com origem em " << to_string(vOrigem) <<": " << to_string(grafoMST->getArestas().at(vOrigem).size()) << endl;
		if (!grafoMST->getArestas().at(vOrigem).empty()) {
			//for (pair<int, int> arestaSaindoDeVOrigem : grafoMST->getArestas().at(vOrigem)) {
			for (int i = 0; i < grafoMST->getArestas().at(vOrigem).size(); i++) {
				cout << "Par: (" << to_string(grafoMST->getArestas().at(vOrigem).at(i).first) << "," << to_string(grafoMST->getArestas().at(vOrigem).at(i).second) << ")" << endl;
				//first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
				pesoArestas += grafoMST->getArestas().at(vOrigem).at(i).second;
			}
		}
	}
	return pesoArestas;
}

TEST_F(MSTTest, Grafo1) {
	inserirVertices(grafo, 1, 9);
	
	//https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-ponderado-representacao-matriz-preenchido.png
	grafo->inserirArestaNaoDirecionada("v1", "v2", 6);
	grafo->inserirArestaNaoDirecionada("v1", "v3", 4);
	grafo->inserirArestaNaoDirecionada("v2", "v4", 5);
	grafo->inserirArestaNaoDirecionada("v3", "v4", 2);
	grafo->inserirArestaNaoDirecionada("v3", "v5", 4);
	grafo->inserirArestaNaoDirecionada("v4", "v6", 5);
	grafo->inserirArestaNaoDirecionada("v4", "v7", 5);
	grafo->inserirArestaNaoDirecionada("v5", "v9", 9);
	grafo->inserirArestaNaoDirecionada("v6", "v8", 6);
	grafo->inserirArestaNaoDirecionada("v8", "v9", 8);

	GrafoListaAdj* grafoMST = grafo->KruskalMST();

	int pesoArestas = somaArestasMST(grafoMST);
	//78 pois cada aresta não direcionada é 
	//representado por 2 arestas direcionadas
	EXPECT_EQ(pesoArestas, 78);
}

TEST_F(MSTTest, Grafo2) {
	inserirVertices(grafo, 1, 10);
	
	//Grafo: https://www.youtube.com/watch?v=JZBQLXgSGfs&t
	grafo->inserirArestaNaoDirecionada("v1", "v2", 5);
	grafo->inserirArestaNaoDirecionada("v1", "v4", 4);
	grafo->inserirArestaNaoDirecionada("v1", "v5", 1);
	grafo->inserirArestaNaoDirecionada("v2", "v3", 4);
	grafo->inserirArestaNaoDirecionada("v2", "v4", 2);
	grafo->inserirArestaNaoDirecionada("v3", "v8", 4);
	grafo->inserirArestaNaoDirecionada("v3", "v9", 1);
	grafo->inserirArestaNaoDirecionada("v3", "v10", 2);
	grafo->inserirArestaNaoDirecionada("v4", "v5", 2);
	grafo->inserirArestaNaoDirecionada("v4", "v6", 5);
	grafo->inserirArestaNaoDirecionada("v4", "v7", 11);
	grafo->inserirArestaNaoDirecionada("v4", "v8", 2);
	grafo->inserirArestaNaoDirecionada("v5", "v6", 1);
	grafo->inserirArestaNaoDirecionada("v6", "v7", 7);
	grafo->inserirArestaNaoDirecionada("v7", "v8", 1);
	grafo->inserirArestaNaoDirecionada("v7", "v9", 4);
	grafo->inserirArestaNaoDirecionada("v8", "v9", 6);
	grafo->inserirArestaNaoDirecionada("v9", "v10", 0);

	GrafoListaAdj* grafoMST = grafo->KruskalMST();

	int pesoArestas = somaArestasMST(grafoMST);
	//28 pois cada aresta não direcionada é 
	//representado por 2 arestas direcionadas
	EXPECT_EQ(pesoArestas, 28);
}