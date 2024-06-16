//
// Danilo Alexandre Pereira 08/06/2024
//

#ifndef PRATICA_RUBRO_NEGRA
#define PRATICA_RUBRO_NEGRA
typedef struct no no;

typedef struct arvore arv;

arv *criaArvoreRubro();
int processaCargaRubro(arv *arv, char *nomeArquivo, int tipo);
int insereRubro(arv *arv, int valor);
int removeRubro(arv *arv, int valor);
int BuscaRubro(arv *arv, int valor);
void buscaElementosEmArquivoRubro(arv *arv, char *nomeArquivo);
void balanceamentoInsercaoRubro(arv *arv, no *noDesbal);
void balanceamentoRemocaoRubro(arv *arv, no *noDesbal);
void rotacaoDirRubro(arv *arv, no *noDesbal);
void rotacaoEsqRubro(arv *arv, no *noDesbal);
int getNumElementosRubro(arv *arv);
no *getRaizRubro(arv *arv);
void imprimePreOrdemRubro(arv *arv, no *raiz);
void imprimeOrdemRubro(arv *arv, no *raiz);
void imprimeArvoreRubro(arv *arv); //

#endif // PRATICA_RUBRO_NEGRA