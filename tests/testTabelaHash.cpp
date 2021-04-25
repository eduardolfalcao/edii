#include "pch.h"
#include "../src/tabelas-hash/TabelaHash.h"
#include <algorithm>
#include <chrono>
using namespace std::chrono;
using namespace std;

class TabelaHashTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		estoqueSupermercadoTabelaHash.clear();
	}

	string itens[5] = { "cebola", "feijao", "tomate", "arroz", "macarrao" };
	TabelaHash<string, int> estoqueSupermercadoTabelaHash;
};

//& para forçar a passagem do objeto por referência
void criarTabela(TabelaHash<string, int>& tabela, int qtdadeRepeticoes, string itens[]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			tabela.inserir(itens[i] + to_string(j), 500);
		}
	}
}

TEST_F(TabelaHashTest, AdicionarEmTabelaVazia) {
	criarTabela(estoqueSupermercadoTabelaHash,1,itens);
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("cebola1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("tomate1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("feijao1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("arroz1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("macarrao1"));
	EXPECT_EQ(estoqueSupermercadoTabelaHash.size(), 5);
	EXPECT_EQ(estoqueSupermercadoTabelaHash.bucket_count(), 8);
}

TEST_F(TabelaHashTest, ForcarAumentoDeTabela) {
	int qtdadeRepeticoes = 2;
	criarTabela(estoqueSupermercadoTabelaHash,qtdadeRepeticoes,itens);
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave(itens[i] + to_string(j)));
		}
	}
	EXPECT_EQ(estoqueSupermercadoTabelaHash.size(), 10);
	//tamanho inicial do array é 8, e cada vez que precisamos aumentar
	//ele multiplica por 8
	EXPECT_EQ(estoqueSupermercadoTabelaHash.bucket_count(), 64);	
}

TEST_F(TabelaHashTest, ForcarAumentoDeTabelaMultiplasVezes) {
	int qtdadeRepeticoes = 1000;
	criarTabela(estoqueSupermercadoTabelaHash,qtdadeRepeticoes,itens);
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave(itens[i] + to_string(j)));
		}
	}
	EXPECT_EQ(estoqueSupermercadoTabelaHash.size(), 5*qtdadeRepeticoes);
	//tamanho inicial do array é 8, e cada vez que precisamos aumentar
	//ele multiplica por 8
	EXPECT_EQ(estoqueSupermercadoTabelaHash.bucket_count(), 32768);
}

TEST_F(TabelaHashTest, LoadFactorEmTabelaPequena) {
	criarTabela(estoqueSupermercadoTabelaHash,1,itens);
	EXPECT_EQ(estoqueSupermercadoTabelaHash.load_factor(), 5.0/8.0);
}

TEST_F(TabelaHashTest, LoadFactorEmTabelaGrande) {
	criarTabela(estoqueSupermercadoTabelaHash,1000,itens);
	EXPECT_EQ(estoqueSupermercadoTabelaHash.load_factor(), 5000.0 / 32768.0);
}

TEST_F(TabelaHashTest, GetValor) {
	criarTabela(estoqueSupermercadoTabelaHash, 1000, itens);
	EXPECT_EQ(estoqueSupermercadoTabelaHash.getValor("cebola1000"), 500);
	EXPECT_EQ(estoqueSupermercadoTabelaHash.getValor("cebola1001"), NULL);
}

TEST_F(TabelaHashTest, ContemChave) {
	criarTabela(estoqueSupermercadoTabelaHash, 1000, itens);
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("cebola1000"));
	EXPECT_FALSE(estoqueSupermercadoTabelaHash.contemChave("cebola1001"));
}

TEST_F(TabelaHashTest, GetChaves) {
	int qtdadeRepeticoes = 1000;
	criarTabela(estoqueSupermercadoTabelaHash, qtdadeRepeticoes, itens);	
	vector<string> chaves = estoqueSupermercadoTabelaHash.getChaves();
	EXPECT_EQ(chaves.size(),5000);
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			EXPECT_TRUE(count(chaves.begin(), chaves.end(), itens[i] + to_string(j)));
		}
	}	
}

TEST_F(TabelaHashTest, RemoverTuplaEmTabelaPequena) {
	criarTabela(estoqueSupermercadoTabelaHash, 1, itens);
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("cebola1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("tomate1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("feijao1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("arroz1"));
	EXPECT_TRUE(estoqueSupermercadoTabelaHash.contemChave("macarrao1"));
	EXPECT_EQ(estoqueSupermercadoTabelaHash.size(), 5);

	estoqueSupermercadoTabelaHash.remover("tomate1");
	EXPECT_EQ(estoqueSupermercadoTabelaHash.size(), 4);
	vector<string> chaves = estoqueSupermercadoTabelaHash.getChaves();
	EXPECT_FALSE(count(chaves.begin(), chaves.end(), "tomate1"));

	estoqueSupermercadoTabelaHash.remover("arroz1");
	EXPECT_EQ(estoqueSupermercadoTabelaHash.size(), 3);
	chaves = estoqueSupermercadoTabelaHash.getChaves();
	EXPECT_FALSE(count(chaves.begin(), chaves.end(), "arroz1"));
}

TEST_F(TabelaHashTest, RemoverTodasAsTuplasEmTabelaGrande) {
	int qtdadeRepeticoes = 1000;
	criarTabela(estoqueSupermercadoTabelaHash, qtdadeRepeticoes, itens);

	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			estoqueSupermercadoTabelaHash.remover(itens[i] + to_string(j));
		}
	}

	vector<string> chaves = estoqueSupermercadoTabelaHash.getChaves();
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= qtdadeRepeticoes; j++) {
			EXPECT_FALSE(count(chaves.begin(), chaves.end(), itens[i] + to_string(j)));
		}
	}
	EXPECT_EQ(estoqueSupermercadoTabelaHash.size(), 0);
}