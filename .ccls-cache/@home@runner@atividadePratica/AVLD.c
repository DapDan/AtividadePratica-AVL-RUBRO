#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define TAM 10000
#define TAM2 1000
#define TETO 50000
#define COMECO 1500

/*Oque já foi feito:

    Ja fiz a funcao que escreve 10000 elementos em um arquivo nomeado
   "entradaL.txt" (adicionei o merge e o mergesort)

    Ja fiz a funcao que busca 1000 elementos em uma arvore binaria AVL (falta
   adicionar o tempo)

*/

/* Lembrete:

    clock_t t1, t2;

    t1 = clock();
    ...
    t2 = clock();

    mediatemp += timediff(t1, t2);

    a funcao timediff vc tem que escrever ela, nao vem sozinha nao

*/

/* Coisas a se fazer (Nao sei o quao preciso é)

    Adicionar os contadores de tempo
    Adicionar os contadores de rotações

    Fazer rodar os 10000 elementos e obter os contadores

    Integrar todo o programa

    Criar o menu para aparecer todos os contadores e responder as questões

    (Pode estar faltando coisas)

*/

typedef struct no {

  long int chave;
  int fb;
  struct no *Fesq;
  struct no *Fdir;
  struct no *pai;

} no;

typedef struct avl {

  struct no *sentinela;
  int numElementos;

} avl;

avl *criaArvore();
long int *escreveArq();
void mergeSort(long int *, int, int);
void merge(long int *, int, int, int);
void procuraElementoArvore(avl *, long int *);
int insereNo(avl *, int, long int *);
void atualizaFB_insercao(avl *, no *, long int *);
int removeNo(avl *, int, long int *);
void atualizaFB_remocao(avl *, no *, int, long int *);
int processaCarga(avl *, int, long int *);
void balanceamento(avl *, no *, long int *, long int *);
void rotacaoEsq(no *);
void rotacaoDir(no *);
void introducao();
long timediff(clock_t, clock_t);
void removeElementosArvore(avl *, long int *, long int *);
void tabelaInsercao(float, long int);
void tabelaRemocao(float, long int);
void tabelaBusca(float);

void introducao() {

  printf("Vamos fazer tres testes:\nInserir 10000 elementos\nProcurar 1000 "
         "elementos\nRemover 10000 elementos\n");
  sleep(2);
  printf("Para cada teste sera mostrado o tempo decorrido e a quantidade de "
         "rotações executadas (quando houver)\n");
  sleep(2);
  printf("Comecando testes...");
  sleep(2);
}

void tabelaInsercao(float tempo, long int rotacoes) {

  printf("================================================\n");
  printf("TABELA DE INSERCAO DE 10000 ELEMENTOS NA ARVORE\n");
  printf("Tempo:      %f", tempo);
  printf("Rotacoes:   %li", rotacoes);
}

void tabelaRemocao(float tempo, long int rotacoes) {

  printf("================================================\n");
  printf("TABELA DE REMOCAO DE 10000 ELEMENTOS NA ARVORE\n");
  printf("Tempo:      %f", tempo);
  printf("Rotacoes:   %li", rotacoes);
}

void tabelaBusca(float tempo) {

  printf("================================================\n");
  printf("TABELA DE BUSCA DE 1000 ELEMENTOS NA ARVORE\n");
  printf("Tempo:      %f", tempo);
}

avl *criaArvore() {

  avl *arv = (avl *)malloc(sizeof(avl));
  if (arv != NULL) {
    arv->numElementos = 0;
    no *sent = (no *)malloc(sizeof(no));
    sent->chave = -1000;
    sent->Fdir = NULL;
    sent->Fesq = NULL;
    sent->pai = NULL;
    arv->sentinela = sent;
  }
  return arv;
}

long int *escreveArq() {
  int i, j;

  long int *vetor = (long int *)malloc(sizeof(long int) * TAM);

  mergeSort(vetor, 0, TAM - 1);

  srand(time(NULL));

  for (i = 0; i < TAM; i++) {

    vetor[i] = (rand() % (TETO + 1));
  }

  FILE *arq = fopen("entradaL.txt", "w");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return NULL;
  }

  for (j = 0; j < TAM; j++) {
    fprintf(arq, "%d\n", vetor[j]);
  }

  fclose(arq);

  return vetor;
}

void mergeSort(long int *vet, int inicio, int fim) {
  int meio;
  meio = (inicio + fim) / 2;
  if (inicio < fim) {
    mergeSort(vet, inicio, meio);
    mergeSort(vet, meio + 1, fim);
    merge(vet, inicio, meio, fim);
  }
}

void merge(long int *vet, int inicio, int meio, int fim) {
  int marcador1 = inicio;
  int marcador2 = meio + 1;
  int i = 0;
  int *vetoraux;

  vetoraux = (int *)malloc(((fim - inicio) + 1) * sizeof(int));
  if (vetoraux == NULL) {
    printf("ERRO AO ALOCAR MEMÓRIA\n");
    exit(1);
  }

  while (marcador1 <= meio && marcador2 <= fim) {

    if (vet[marcador1] <= vet[marcador2]) {

      vetoraux[i] = vet[marcador1];
      i++;
      marcador1++;

    } else {
      vetoraux[i] = vet[marcador2];
      i++;
      marcador2++;
    }
  }
  while (marcador1 <= meio)
    vetoraux[i++] = vet[marcador1++];

  while (marcador2 <= fim)
    vetoraux[i++] = vet[marcador2++];

  for (marcador1 = inicio; marcador1 <= fim; marcador1++)
    vet[marcador1] = vetoraux[marcador1 - inicio];

  free(vetoraux);
}

void procuraElementoArvore(avl *arv, long int *vet) {
  int i, j;

  no *aux = arv->sentinela->Fdir;

  if (TAM2 > TAM) {
    printf("Tentando buscar mais elementos do que existem\n");
    exit(1);
  }

  for (i = COMECO; i < (TAM2 + COMECO); i++) {

    while ((aux != NULL) && (aux->chave != vet[i])) {
      if (aux->chave > vet[i]) {
        aux = aux->Fesq;
      } else {
        aux = aux->Fdir;
      }
    }
  }
}

int insereNo(avl *arv, int valor, long int *rotacoesI) {

  if (arv == NULL)
    return 0;

  no *novoNo = (no *)malloc(sizeof(no));

  novoNo->chave = valor;
  novoNo->fb = 0;
  novoNo->Fdir = NULL;
  novoNo->Fesq = NULL;
  novoNo->pai = NULL;

  if (arv->sentinela->Fdir == NULL) {
    arv->sentinela->Fdir = novoNo;
    novoNo->pai = arv->sentinela;
    arv->numElementos++;
    return 1;
  } else {
    no *atual = arv->sentinela->Fdir;
    no *anterior = atual->pai;

    while (atual != NULL) {
      anterior = atual;

      if (valor < atual->chave) {
        atual = atual->Fesq;
      } else {
        atual = atual->Fdir;
      }
    }
    if (valor < anterior->chave) {
      anterior->Fesq = novoNo;
      novoNo->pai = anterior;
    } else {
      anterior->Fdir = novoNo;
      novoNo->pai = anterior;
    }
  }

  arv->numElementos++;
  atualizaFB_insercao(arv, novoNo, rotacoesI);
  return 1;
}

void atualizaFB_insercao(avl *arv, no *novoNo, long int *rotacoesI) {
  no *aux;
  aux = novoNo;
  do {
    if (aux->chave < aux->pai->chave) {
      aux->pai->fb--;
    } else {
      aux->pai->fb++;
    }
    aux = aux->pai;
  } while ((aux->fb != 0) && (aux->fb != 2) && (aux->fb != -2) &&
           (aux->pai != arv->sentinela));
  if ((aux->fb == 2) || (aux->fb == -2)) {
    balanceamento(arv, aux, rotacoesI, NULL);
  }
}

int removeNo(avl *arv, int valor, long int *rotacoesR) {

  no *pai = NULL;
  no *atual = arv->sentinela;

  if (atual == NULL) {
    return 0;
  }
  while (atual != NULL && atual->chave != valor) {
    pai = atual;
    if (valor < atual->chave) {
      atual = atual->Fesq;
    } else {
      atual = atual->Fdir;
    }
  }
  if (atual == NULL) {
    return -1;
  }
  if (atual->Fesq == NULL && atual->Fdir == NULL) {
    if (pai == NULL) {
      arv->sentinela = NULL;
    } else if (atual == pai->Fesq) {
      pai->Fesq = NULL;
    } else {
      pai->Fdir = NULL;
    }
    atualizaFB_remocao(arv, pai, atual->chave, rotacoesR);
    free(atual);
  }

  else if (atual->Fesq == NULL || atual->Fdir == NULL) {
    no *ramo;
    if (atual->Fesq == NULL) {
      ramo = atual->Fdir;
      ramo->pai = pai;
    } else {
      ramo = atual->Fesq;
      ramo->pai = pai;
    }
    if (pai == NULL) {
      arv->sentinela = ramo;
    } else if (atual == pai->Fesq) {
      pai->Fesq = ramo;
    } else {
      pai->Fdir = ramo;
    }
    atualizaFB_remocao(arv, pai, atual->chave, rotacoesR);
    free(atual);
  } else {
    no *proximo = atual->Fdir;
    pai = atual;
    while (proximo->Fesq != NULL) {
      pai = proximo;
      proximo = proximo->Fesq;
    }
    atual->chave = proximo->chave;
    if (pai->Fesq == proximo) {
      pai->Fesq = proximo->Fdir;
      if (proximo->Fdir != NULL) {
        proximo->Fdir->pai = atual;
      }
    } else {
      pai->Fdir = proximo->Fdir;
      if (proximo->Fdir != NULL) {
        proximo->Fdir->pai = atual;
      }
    }

    atualizaFB_remocao(arv, proximo->pai, proximo->chave, rotacoesR);
    free(proximo);
    proximo = NULL;
  }
  arv->numElementos--;
  return 1;
}

void atualizaFB_remocao(avl *arv, no *pai, int chaveRemovida,
                        long int *rotacoesR) {

  if (pai == arv->sentinela)
    return;

  no *aux = pai;

  if (chaveRemovida < aux->chave) {
    aux->fb++;
  } else {
    aux->fb--;
  }

  while (aux != arv->sentinela->Fdir && aux->fb == 0) {
    aux = aux->pai;

    if (chaveRemovida < aux->chave) {
      aux->fb++;
    } else {
      aux->fb--;
    }
  }

  if (aux->fb == 2 || aux->fb == -2) {
    balanceamento(arv, aux, NULL, rotacoesR);
    if ((aux->pai != arv->sentinela) && (aux->pai->fb == 0)) {
      atualizaFB_remocao(arv, aux->pai->pai, chaveRemovida, rotacoesR);
    }
  }
}

int processaCarga(avl *arv, int tipo, long int *rotacoesI) {

  FILE *arquivo;
  int insere, remove;

  arquivo = fopen("entradaL.txt", "r");

  if (arquivo == NULL) {
    return -2;
  }

  if (tipo == 1) {

    if (arv == NULL) {
      return 0;
    }

    while (fscanf(arquivo, "%d", &insere) == 1) {
      insereNo(arv, insere, rotacoesI);
    }

    return 1;
  }

  // Essa parte nao sera usada
  if (tipo == 2) {

    if (arv->sentinela->Fdir == NULL) {

      return 0;
    }

    while (fscanf(arquivo, "%d", &remove) == 1) {
      removeNo(arv, remove, NULL);
    }
    return 1;
  }

  fclose(arquivo);
}

void removeElementosArvore(avl *arv, long int *vet, long int *rotacoesR) {

  int i;

  for (i = (TAM - 1); i >= 0; i--) {

    removeNo(arv, vet[i], rotacoesR);
  }
}

void balanceamento(avl *arv, no *noDesbalanceado, long int *rotacoesI,
                   long int *rotacoesR) {

  no *filho;
  if (noDesbalanceado->fb == -2) {
    filho = noDesbalanceado->Fesq;
    if (filho->fb == 1) { //erro nessa linha de segmentação

      int fbNeto = filho->Fdir->fb;
      rotacaoEsq(filho);
      rotacaoDir(noDesbalanceado);

      // Aumentar o contador de rotacoes
      if (rotacoesI != NULL) {

        *rotacoesI += 2;
      }

      if (rotacoesR != NULL) {

        *rotacoesR += 2;
      }

      if (fbNeto == 0) {
        noDesbalanceado->fb = 0;
        filho->fb = 0;
      } else if (fbNeto == -1) {
        noDesbalanceado->fb = 1;
        filho->fb = 0;
        noDesbalanceado->pai->fb = 0;
      } else {
        noDesbalanceado->fb = 0;
        filho->fb = -1;
        noDesbalanceado->pai->fb = 0;
      }
    } else {

      int fbFilho = filho->fb;
      rotacaoDir(noDesbalanceado);

      if (rotacoesI != NULL) {

        *rotacoesI++;
      }

      if (rotacoesR != NULL) {

        *rotacoesR++;
      }

      if (fbFilho != 0) {

        filho->fb = 0;
        noDesbalanceado->fb = 0;
      } else {
        filho->fb = 1;
        noDesbalanceado->fb = -1;
      }
    }
  }

  if (noDesbalanceado->fb == 2) {
    filho = noDesbalanceado->Fdir;
    if (filho->fb == -1) {

      int fbNeto = filho->Fesq->fb;
      rotacaoDir(filho);
      rotacaoEsq(noDesbalanceado);

      if (rotacoesI != NULL) {

        *rotacoesI += 2;
      }

      if (rotacoesR != NULL) {

        *rotacoesR += 2;
      }

      if (fbNeto == 0) {
        noDesbalanceado->fb = 0;
        filho->fb = 0;
      } else if (fbNeto == -1) {
        noDesbalanceado->fb = 0;
        filho->fb = 1;
        noDesbalanceado->pai->fb = 0;
      } else {
        noDesbalanceado->fb = -1;
        filho->fb = 0;
        noDesbalanceado->pai->fb = 0;
      }
    } else {

      int fbFilho = filho->fb;
      rotacaoEsq(noDesbalanceado);

      if (rotacoesI != NULL) {

        *rotacoesI++;
      }

      if (rotacoesR != NULL) {

        *rotacoesR++;
      }

      if (fbFilho != 0) {

        filho->fb = 0;
        noDesbalanceado->fb = 0;
      } else {
        filho->fb = -1;
        noDesbalanceado->fb = 1;
      }
    }
  }
}

void rotacaoEsq(no *noDesbal) {
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

void rotacaoDir(no *noDesbal) {
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

long timediff(clock_t t1, clock_t t2) {
  long elapsed;
  elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
  return elapsed;
}

int main() {

  /*Explicação dos nomes

      I = insercao
      B = busca
      R = remocao

  */

  clock_t tempI1, tempI2, tempB1, tempB2, tempR1, tempR2;
  float tempI3 = 0.0, tempB3 = 0.0, tempR3 = 0.0;
  long int rotacoesI = 0, rotacoesR = 0;

  // Funcao que da as mensagens de introducao
  introducao();

  long int *vetor = escreveArq();
  avl *arv = criaArvore();

  tempI1 = clock();
  // Processa carga da uns problemas...
  processaCarga(arv, 1, &rotacoesI);
  tempI2 = clock();

  // Funcao para calcular diferenca de tempo
  tempI3 = timediff(tempI1, tempI2);

  tempB1 = clock();

  procuraElementoArvore(arv, vetor);

  tempB2 = clock();

  tempB3 = timediff(tempB1, tempB2);

  tempR1 = clock();
  // Segundo problema aqui
  removeElementosArvore(arv, vetor, &rotacoesR);
  tempR2 = clock();

  tempR3 = timediff(tempR1, tempR2);

  printf("Para o primeiro teste:\n");
  tabelaInsercao(tempI3, rotacoesI);
  sleep(8000);

  printf("Para o segundo teste:\n");
  tabelaBusca(tempB3);
  sleep(8000);

  printf("Para o terceiro teste:\n");
  tabelaRemocao(tempR3, rotacoesR);
  sleep(8000);

  return 0;
}

/*

void imprimeOrdem(no *raiz){

    if(raiz == NULL)
        return;

    if(raiz != NULL){
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimeOrdem(raiz->Fesq);
        imprimeOrdem(raiz->Fdir);
    }
}


void imprimePreOrdem(no *raiz){

    if(raiz == NULL)
        return;

    if(raiz->pai == NULL){
        imprimePreOrdem(raiz->Fesq);
        imprimePreOrdem(raiz->Fdir);
    }
    else if(raiz->pai != NULL){
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimePreOrdem(raiz->Fesq);
        imprimePreOrdem(raiz->Fdir);
    }
}

no *getRaiz(avl *arv){
    return arv->sentinela;
}

int getNumElementos(avl *arv){

    return arv->numElementos;

}

*/