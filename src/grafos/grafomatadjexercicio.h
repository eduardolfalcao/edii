#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

struct GrafoMatrizAdj{
    int** arestas;
    char** rotuloVertices;
    int verticesInseridos;
};

/**
 * Se o grafo for ponderado, inicializamos cada posicao da matriz com INT_MAX.
 * Se o grafo for não ponderado, inicializamos cada posicao da matriz com 0.
 **/
struct GrafoMatrizAdj* inicializar(int numVertices, bool ponderado){
}

/**
 * A principio nao temos nenhuma ordenacao usando os rotulos. 
 * Portanto, usaremos busca linear
 **/ 
int obterIndiceVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice){
}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da aresta.
 * Se o grafo for não ponderado, usamos a variavel peso para especificar a existência (0 ou 1) da aresta.
 * Se um dos rotulos dos vertices nao existir, simplesmente nao faremos nada.
 **/ 
void inserirAresta(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino, int peso){
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de vertices que ja foi inserido no grafo.
 * Logo, ela pode/deve ser usada para especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice){
}

/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois vertices em um grafo ponderado,
 * e haver conexão entre dois vertices em um grafo nao-ponderado.
 **/
bool saoConectados(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino){
}

/**
 * Se o grafo for ponderado, deve retornar a soma dos pesos do menor caminho.
 * Se o grafo for não-ponderado, deve retornar a menor quantidade de arestas que liga os 2 vertices.
 **/ 
int menorCaminho(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino){    
}