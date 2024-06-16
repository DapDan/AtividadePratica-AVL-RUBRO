#include "../AVL/avl.h"
#include "../Rubro/rubro.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

typedef struct avl {
  struct no *sentinela;
  int numElementos;
} avl;

int opcao();
// int insereArvores(avl *avl, arv *rub, int elemento);
void elementos10000(char *nomeArquivo);
// void remover10000elemtento(char *nomeArquivo);
void selecionar1000Elementos(char *inputFile, char *outputFile);
void shuffle(int *array, int n);

int opcao() {
  int op, num_repeticoes, escolha; // USAR ???
  num_repeticoes = 5;

  printf("\n1 - AVL\n2 - Rubro-Negra\n"
         "\nEscolha um algoritmo para a realizacao do teste: ");
  scanf("%d", &op);

  switch (op) {
  case 1: // AVL
    printf("\nInserindo 10.000 elementos na AVL\n");
    elementos10000("10000.txt");

    // agora inserir cada elemento na AVL
    avl *arvoreAVL;
    int resAVL;

    arvoreAVL = criaArvoreAVL();
    resAVL = processaCargaAVL(arvoreAVL, "10000.txt", 1);
    if (resAVL == -2) {
      printf("Erro ao abrir o arquivo de insercao");
      return 0;
    }
    if (resAVL == 0) {
      printf("Erro na insercao");
      return 0;
    }

    // printf("\tele - \tpai - \tfb\n");
    // imprimeOrdemAVL(getRaizAVL(arvoreAVL));
    printf("Qtd de elementos: %d\n", getNumElementosAVL(arvoreAVL));
    // puts("\n\n");

    printf("\n1 - Remover Elementos\n2 - Encontrar Elementos\n"
           "\nEscolha o que deseja fazer agora: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("\nRemovendo 10.000 elementos na AVL\n");
      resAVL = processaCargaAVL(arvoreAVL, "10000.txt", 2);
      if (resAVL == -2) {
        printf("Erro ao abrir o arquivo de remocao");
        return 0;
      }
      if (resAVL == 0) {
        printf("Erro na remocao");
        return 0;
      }

      // printf("\tele - \tpai - \tfb\n");
      // imprimeOrdemAVL(getRaizAVL(arvoreAVL));
      printf("Qtd de elementos: %d\n", getNumElementosAVL(arvoreAVL));
      free(arvoreAVL);
      break;
    case 2:
      printf("\nEscolhendo 1.000 elementos aleatórios na AVL\n");
      selecionar1000Elementos("10000.txt", "1000.txt");
      // printf("1000 elementos foram salvos em '1000.txt'\n");
      buscaElementosEmArquivoAVL(arvoreAVL, "1000.txt");
      break;

    default:
      printf("Opção Inválida!");
      break;
    }

    break;

  case 2:
    printf("\nInserindo 10.000 elementos na AVL\n");
    elementos10000("10000.txt");

    // agora inserir cada elemento na RUBRO
    arv *arvoreRUBRO;
    int resRUBRO, escolha;

    arvoreRUBRO = criaArvoreRubro();
    resRUBRO = processaCargaRubro(arvoreRUBRO, "10000.txt", 1);
    if (resRUBRO == -2) {
      printf("Erro ao abrir o arquivo de insercao");
      return 0;
    }
    if (resRUBRO == 0) {
      printf("Erro na insercao");
      return 0;
    }

    // printf("\tele - \tpai - \tfb\n");
    // imprimeOrdemRubro(arvoreRUBRO, getRaizRubro(arvoreRUBRO));
    // printf("Qtd de elementos: %d\n", getNumElementosRubro(arvoreRUBRO));
    // puts("\n\n");

    printf("\n1 - Remover Elementos\n2 - Encontrar Elementos\n"
           "\nEscolha o que deseja fazer agora: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("\nRemovendo 10.000 elementos na RUBRO\n");
      resRUBRO = processaCargaRubro(arvoreRUBRO, "10000.txt", 2);
      if (resRUBRO == -2) {
        printf("Erro ao abrir o arquivo de remocao");
        return 0;
      }
      if (resRUBRO == 0) {
        printf("Erro na remocao");
        return 0;
      }

      // printf("\tele - \tpai - \tfb\n");
      // imprimeOrdemAVL(getRaizAVL(arvoreAVL));
      printf("Qtd de elementos: %d\n", getNumElementosRubro(arvoreRUBRO));
      free(arvoreRUBRO);
      break;

    case 2:
      printf("\nEscolhendo 1.000 elementos aleatórios na RUBRO\n");
      selecionar1000Elementos("10000.txt", "1000.txt");
      // printf("1000 elementos foram salvos em '1000.txt'\n");
      buscaElementosEmArquivoRubro(arvoreRUBRO, "1000.txt");
      break;

    default:
      printf("Opção Inválida!");
      break;
    }

    break;
  default:
    printf("Opção Inválida!");
    break;
  }

  return 1;
}

// int insereArvores(avl *avl, arv *rub, int elemento);

void elementos10000(char *nomeArquivo) {
  FILE *arq = fopen(nomeArquivo, "w");
  if (arq == NULL) {
    perror("Erro ao criar arquivo");
    return;
  }

  // inserindo 10000 ordenados no arquivo
  for (int i = 1; i <= 10000; ++i) {
    fprintf(arq, "%d\n", i);
  }

  fclose(arq);
}

// escolhe aleatoriamente 1000 elementos do arquivo "10000.txt"
void shuffle(int *array, int n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void selecionar1000Elementos(char *inputFile, char *outputFile) {
  int elements[10000];
  FILE *file = fopen(inputFile, "r");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo de entrada");
    return;
  }

  for (int i = 0; i < 10000; i++) {
    if (fscanf(file, "%d", &elements[i]) != 1) {
      fprintf(stderr, "Erro ao ler o elemento %d\n", i);
      fclose(file);
      return;
    }
  }
  fclose(file);

  srand(time(NULL));
  shuffle(elements, 10000);

  file = fopen(outputFile, "w");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo de saída");
    return;
  }

  for (int i = 0; i < 1000; i++) {
    fprintf(file, "%d\n", elements[i]);
  }
  fclose(file);
}