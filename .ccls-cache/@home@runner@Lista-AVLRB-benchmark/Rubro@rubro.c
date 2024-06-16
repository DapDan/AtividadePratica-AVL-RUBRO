#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int chave;
  struct no *Fesq;
  struct no *Fdir;
  struct no *pai;
  char cor;
} no;

typedef struct arvore {
  struct no *sentinela;
  struct no *null;
  int numElementos;
} arv;

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

arv *criaArvoreRubro() {
  arv *a = (arv *)malloc(sizeof(arv));
  if (!a)
    return NULL;

  a->sentinela = (no *)malloc(sizeof(no));
  if (!a->sentinela)
    return NULL;

  a->sentinela->pai = NULL;
  a->sentinela->Fdir = NULL;
  a->sentinela->Fesq = NULL;
  a->sentinela->chave = -1000;
  a->sentinela->cor = 'P';

  a->numElementos = 0;
  a->null = NULL;

  return a;
}

int processaCargaRubro(arv *arv, char *nomeArquivo, int tipo,
                       long int *rotacoesRBIN, long int *rotacoesRBRE) {
  FILE *arquivo;
  int valor, res;

  arquivo = fopen(nomeArquivo, "r");
  if (!arquivo)
    return -2;

  if (tipo == 1) {
    while (fscanf(arquivo, "%d", &valor) != EOF) {
      res = insereRubro(arv, valor, rotacoesRBIN);
      if (res != 1)
        return 0;
    }
  } else {
    while (fscanf(arquivo, "%d", &valor) != EOF) {
      res = removeRubro(arv, valor, rotacoesRBRE);
      if (res != 1)
        return 0;
    }
  }

  fclose(arquivo);
  return 1;
}

int insereRubro(arv *arv, int valor, long int *rotacoesRBIN) {
  no *aux, *pai, *novo;

  novo = (no *)malloc(sizeof(no));
  if (!novo)
    return 0;

  novo->chave = valor;
  novo->Fdir = NULL;
  novo->Fesq = NULL;
  novo->pai = NULL;
  novo->cor = 'V'; // Novo nó sempre é vermelho inicialmente

  pai = arv->sentinela;
  aux = arv->sentinela->Fdir;

  // Encontrar a posição correta para inserir o novo nó
  while (aux != NULL && aux->chave != -1000) {
    pai = aux;
    if (aux->chave > valor) {
      aux = aux->Fesq;
    } else {
      aux = aux->Fdir;
    }
  }

  novo->pai = pai;

  // Inserir o novo nó na posição correta
  if (pai->chave == -1000) {
    arv->sentinela->Fdir = novo;
  } else if (valor < pai->chave) {
    pai->Fesq = novo;
  } else {
    pai->Fdir = novo;
  }

  arv->numElementos++;
  balanceamentoInsercaoRubro(arv, novo, rotacoesRBIN);

  // Após o balanceamento, garantir que a raiz seja preta
  arv->sentinela->Fdir->cor = 'P';

  return 1;
}

int removeRubro(arv *arv, int valor, long int *rotacoesRBRE) {
  char c;
  if (arv == NULL || arv->sentinela->Fdir == NULL)
    return 0;

  no *noRemover = arv->sentinela->Fdir;
  while (noRemover != NULL && noRemover->chave != valor) {
    if (valor < noRemover->chave)
      noRemover = noRemover->Fesq;
    else
      noRemover = noRemover->Fdir;
  }

  if (noRemover == NULL)
    return -1; // Valor não encontrado

  if (noRemover->Fesq != NULL && noRemover->Fdir != NULL) {
    no *sucessor = noRemover->Fdir;
    while (sucessor->Fesq != NULL)
      sucessor = sucessor->Fesq;

    noRemover->chave = sucessor->chave;
    noRemover = sucessor;
  }

  no *filho = NULL;
  if (noRemover->Fesq != NULL)
    filho = noRemover->Fesq;
  else
    filho = noRemover->Fdir;
  if (noRemover->cor == 'P') {
    if (filho == NULL) {
      noRemover->cor = 'P';
    } else {
      noRemover->cor = filho->cor;
    }
    balanceamentoRemocaoRubro(arv, noRemover, rotacoesRBRE);
  }

  if (noRemover->pai == NULL) {
    arv->sentinela->Fdir = filho;
    if (filho != NULL)
      filho->pai = NULL;
  } else {
    if (noRemover == noRemover->pai->Fesq)
      noRemover->pai->Fesq = filho;
    else
      noRemover->pai->Fdir = filho;

    if (filho != NULL)
      filho->pai = noRemover->pai;
  }

  free(noRemover);
  arv->numElementos--;
  return 1;
}

int BuscaRubro(arv *arv, int valor) {
  no *atual = arv->sentinela->Fdir;
  while (atual != NULL && atual->chave != -1000) {
    if (valor == atual->chave)
      return 1; // Encontrado
    else if (valor < atual->chave)
      atual = atual->Fesq;
    else
      atual = atual->Fdir;
  }
  return 0; // Não encontrado
}

void buscaElementosEmArquivoRubro(arv *arv, char *nomeArquivo) {
  FILE *arquivo;
  int valor, flag;

  flag = 0;
  arquivo = fopen(nomeArquivo, "r");
  if (!arquivo) {
    perror("Erro ao abrir o arquivo de busca");
    return;
  }

  while (fscanf(arquivo, "%d", &valor) != EOF) {
    if (BuscaRubro(arv, valor)) {
      // printf("Elemento %d encontrado na árvore Rubro-Negra.\n", valor);
      flag++;
    } else {
      // printf("Elemento %d não encontrado na árvore Rubro-Negra.\n", valor);
      flag--;
    }
  }

  if (flag == 1000)
    printf("Todos os elementos foram encontrados!\n");
  else
    printf("Quase todos os elementos foram encontrados!\n");

  fclose(arquivo);
}

// Função para balancear a árvore após a inserção de um nó
void balanceamentoInsercaoRubro(arv *arv, no *noDesbal,
                                long int *rotacoesRBIN) {
  no *tio;

  while (noDesbal->pai != NULL && noDesbal->pai->cor == 'V') {
    if (noDesbal->pai == noDesbal->pai->pai->Fesq) {
      tio = noDesbal->pai->pai->Fdir; // Tio do nó desbalanceado

      if (tio != NULL && tio->cor == 'V') { // Caso 1: Tio vermelho
        noDesbal->pai->cor = 'P';
        tio->cor = 'P';
        noDesbal->pai->pai->cor = 'V';
        noDesbal = noDesbal->pai->pai;
      } else {
        if (noDesbal ==
            noDesbal->pai
                ->Fdir) { // Caso 2: Tio preto e nó desbalanceado à direita
          noDesbal = noDesbal->pai;
          rotacaoEsqRubro(arv, noDesbal);

          // Atualiza contador
          if (rotacoesRBIN != NULL) {

            *rotacoesRBIN += 1;
          }
        }
        // Caso 3: Tio preto e nó desbalanceado à esquerda
        noDesbal->pai->cor = 'P';
        noDesbal->pai->pai->cor = 'V';
        rotacaoDirRubro(arv, noDesbal->pai->pai);

        // Atualiza contador
        if (rotacoesRBIN != NULL) {

          *rotacoesRBIN += 1;
        }
      }
    } else {                          // Espelhamento para o lado direito
      tio = noDesbal->pai->pai->Fesq; // Tio do nó desbalanceado

      if (tio != NULL && tio->cor == 'V') { // Caso 1: Tio vermelho
        noDesbal->pai->cor = 'P';
        tio->cor = 'P';
        noDesbal->pai->pai->cor = 'V';
        noDesbal = noDesbal->pai->pai;
      } else {
        if (noDesbal ==
            noDesbal->pai
                ->Fesq) { // Caso 2: Tio preto e nó desbalanceado à esquerda
          noDesbal = noDesbal->pai;
          rotacaoDirRubro(arv, noDesbal);

          // Atualiza contador
          if (rotacoesRBIN != NULL) {

            *rotacoesRBIN += 1;
          }
        }
        // Caso 3: Tio preto e nó desbalanceado à direita
        noDesbal->pai->cor = 'P';
        noDesbal->pai->pai->cor = 'V';
        rotacaoEsqRubro(arv, noDesbal->pai->pai);

        // Atualiza contador
        if (rotacoesRBIN != NULL) {

          *rotacoesRBIN += 1;
        }
      }
    }
  }

  // Garantir que a raiz seja preta após o balanceamento
  arv->sentinela->Fdir->cor = 'P';
}

void balanceamentoRemocaoRubro(arv *arv, no *noDesbal, long int *rotacoesRBRE) {
  no *irmao;
  while (noDesbal != arv->sentinela->Fdir && noDesbal->cor == 'P') {
    if (noDesbal == noDesbal->pai->Fesq) {
      irmao = noDesbal->pai->Fdir;
      if (irmao != NULL && irmao->cor == 'V') { // Caso 1: Irmão vermelho
        irmao->cor = 'P';
        noDesbal->pai->cor = 'V';
        rotacaoEsqRubro(arv, noDesbal->pai);
        irmao = noDesbal->pai->Fdir;

        // Atualizar contador
        if (rotacoesRBRE != NULL) {

          *rotacoesRBRE += 1;
        }
      }
      // Caso 2: Ambos filhos de irmão pretos
      if (irmao != NULL && (irmao->Fesq == NULL || irmao->Fesq->cor == 'P') &&
          (irmao->Fdir == NULL || irmao->Fdir->cor == 'P')) {
        irmao->cor = 'V';
        noDesbal = noDesbal->pai;
      } else {
        // Caso 3: Filho direito do irmão preto
        if (irmao != NULL && irmao->Fdir != NULL && irmao->Fdir->cor == 'P') {
          if (irmao->Fesq != NULL)
            irmao->Fesq->cor = 'P';
          irmao->cor = 'V';
          rotacaoDirRubro(arv, irmao);
          irmao = noDesbal->pai->Fdir;

          // Atualizar contador
          if (rotacoesRBRE != NULL) {

            *rotacoesRBRE += 1;
          }
        }
        // Caso 4: Filho direito do irmão vermelho
        if (irmao != NULL) {
          irmao->cor = noDesbal->pai->cor;
          noDesbal->pai->cor = 'P';
          if (irmao->Fdir != NULL)
            irmao->Fdir->cor = 'P';
          rotacaoEsqRubro(arv, noDesbal->pai);

          // Atualizar contador
          if (rotacoesRBRE != NULL) {

            *rotacoesRBRE += 1;
          }
        }
        noDesbal = arv->sentinela->Fdir;
      }
    } else {
      irmao = noDesbal->pai->Fesq;

      // Caso 1: Irmão vermelho
      if (irmao != NULL && irmao->cor == 'V') {
        irmao->cor = 'P';
        noDesbal->pai->cor = 'V';
        rotacaoDirRubro(arv, noDesbal->pai);
        irmao = noDesbal->pai->Fesq;

        // Atualizar contador
        if (rotacoesRBRE != NULL) {

          *rotacoesRBRE += 1;
        }
      }

      // Caso 2: Ambos filhos de irmão pretos
      if (irmao != NULL && (irmao->Fesq == NULL || irmao->Fesq->cor == 'P') &&
          (irmao->Fdir == NULL || irmao->Fdir->cor == 'P')) {
        irmao->cor = 'V';
        noDesbal = noDesbal->pai;
      } else {

        // Caso 3: Filho esquerdo do irmão preto
        if (irmao != NULL && irmao->Fesq != NULL && irmao->Fesq->cor == 'P') {
          if (irmao->Fdir != NULL)
            irmao->Fdir->cor = 'P';
          irmao->cor = 'V';
          rotacaoEsqRubro(arv, irmao);
          irmao = noDesbal->pai->Fesq;

          // Atualizar contador
          if (rotacoesRBRE != NULL) {

            *rotacoesRBRE += 1;
          }
        }

        // Caso 4: Filho esquerdo do irmão vermelho
        if (irmao != NULL) {
          irmao->cor = noDesbal->pai->cor;
          noDesbal->pai->cor = 'P';
          if (irmao->Fesq != NULL)
            irmao->Fesq->cor = 'P';
          rotacaoDirRubro(arv, noDesbal->pai);

          // Atualizar contador
          if (rotacoesRBRE != NULL) {

            *rotacoesRBRE += 1;
          }
        }
        noDesbal = arv->sentinela->Fdir;
      }
    }
  }
  noDesbal->cor = 'V';
}

void rotacaoDirRubro(arv *arv, no *noDesbal) {
  no *filhoEsq = noDesbal->Fesq;
  noDesbal->Fesq = filhoEsq->Fdir;

  if (filhoEsq->Fdir != NULL) {
    filhoEsq->Fdir->pai = noDesbal;
  }

  filhoEsq->pai = noDesbal->pai;

  if (noDesbal->pai == NULL) {
    arv->sentinela->Fdir = filhoEsq;
  } else if (noDesbal == noDesbal->pai->Fesq) {
    noDesbal->pai->Fesq = filhoEsq;
  } else {
    noDesbal->pai->Fdir = filhoEsq;
  }

  filhoEsq->Fdir = noDesbal;
  noDesbal->pai = filhoEsq;
}

void rotacaoEsqRubro(arv *arv, no *noDesbal) {
  no *filhoDir = noDesbal->Fdir;
  noDesbal->Fdir = filhoDir->Fesq;

  if (filhoDir->Fesq != NULL) {
    filhoDir->Fesq->pai = noDesbal;
  }

  filhoDir->pai = noDesbal->pai;

  if (noDesbal->pai == NULL) {
    arv->sentinela->Fdir = filhoDir;
  } else if (noDesbal == noDesbal->pai->Fesq) {
    noDesbal->pai->Fesq = filhoDir;
  } else {
    noDesbal->pai->Fdir = filhoDir;
  }

  filhoDir->Fesq = noDesbal;
  noDesbal->pai = filhoDir;
}

int getNumElementosRubro(arv *arv) { return arv->numElementos; }

no *getRaizRubro(arv *arv) { return arv->sentinela->Fdir; }

void imprimePreOrdemRubro(arv *arv, no *raiz) {
  if (raiz != NULL && raiz->chave != -1000) {
    printf("%d - %d - %c\n", raiz->chave,
           raiz->pai != NULL ? raiz->pai->chave : -1000, raiz->cor);
    imprimePreOrdemRubro(arv, raiz->Fesq);
    imprimePreOrdemRubro(arv, raiz->Fdir);
  }
}

void imprimeOrdemRubro(arv *arv, no *raiz) {
  if (raiz != arv->null) {
    imprimePreOrdemRubro(arv, raiz->Fesq);
    printf("%d - %d - %c\n", raiz->chave,
           raiz->pai != NULL ? raiz->pai->chave : -1000, raiz->cor);
    imprimePreOrdemRubro(arv, raiz->Fdir);
  }
}

void imprimeArvoreRubro(arv *arv) {
  printf("Imprimindo árvore Rubro-Negra:\n");
  imprimePreOrdemRubro(arv, arv->sentinela->Fdir);
}