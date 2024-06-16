// #include <stdio.h>
// #include <stdlib.h>

// struct no {
//     int chave;
//     char cor;
//     struct no *esq;
//     struct no *dir;
//     struct no *pai;
// };

// typedef struct no no;

// struct rb {
//     struct no *raiz;
//     int numElementos;
// };

// typedef struct rb rb;

// rb *criaArvore() {
//     rb *arv = (rb *) malloc(sizeof(rb));
//     if (arv != NULL) {
//         arv->raiz = NULL;
//         arv->numElementos = 0;
//     }
//     return arv;
// }

// int insereNo(rb *arv, int valor) {
//     if (arv == NULL)
//         return 0;

//     no *novoNo = (no *) malloc(sizeof(no));
//     if (novoNo == NULL)
//         return 0;

//     novoNo->chave = valor;
//     novoNo->cor = 'V';
//     novoNo->esq = NULL;
//     novoNo->dir = NULL;
//     novoNo->pai = NULL;

//     if (arv->raiz == NULL) {
//         novoNo->cor = 'P';
//         arv->raiz = novoNo;
//         arv->numElementos++;
//         return 1;
//     }

//     no *atual = arv->raiz;
//     no *ant = NULL;

//     while (atual != NULL) {
//         ant = atual;

//         if (valor == atual->chave) {
//             free(novoNo);
//             return 0; // Valor já existe na árvore
//         } else if (valor < atual->chave) {
//             atual = atual->esq;
//         } else {
//             atual = atual->dir;
//         }
//     }

//     novoNo->pai = ant;
//     if (valor < ant->chave) {
//         ant->esq = novoNo;
//     } else {
//         ant->dir = novoNo;
//     }

//     arv->numElementos++;
//     balanceamentoInsercao(arv, novoNo);

//     return 1;
// }

// void balanceamentoInsercao(rb *arv, no *noDesbal) {
//     while (noDesbal->pai != NULL && noDesbal->pai->cor == 'V') {
//         if (noDesbal->pai == noDesbal->pai->pai->esq) {
//             no *tio = noDesbal->pai->pai->dir;

//             if (tio != NULL && tio->cor == 'V') {
//                 noDesbal->pai->cor = 'P';
//                 tio->cor = 'P';
//                 noDesbal->pai->pai->cor = 'V';
//                 noDesbal = noDesbal->pai->pai;
//             } else {
//                 if (noDesbal == noDesbal->pai->dir) {
//                     noDesbal = noDesbal->pai;
//                     rotacaoEsq(arv, noDesbal);
//                 }

//                 noDesbal->pai->cor = 'P';
//                 noDesbal->pai->pai->cor = 'V';
//                 rotacaoDir(arv, noDesbal->pai->pai);
//             }
//         } else {
//             no *tio = noDesbal->pai->pai->esq;

//             if (tio != NULL && tio->cor == 'V') {
//                 noDesbal->pai->cor = 'P';
//                 tio->cor = 'P';
//                 noDesbal->pai->pai->cor = 'V';
//                 noDesbal = noDesbal->pai->pai;
//             } else {
//                 if (noDesbal == noDesbal->pai->esq) {
//                     noDesbal = noDesbal->pai;
//                     rotacaoDir(arv, noDesbal);
//                 }

//                 noDesbal->pai->cor = 'P';
//                 noDesbal->pai->pai->cor = 'V';
//                 rotacaoEsq(arv, noDesbal->pai->pai);
//             }
//         }
//     }

//     arv->raiz->cor = 'P';
// }

// void rotacaoDir(rb *arv, no *noDesbal) {
//     no *filhoEsq = noDesbal->esq;
//     noDesbal->esq = filhoEsq->dir;

//     if (filhoEsq->dir != NULL) {
//         filhoEsq->dir->pai = noDesbal;
//     }

//     filhoEsq->pai = noDesbal->pai;

//     if (noDesbal->pai == NULL) {
//         arv->raiz = filhoEsq;
//     } else if (noDesbal == noDesbal->pai->esq) {
//         noDesbal->pai->esq = filhoEsq;
//     } else {
//         noDesbal->pai->dir = filhoEsq;
//     }

//     filhoEsq->dir = noDesbal;
//     noDesbal->pai = filhoEsq;
// }

// void rotacaoEsq(rb *arv, no *noDesbal) {
//     no *filhoDir = noDesbal->dir;
//     noDesbal->dir = filhoDir->esq;

//     if (filhoDir->esq != NULL) {
//         filhoDir->esq->pai = noDesbal;
//     }

//     filhoDir->pai = noDesbal->pai;

//     if (noDesbal->pai == NULL) {
//         arv->raiz = filhoDir;
//     } else if (noDesbal == noDesbal->pai->esq) {
//         noDesbal->pai->esq = filhoDir;
//     } else {
//         noDesbal->pai->dir = filhoDir;
//     }

//     filhoDir->esq = noDesbal;
//     noDesbal->pai = filhoDir;
// }

// int removeNo(rb *arv, int valor) {
//     char c;
//     if (arv == NULL || arv->raiz == NULL)
//         return 0;

//     no *noRemover = arv->raiz;
//     while (noRemover != NULL && noRemover->chave != valor) {
//         if (valor < noRemover->chave)
//             noRemover = noRemover->esq;
//         else
//             noRemover = noRemover->dir;
//     }

//     if (noRemover == NULL)
//         return -1; // Valor não encontrado

//     if (noRemover->esq != NULL && noRemover->dir != NULL) {
//         no *sucessor = noRemover->dir;
//         while (sucessor->esq != NULL)
//             sucessor = sucessor->esq;

//         noRemover->chave = sucessor->chave;
//         noRemover = sucessor;
//     }

//     no *filho = NULL;
//     if (noRemover->esq != NULL)
//         filho = noRemover->esq;
//     else
//         filho = noRemover->dir;
//     if (noRemover->cor == 'P') {
//         if (filho==NULL){
//             noRemover->cor = 'P';
//         }else{
//             noRemover->cor = filho->cor;
//         }
//         balanceamentoRemocao(arv, noRemover, noRemover->pai, valor);
//     }

//     if (noRemover->pai == NULL) {
//         arv->raiz = filho;
//         if (filho != NULL)
//             filho->pai = NULL;
//     } else {
//         if (noRemover == noRemover->pai->esq)
//             noRemover->pai->esq = filho;
//         else
//             noRemover->pai->dir = filho;

//         if (filho != NULL)
//             filho->pai = noRemover->pai;
//     }

//     free(noRemover);
//     arv->numElementos--;
//     return 1;
// }

// void balanceamentoRemocao(rb *arv, no *noDesbal, no *pai, int valor) {
//     while (noDesbal != arv->raiz && (noDesbal == NULL || noDesbal->cor == 'P')) {
//         if (noDesbal == pai->esq) {
//             no *irmao = pai->dir;

//             if (irmao->cor == 'V') {
//                 irmao->cor = 'P';
//                 pai->cor = 'V';
//                 rotacaoEsq(arv, pai);
//                 irmao = pai->dir;
//             }

//             if ((irmao->esq == NULL || irmao->esq->cor == 'P') && (irmao->dir == NULL || irmao->dir->cor == 'P')) {
//                 irmao->cor = 'V';
//                 noDesbal = pai;
//                 pai = noDesbal->pai;
//             } else {
//                 if (irmao->dir == NULL || irmao->dir->cor == 'P') {
//                     irmao->esq->cor = 'P';
//                     irmao->cor = 'V';
//                     rotacaoDir(arv, irmao);
//                     irmao = pai->dir;
//                 }

//                 irmao->cor = pai->cor;
//                 pai->cor = 'P';
//                 irmao->dir->cor = 'P';
//                 rotacaoEsq(arv, pai);
//                 noDesbal = arv->raiz;
//             }
//         } else {
//             no *irmao = pai->esq;

//             if (irmao->cor == 'V') {
//                 irmao->cor = 'P';
//                 pai->cor = 'V';
//                 rotacaoDir(arv, pai);
//                 irmao = pai->esq;
//             }

//             if ((irmao->dir == NULL || irmao->dir->cor == 'P') && (irmao->esq == NULL || irmao->esq->cor == 'P')) {
//                 irmao->cor = 'V';
//                 noDesbal = pai;
//                 pai = noDesbal->pai;
//             } else {
//                 if (irmao->esq == NULL || irmao->esq->cor == 'P') {
//                     irmao->dir->cor = 'P';
//                     irmao->cor = 'V';
//                     rotacaoEsq(arv, irmao);
//                     irmao = pai->esq;
//                 }

//                 irmao->cor = pai->cor;
//                 pai->cor = 'P';
//                 irmao->esq->cor = 'P';
//                 rotacaoDir(arv, pai);
//                 noDesbal = arv->raiz;
//             }
//         }
//     }

//     if (noDesbal != NULL)
//         noDesbal->cor = 'P';
// }


// void imprimeOrdem(no *raiz) {
//     if (raiz != NULL) {
//         imprimeOrdem(raiz->esq);
//         printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);
//         imprimeOrdem(raiz->dir);
//     }
// }

// void imprimePreOrdem(rb *arv, no *raiz) {
//     if (raiz != NULL) {
//         printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai != NULL ? raiz->pai->chave : -1000);
//         imprimePreOrdem(arv, raiz->esq);
//         imprimePreOrdem(arv, raiz->dir);
//     }
// }

// no *getRaiz(rb *arv) {
//     if (arv != NULL)
//         return arv->raiz;
//     return NULL;
// }

// int getNumElementos(rb *arv) {
//     if (arv != NULL)
//         return arv->numElementos;
//     return 0;
// }

// int processaCarga(rb *arv, char *nomeArquivo, int tipo) {
//     FILE *arquivo = fopen(nomeArquivo, "r");
//     if (arquivo == NULL)
//         return -2;

//     int valor;
//     int resultado = 0;

//     if (tipo == 1) {
//         while (fscanf(arquivo, "%d", &valor) != EOF) {
//             resultado = insereNo(arv, valor);
//             if (resultado == 0)
//                 break;
//         }
//     } else if (tipo == 2) {
//         while (fscanf(arquivo, "%d", &valor) != EOF) {
//             resultado = removeNo(arv, valor);
//             if (resultado == -1)
//                 break;
//         }
//     }

//     fclose(arquivo);
//     return resultado;
// }

