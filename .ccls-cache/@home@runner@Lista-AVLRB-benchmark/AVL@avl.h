//
// Created by Danilo on 08/06/2023.
//

#ifndef INC_7_AVL_AVL_H
#define INC_7_AVL_AVL_H

typedef struct no no;
typedef struct avl avl;

avl *criaArvoreAVL();
int insereNoAVL(avl *arv, int valor, long int *rotacoesAVLIN);
int removeNoAVL(avl *arv, int valor, long int *rotacoesAVLRE);
void imprimeOrdemAVL(no *raiz);
void imprimePreOrdemAVL(no *raiz);
int BuscaAVL(avl *arv, int valor); // fazer
void buscaElementosEmArquivoAVL(avl *arv, char *nomeArquivo);
no *getRaizAVL(avl *arv);
int getNumElementosAVL(avl *arv);
int processaCargaAVL(avl *arv, char *nomeArquivo, int tipo,
                     long int *rotacoesAVLIN, long int *rotacoesAVLRE);
void atualizaFB_insercaoAVL(avl *arv, no *novoNo, long int *rotacoesAVLIN);
void balanceamentoAVL(avl *arv, no *noDesbal, long int *rotacoesAVLIN,
                      long int *rotacoesAVLRE);
void rotacaoDirAVL(no *noDesbal);
void rotacaoEsqAVL(no *noDesbal);
void atualizaFB_remocaoAVL(avl *arv, no *pai, int chaveRemovida,
                           long int *rotacoesAVLRE);

#endif // INC_7_AVL_AVL_H
