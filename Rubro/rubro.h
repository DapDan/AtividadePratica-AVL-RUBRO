//
// Danilo Alexandre Pereira 08/06/2024
//

#ifndef PRATICA_RUBRO_NEGRA
#define PRATICA_RUBRO_NEGRA
typedef struct no no;

typedef struct arvore arv;

// Função para criar uma nova árvore Rubro-Negra
arv *criaArvoreRubro();

// Função para processar a carga de elementos na árvore a partir de um arquivo
int processaCargaRubro(arv *arv, char *nomeArquivo, int tipo,
                       long int *rotacoesRBIN, long int *rotacoesRBRE);

// Função para inserir um novo nó na árvore Rubro-Negra
int insereRubro(arv *arv, int valor, long int *rotacoesRBIN);

// Função para remover um nó da árvore Rubro-Negra
int removeRubro(arv *arv, int valor, long int *rotacoesRBRE);

// Função para buscar um valor na árvore Rubro-Negra
int BuscaRubro(arv *arv, int valor);

// Função para buscar elementos em um arquivo e verificar sua presença na árvore
void buscaElementosEmArquivoRubro(arv *arv, char *nomeArquivo);

// Função para balancear a árvore após a inserção de um nó
void balanceamentoInsercaoRubro(arv *arv, no *noDesbal, long int *rotacoesRBIN);

// Função para balancear a árvore após a remoção de um nó
void balanceamentoRemocaoRubro(arv *arv, no *noDesbal, long int *rotacoesRBRE);

// Função para realizar rotação à esquerda
void rotacaoDirRubro(arv *arv, no *noDesbal);

// Função para realizar rotação à direita
void rotacaoEsqRubro(arv *arv, no *noDesbal);

int getNumElementosRubro(arv *arv);
no *getRaizRubro(arv *arv);
void imprimePreOrdemRubro(arv *arv, no *raiz);
void imprimeOrdemRubro(arv *arv, no *raiz);
void imprimeArvoreRubro(arv *arv);

#endif // PRATICA_RUBRO_NEGRA