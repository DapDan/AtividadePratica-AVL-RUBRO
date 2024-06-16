#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int chave;
  struct no *Fesq;
  struct no *Fdir;
  struct no *pai;
  int fb;
} no;

typedef struct avl {
  struct no *sentinela;
  int numElementos;
} avl;

avl *criaArvore();
int insereNo(avl *arv, int valor);
int removeNo(avl *arv, int valor);
void imprimeOrdem(no *raiz);
void imprimePreOrdem(no *raiz);
no *getRaiz(avl *arv);
int getNumElementos(avl *arv);

void atualizaFB_insercao(avl *arv, no *novoNo);
void balanceamento(avl *arv, no *noDesbal);
void rotacaoDir(no *noDesbal);
void rotacaoEsq(no *noDesbal);
void atualizaFB_remocao(avl *arv, no *pai, int chaveRemovida);

avl *criaArvore() {
  avl *a = (avl *)malloc(sizeof(avl));

  if (!a) {
    exit(0);
  }

  a->numElementos = 0;
  a->sentinela = (no *)malloc(sizeof(no));

  if (!a->sentinela) {
    exit(0);
  }

  a->sentinela->chave = -1000;
  a->sentinela->fb = 0;
  a->sentinela->pai = NULL;
  a->sentinela->Fdir = NULL;
  a->sentinela->Fesq = NULL;

  return a;
}

// Função que insere um elemento na árvore
// Retorna 1 se a inserção foi realizada com sucesso
// Retorna 0 se não foi possível realizar a inserção
int insereNo(avl *arv, int valor) {
  no *novo, *pai, *aux;
  novo = (no *)malloc(sizeof(no));

  if (!novo) {
    return 0;
  }

  novo->Fdir = NULL;
  novo->Fesq = NULL;
  novo->pai = NULL;
  novo->fb = 0;
  novo->chave = valor;

  if (arv->sentinela->Fdir == NULL) {
    novo->pai = arv->sentinela;
    arv->sentinela->Fdir = novo;
  } else {
    aux = arv->sentinela->Fdir;
    while (aux != NULL) {
      pai = aux;
      if (valor < aux->chave)
        aux = aux->Fesq;
      else
        aux = aux->Fdir;
    }

    if (valor < pai->chave) {
      pai->Fesq = novo;
      novo->pai = pai;
    } else {
      pai->Fdir = novo;
      novo->pai = pai;
    }
  }

  arv->numElementos++;
  atualizaFB_insercao(arv, novo);
  return 1;
}

// Função que remove um elemento da árvore implementando a remoção por cópia
// usando o sucessor Retorna 1 se o elemento foi removido Retorna 0 se a árvore
// estiver vazia Retorna -1 caso o elemento a ser removido não esteja na árvore
int removeNo(avl *arv, int valor);

void imprimeOrdem(no *raiz) {
  if (raiz == NULL) {
    imprimeOrdem(raiz->Fesq);
    printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
    imprimeOrdem(raiz->Fdir);
  }
}

void imprimePreOrdem(no *raiz) {
  if (raiz == NULL) {
    printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
    imprimeOrdem(raiz->Fesq);
    imprimeOrdem(raiz->Fdir);
  }
}

no *getRaiz(avl *arv) { return arv->sentinela->Fdir; }

// Função que retorna a quantidade de elementos da árvore
int getNumElementos(avl *arv) { return arv->numElementos; }

// Função que verifica o desbalanceamento na inserção
void atualizaFB_insercao(avl *arv, no *novoNo) {
  no *aux;
  aux = novoNo;

  while ((aux->chave != arv->sentinela->chave) ||
         (aux->fb == 2 || aux->fb == -2 || aux->fb == 0)) {
    if (aux->chave < aux->pai->chave) {
      aux->pai->fb--;
      aux = aux->pai;
    } else {
      aux->pai->fb++;
      aux = aux->pai;
    }

    if (aux->fb == 2 || aux->fb == -2 || aux->fb == 0) {
      balanceamento(arv, aux);
    }
  }

  // Função que faz o balanceamento após inseção
  void balanceamento(avl * arv, no * noDesbal){
    
  }

  // Função que implementa a rotação à direita
  void rotacaoDir(no * noDesbal);

  // Função que implementa a rotação à esquerda
  void rotacaoEsq(no * noDesbal);

  // Função que verifica o desbalanceamento na remoção
  void atualizaFB_remocao(avl * arv, no * pai, int chaveRemovida);
