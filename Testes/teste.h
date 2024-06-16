//
// Danilo Alexandre Pereira 08/06/2024
//

#include <time.h>

#ifndef PRATICA_RUBRO_NEGRA_VETORES
#define PRATICA_RUBRO_NEGRA_VETORES

typedef struct no no;
typedef struct arvore arv;
typedef struct avl avl;

// Função para escolher e executar operações em AVL ou Rubro-Negra
int opcao();

// Gera um arquivo com 10.000 elementos ordenados
void elementos10000(char *nomeArquivo);

// Seleciona 1.000 elementos aleatórios de um arquivo de
// entrada e salva em um arquivo de saída
void selecionar1000Elementos(char *inputFile, char *outputFile);

// Embaralha os elementos de um array
void shuffle(int *array, int n);

// Calcula a diferença de tempo entre dois instantes
double timediff(clock_t, clock_t);

// Funções para imprimir tabelas de inserção, remoção e busca em AVL
void tabelaInsercaoAVL(float tempoAVLIN, long int rotacoesAVLIN);
void tabelaRemocaoAVL(float tempoAVLRE, long int rotacoesAVLRE);
void tabelaBuscaAVL(float tempoAVLBU);

// Funções para imprimir tabelas de inserção, remoção e busca em Rubro-Negra
void tabelaInsercaoRubro(float tempoRBIN, long int rotacoesRBIN);
void tabelaRemocaoRubro(float tempoRBRE, long int rotacoesRBRE);
void tabelaBuscaRubro(float tempoRBBU);

#endif // PRATICA_RUBRO_NEGRA_VETORES