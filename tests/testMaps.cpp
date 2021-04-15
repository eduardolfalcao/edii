#include "pch.h"
#include <unordered_map>
#include <map>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;

class CppMapsTest : public ::testing::Test {
protected:
	virtual void TearDown() {
		estoqueSupermercadoDesordenado.clear();
		estoqueSupermercadoOrdenado.clear();
		estoqueSupermercadoDesordenadoMulti.clear();
	}

	virtual void SetUp() {
		cout << "Bucket count antes da insercao: " << estoqueSupermercadoDesordenado.bucket_count() << endl;
		cout << "Numero de elemntos antes da insercao: " << estoqueSupermercadoDesordenado.size() << endl;
		cout << "load_factor antes: " << estoqueSupermercadoDesordenado.load_factor() << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 1; j <= QTDADE_POR_ITEM; j++) {
				estoqueSupermercadoDesordenado[itens[i] + to_string(j)] = 500;
				estoqueSupermercadoOrdenado[itens[i] + to_string(j)] = 500;
				estoqueSupermercadoDesordenadoMulti.insert(make_pair<std::string, int>(itens[i] + to_string(j), 500));
			}		
		}
		cout << "Bucket count depois da insercao: " << estoqueSupermercadoDesordenado.bucket_count() << endl;
		cout << "Numero de elemntos depois da insercao: " << estoqueSupermercadoDesordenado.size() << endl;
		cout << "load_factor depois: " << estoqueSupermercadoDesordenado.load_factor() << endl;
	}

	const int QTDADE_POR_ITEM = 100000;
	string itens[5] = { "cebola", "feijao", "tomate", "arroz", "macarrao" };

	//cebola1, 500
	//...
	//cebola1000, 500
	//feijao1, 500
	//...
	//feijao1000, 500
	//tomate1, 500
	//...
	//tomate1000, 500
	//arroz1, 500
	//...
	//arroz1000, 500
	//macarrao1, 500
	//...
	//macarrao1000, 500
	
	unordered_map<string, int> estoqueSupermercadoDesordenado;
	//implementado com tabela hash, nao mantem ordem, O(1)

	map<string, int> estoqueSupermercadoOrdenado;
	//implementado com arvores rubro-negras, mantem ordem de insercao, O(lg(n))

	unordered_multimap<string, int> estoqueSupermercadoDesordenadoMulti;
};

TEST_F(CppMapsTest, HaItemMapDesordenado) {
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= QTDADE_POR_ITEM; j++)
			EXPECT_TRUE(estoqueSupermercadoDesordenado.find(itens[i] + to_string(j)) != estoqueSupermercadoDesordenado.end());
		//complexidade do find: O(1)
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Duracao: " << duration.count() << endl;
}

TEST_F(CppMapsTest, HaItemMapOrdenado) {
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= QTDADE_POR_ITEM; j++)
			EXPECT_TRUE(estoqueSupermercadoOrdenado.find(itens[i] + to_string(j)) != estoqueSupermercadoOrdenado.end());
			//complexidade do find: O(lg(n))
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Duracao: " << duration.count() << endl;
}

TEST_F(CppMapsTest, InsercaoDeItemExistente) {
	EXPECT_EQ(estoqueSupermercadoDesordenado["cebola1"], 500);
	estoqueSupermercadoDesordenado["cebola1"] = 123;
	//o valor já existente é substituído
	EXPECT_EQ(estoqueSupermercadoDesordenado["cebola1"], 123);

	EXPECT_EQ(estoqueSupermercadoOrdenado["cebola1"], 500);
	estoqueSupermercadoOrdenado["cebola1"] = 123;
	//o valor já existente é substituído
	EXPECT_EQ(estoqueSupermercadoOrdenado["cebola1"], 123);

	estoqueSupermercadoDesordenadoMulti.insert(make_pair<string, int>("cebola1", 123));
	unordered_multimap<string, int>::iterator itr;
	itr = estoqueSupermercadoDesordenadoMulti.find("cebola1");
	EXPECT_EQ(itr->second, 500);
	itr++;
	EXPECT_EQ(itr->second, 123);
}

TEST_F(CppMapsTest, CalculandoOBucket) {	
	unsigned nBuckets = estoqueSupermercadoDesordenado.bucket_count();
	cout << "estoqueSupermercadoDesordenado tem " << nBuckets << " buckets.\n";
	for (unsigned bucket = 0; bucket < nBuckets; ++bucket) {
		cout << "bucket #" << bucket << " contains: ";
		for (auto it = estoqueSupermercadoDesordenado.begin(bucket); it != estoqueSupermercadoDesordenado.end(bucket); ++it) {
			cout << "[" << it->first << ":" << it->second << "; keyHash: " << hash<string>{}(it->first) << "]";
			EXPECT_EQ(hash<string>{}(it->first)%nBuckets, bucket);
		}
		cout << endl;
	}
}

TEST_F(CppMapsTest, VerificandoOrdenacao) {

	unordered_map<string, int>::iterator itrUnorderedMap;
	for (itrUnorderedMap = estoqueSupermercadoDesordenado.begin(); itrUnorderedMap != estoqueSupermercadoDesordenado.end(); itrUnorderedMap++)
		cout << itrUnorderedMap->first << "  " << itrUnorderedMap->second << endl;

	map<string, int>::iterator itrMap;
	for (itrMap = estoqueSupermercadoOrdenado.begin(); itrMap != estoqueSupermercadoOrdenado.end(); itrMap++)
		cout << itrMap->first << "  " << itrMap->second << endl;
	
}