//
// Created by Danilo on 08/06/2023.
//

#ifndef INC_7_AVL_AVL_H
#define INC_7_AVL_AVL_H

typedef struct no no;
typedef struct avl avl;

avl *criaArvoreAVL();
int insereNoAVL(avl *arv, int valor);
int removeNoAVL(avl *arv, int valor);
void imprimeOrdemAVL(no *raiz);
void imprimePreOrdemAVL(no *raiz);
int BuscaAVL(avl *arv, int valor);
void buscaElementosEmArquivoAVL(avl *arv, char *nomeArquivo);
no *getRaizAVL(avl *arv);
int getNumElementosAVL(avl *arv);
int processaCargaAVL(avl *arv, char *nomeArquivo, int tipo);
void atualizaFB_insercaoAVL(avl *arv, no *novoNo);
void balanceamentoAVL(avl *arv, no *noDesbal);
void rotacaoDirAVL(no *noDesbal);
void rotacaoEsqAVL(no *noDesbal);
void atualizaFB_remocaoAVL(avl *arv, no *pai, int chaveRemovida);

#endif // INC_7_AVL_AVL_H
