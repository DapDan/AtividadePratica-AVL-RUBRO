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

avl *criaArvoreAVL() {
  avl *a;
  a = (avl *)malloc(sizeof(avl));

  if (!a) {
    exit(1);
  }

  a->sentinela = (no *)malloc(sizeof(no));

  if (!a->sentinela) {
    exit(1);
  }

  a->sentinela->Fdir = NULL;
  a->sentinela->Fesq = NULL;
  a->sentinela->chave = -1000;
  a->sentinela->pai = NULL;
  a->sentinela->fb = 0;

  a->numElementos = 0;

  return a;
}

int insereNoAVL(avl *arv, int valor, long int *rotacoesAVLIN) {
  no *novo, *pai, *aux;

  novo = (no *)malloc(sizeof(no));
  if (!novo)
    return 0;

  novo->Fdir = NULL;
  novo->Fesq = NULL;
  novo->chave = valor;
  novo->pai = NULL;
  novo->fb = 0;

  aux = arv->sentinela->Fdir;
  novo->pai = arv->sentinela;

  while (aux) {
    novo->pai = aux;
    if (aux->chave > valor) {
      aux = aux->Fesq;
    } else {
      aux = aux->Fdir;
    }
  }

  if (valor < novo->pai->chave) {
    novo->pai->Fesq = novo;
  } else {
    novo->pai->Fdir = novo;
  }

  if (novo->pai == arv->sentinela) {
    arv->sentinela->Fdir = novo;
  }

  arv->numElementos++;
  if (novo != arv->sentinela->Fdir) {
    atualizaFB_insercaoAVL(arv, novo, rotacoesAVLIN);
  }
  return 1;
}

int removeNoAVL(avl *arv, int valor, long int *rotacoesAVLRE) {
  if (arv->sentinela->Fdir == NULL)
    return 0;

  no *atual = arv->sentinela->Fdir;

  while (atual != NULL && atual->chave != valor) {
    if (valor < atual->chave)
      atual = atual->Fesq;
    else
      atual = atual->Fdir;
  }

  if (atual == NULL)
    return -1;

  arv->numElementos--;
  if (atual->Fesq == NULL) {
    if (atual->Fdir != NULL)
      atual->Fdir->pai = atual->pai;
    if (atual->pai->chave == -1000)
      arv->sentinela->Fdir = atual->Fdir;
    else if (atual == atual->pai->Fesq)
      atual->pai->Fesq = atual->Fdir;
    else
      atual->pai->Fdir = atual->Fdir;
  } else if (atual->Fdir == NULL) {
    if (atual->Fesq != NULL)
      atual->Fesq->pai = atual->pai;
    if (atual->pai->chave == -1000)
      arv->sentinela->Fdir = atual->Fesq;
    else if (atual == atual->pai->Fesq)
      atual->pai->Fesq = atual->Fesq;
    else
      atual->pai->Fdir = atual->Fesq;
  } else {
    no *sucessor = atual->Fdir;
    while (sucessor->Fesq != NULL)
      sucessor = sucessor->Fesq;
    atual->chave = sucessor->chave;
    if (sucessor == sucessor->pai->Fesq)
      sucessor->pai->Fesq = sucessor->Fdir;
    else
      sucessor->pai->Fdir = sucessor->Fdir;
    if (sucessor->Fdir != NULL)
      sucessor->Fdir->pai = sucessor->pai;

    atualizaFB_remocaoAVL(arv, sucessor->pai, sucessor->chave, rotacoesAVLRE);
    free(sucessor);
    return 1;
  }

  atualizaFB_remocaoAVL(arv, atual->pai, atual->chave, rotacoesAVLRE);
  free(atual);
  return 1;
}

void imprimeOrdemAVL(no *raiz) {
  if (raiz != NULL) {
    imprimeOrdemAVL(raiz->Fesq);
    printf("\t%d - \t%d - \t%d\n", raiz->chave, raiz->pai->chave, raiz->fb);
    imprimeOrdemAVL(raiz->Fdir);
  }
}
void imprimePreOrdemAVL(no *raiz) {
  if (raiz != NULL) {
    printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
    imprimeOrdemAVL(raiz->Fesq);
    imprimeOrdemAVL(raiz->Fdir);
  }
}

int BuscaAVL(avl *arv, int valor) {
  no *atual = arv->sentinela->Fdir;
  while (atual != NULL) {
    if (valor == atual->chave)
      return 1; // Encontrado
    else if (valor < atual->chave)
      atual = atual->Fesq;
    else
      atual = atual->Fdir;
  }
  return 0; // Não encontrado
}

void buscaElementosEmArquivoAVL(avl *arv, char *nomeArquivo) {
  FILE *arquivo;
  int valor, flag;

  flag = 0;
  arquivo = fopen(nomeArquivo, "r");
  if (!arquivo) {
    perror("Erro ao abrir o arquivo de busca");
    return;
  }

  while (fscanf(arquivo, "%d", &valor) != EOF) {
    if (BuscaAVL(arv, valor)) {
      // printf("Elemento %d encontrado na árvore AVL.\n", valor);
      flag++;
    } else {
      // printf("Elemento %d não encontrado na árvore AVL.\n", valor);
      flag--;
    }
  }

  if (flag == 1000)
    printf("Todos os elementos foram encontrados!");
  else
    printf("Quase todos os elementos foram encontrados!");
  fclose(arquivo);
}

no *getRaizAVL(avl *arv) { return arv->sentinela->Fdir; }

int getNumElementosAVL(avl *arv) { return arv->numElementos; }

int processaCargaAVL(avl *arv, char *nomeArquivo, int tipo,
                     long int *rotacoesAVLIN, long int *rotacoesAVLRE) {
  FILE *arquivo;
  int valor, res;

  arquivo = fopen(nomeArquivo, "r");
  if (!arquivo)
    return -2;

  if (tipo == 1) {
    while (fscanf(arquivo, "%d", &valor) != EOF) {
      res = insereNoAVL(arv, valor, rotacoesAVLIN);
      if (res != 1)
        return 0;
    }
  } else {
    while (fscanf(arquivo, "%d", &valor) != EOF) {
      res = removeNoAVL(arv, valor, rotacoesAVLRE);
      if (res != 1)
        return 0;
    }
  }

  fclose(arquivo);
  return 1;
}

void atualizaFB_insercaoAVL(avl *arv, no *novoNo, long int *rotacoesAVLIN) {
  no *aux = novoNo->pai;

  while (aux != NULL && aux->chave != -1000) {
    if (novoNo == aux->Fesq) {
      aux->fb--;
    } else {
      aux->fb++;
    }

    if (aux->fb == 0) {
      break;
    }

    if (aux->fb == 2 || aux->fb == -2) {
      balanceamentoAVL(arv, aux, rotacoesAVLIN, NULL);
      break;
    }

    novoNo = aux;
    aux = aux->pai;
  }
}

void balanceamentoAVL(avl *arv, no *noDesbal, long int *rotacoesAVLIN,
                      long int *rotacoesAVLRE) {
  no *filho;

  if (noDesbal->fb == 2) {
    filho = noDesbal->Fdir;
    if (filho->fb == -1) {
      // Rotação dupla
      int FBneto = filho->Fesq->fb;

      rotacaoDirAVL(filho);
      rotacaoEsqAVL(noDesbal);

      // Atualizando contador rotacoes
      if (rotacoesAVLIN != NULL) {

        *rotacoesAVLIN += 2;
      }
      // Atualizando contador rotacoes
      if (rotacoesAVLRE != NULL) {

        *rotacoesAVLRE += 2;
      }

      // Atualizando os fatores de balanceamento
      if (FBneto == 1) {
        noDesbal->fb = -1;
        filho->fb = 0;
        noDesbal->pai->fb = 0;
      } else if (FBneto == 0) {
        noDesbal->fb = 0;
        filho->fb = 0;
        noDesbal->pai->fb = 0;
      } else { // FBneto == -1
        noDesbal->fb = 0;
        filho->fb = 1;
        noDesbal->pai->fb = 0;
      }
    } else {
      // Rotação simples
      int FBfilho = filho->fb;
      rotacaoEsqAVL(noDesbal);

      if (rotacoesAVLIN != NULL) {

        *rotacoesAVLIN += 1;
      }

      if (rotacoesAVLRE != NULL) {

        *rotacoesAVLRE += 1;
      }

      // Atualizando os fatores de balanceamento
      if (FBfilho == 0) {
        noDesbal->fb = 1;
        filho->fb = -1;
      } else {
        noDesbal->fb = 0;
        filho->fb = 0;
      }
    }
  } else if (noDesbal->fb == -2) {
    filho = noDesbal->Fesq;
    if (filho->fb == 1) {
      // Rotação dupla
      int FBneto = filho->Fdir->fb;

      rotacaoEsqAVL(filho);
      rotacaoDirAVL(noDesbal);

      // Atualizando contador rotacoes
      if (rotacoesAVLIN != NULL) {

        *rotacoesAVLIN += 2;
      }
      // Atualizando contador rotacoes
      if (rotacoesAVLRE != NULL) {

        *rotacoesAVLRE += 2;
      }

      // Atualizando fatores de balanceamento
      if (FBneto == -1) {
        noDesbal->fb = 1;
        filho->fb = 0;
        noDesbal->pai->fb = 0;
      } else if (FBneto == 0) {
        noDesbal->fb = 0;
        filho->fb = 0;
        noDesbal->pai->fb = 0;
      } else { // FBneto == 1
        noDesbal->fb = 0;
        filho->fb = -1;
        noDesbal->pai->fb = 0;
      }
    } else {
      // Rotação simples
      int FBfilho = filho->fb;
      rotacaoDirAVL(noDesbal);

      if (rotacoesAVLIN != NULL) {

        *rotacoesAVLIN += 1;
      }

      if (rotacoesAVLRE != NULL) {

        *rotacoesAVLRE += 1;
      }

      // Atualizando os fatores de balanceamento
      if (FBfilho == 0) {
        noDesbal->fb = -1;
        filho->fb = 1;
      } else {
        noDesbal->fb = 0;
        filho->fb = 0;
      }
    }
  }
}

void rotacaoDirAVL(no *noDesbal) {
  no *x = noDesbal->Fesq;
  noDesbal->Fesq = x->Fdir;
  if (x->Fdir != NULL) {
    x->Fdir->pai = noDesbal;
  }
  x->pai = noDesbal->pai;
  if (noDesbal == noDesbal->pai->Fdir) {
    noDesbal->pai->Fdir = x;
  } else {
    noDesbal->pai->Fesq = x;
  }
  x->Fdir = noDesbal;
  noDesbal->pai = x;
}

void rotacaoEsqAVL(no *noDesbal) {
  no *y = noDesbal->Fdir;
  noDesbal->Fdir = y->Fesq;
  if (y->Fesq != NULL) {
    y->Fesq->pai = noDesbal;
  }
  y->pai = noDesbal->pai;
  if (noDesbal == noDesbal->pai->Fesq) {
    noDesbal->pai->Fesq = y;
  } else {
    noDesbal->pai->Fdir = y;
  }
  y->Fesq = noDesbal;
  noDesbal->pai = y;
}

void atualizaFB_remocaoAVL(avl *arv, no *pai, int chaveRemovida,
                           long int *rotacoesAVLRE) {
  while (pai != NULL && pai->chave != -1000) {
    if (pai->Fesq != NULL && chaveRemovida == pai->Fesq->chave)
      pai->fb--;
    else if (pai->Fdir != NULL && chaveRemovida == pai->Fdir->chave)
      pai->fb++;

    if (pai->fb == 2 || pai->fb == -2) {
      balanceamentoAVL(arv, pai, NULL, rotacoesAVLRE);
      if (pai->pai != arv->sentinela &&
          (pai->fb == 0 || pai->fb == 2 || pai->fb == -2)) {
        chaveRemovida = pai->chave;
        pai = pai->pai;
        continue;
      }
    } else if (pai->fb == 0) {
      break;
    }

    chaveRemovida = pai->chave;
    pai = pai->pai;
  }
}