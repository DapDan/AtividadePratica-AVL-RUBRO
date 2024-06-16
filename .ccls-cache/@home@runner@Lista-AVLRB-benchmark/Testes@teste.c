#include "../AVL/avl.h"
#include "../Rubro/rubro.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//struct de cada tipo, tanto da AVL quanto da Rubro-Negra
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
void elementos10000(char *nomeArquivo);
void selecionar1000Elementos(char *inputFile, char *outputFile);
void shuffle(int *array, int n);
double timediff(clock_t, clock_t);

void tabelaInsercaoAVL(float tempoAVLIN, long int rotacoesAVLIN);
void tabelaRemocaoAVL(float tempoAVLRE, long int rotacoesAVLRE);
void tabelaBuscaAVL(float tempoAVLBU);

void tabelaInsercaoRubro(float tempoRBIN, long int rotacoesRBIN);
void tabelaRemocaoRubro(float tempoRBRE, long int rotacoesRBRE);
void tabelaBuscaRubro(float tempoRBBU);


int opcao() {
  // op = variavel para a escolha do tipo de arvore, avl ou rubro negra
  // escolha se refere se a pessoa vai quere remover ou buscar 1000 elementos aleatorios dos 10000 elementos da arvore
  int op, escolha;

  /*Modo de ler essa variaveis:

  AVL OU RB = tipo da arvore

  I OU F = Significa inicio e fim e se vai ser usado antes da funcao

  IN, RE OU BU = se o tempo se refere a insercao, remocao ou busca

  */

  // Variáveis para medir tempo e contar rotações
  clock_t tempAVLIIN, tempAVLFIN, tempAVLIRE, tempAVLFRE, tempAVLIBU,
      tempAVLFBU, tempRBIIN, tempRBFIN, tempRBIRE, tempRBFRE, tempRBIBU,
      tempRBFBU;

  float tempoAVLIN, tempoAVLRE, tempoAVLBU, tempoRBIN, tempoRBRE, tempoRBBU;

  long int rotacoesAVLIN = 0, rotacoesAVLRE = 0, rotacoesRBIN = 0,
           rotacoesRBRE = 0;

  printf("\n1 - AVL\n2 - Rubro-Negra\n"
         "\nEscolha um algoritmo para a realizacao do teste: ");
  scanf("%d", &op);

  switch (op) {
  case 1: // AVL
    printf("\nInserindo 10.000 elementos na AVL\n");
    elementos10000("10000.txt"); // Gera arquivo com 10.000 elementos

    // agora inserir cada elemento na AVL

    //inicializa a AVL
    avl *arvoreAVL;
    int resAVL;

    arvoreAVL = criaArvoreAVL();

    tempAVLIIN = clock();
    resAVL = processaCargaAVL(arvoreAVL, "10000.txt", 1, &rotacoesAVLIN,
                              &rotacoesAVLRE);
    tempAVLFIN = clock();
    tempoAVLIN = timediff(tempAVLIIN, tempAVLFIN); // Calcula tempo de inserção

    if (resAVL == -2) {
      printf("Erro ao abrir o arquivo de insercao");
      return 0;
    }
    if (resAVL == 0) {
      printf("Erro na insercao");
      return 0;
    }

    tabelaInsercaoAVL(tempoAVLIN, rotacoesAVLIN); // Mostra resultados da inserção

    //nessa parte comentada se refere aos elementos, mostrando o pai do nó e o FB
    // printf("\tele - \tpai - \tfb\n");
    // imprimeOrdemAVL(getRaizAVL(arvoreAVL));
    printf("Qtd de elementos: %d\n", getNumElementosAVL(arvoreAVL));
    
    printf("\n1 - Remover Elementos\n2 - Encontrar Elementos\n"
           "\nEscolha o que deseja fazer agora: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1: // Remover elementos
      printf("\nRemovendo 10.000 elementos na AVL\n");

      tempAVLIRE = clock();
      resAVL = processaCargaAVL(arvoreAVL, "10000.txt", 2, &rotacoesAVLIN,
                                &rotacoesAVLRE);
      tempAVLFRE = clock();
      tempoAVLRE = timediff(tempAVLIRE, tempAVLFRE); // Calcula tempo de remoção
      if (resAVL == -2) {
        printf("Erro ao abrir o arquivo de remocao");
        return 0;
      }
      if (resAVL == 0) {
        printf("Erro na remocao");
        return 0;
      }

      tabelaRemocaoAVL(tempoAVLRE, rotacoesAVLRE); // Mostra resultados da remoção

      printf("Qtd de elementos: %d\n", getNumElementosAVL(arvoreAVL));
      free(arvoreAVL);
      break;
    case 2: // Buscar elementos
      printf("\nEscolhendo 1.000 elementos aleatórios na AVL\n");
      selecionar1000Elementos("10000.txt", "1000.txt"); // Seleciona 1000 elementos aleatórios

      tempAVLIBU = clock();
      buscaElementosEmArquivoAVL(arvoreAVL, "1000.txt");
      tempAVLFBU = clock();
      tempoAVLBU = timediff(tempAVLIBU, tempAVLFBU); // Calcula tempo de busca
      
      tabelaBuscaAVL(tempoAVLBU); // Mostra resultados da busca
      break;

    default:
      printf("Opção Inválida!");
      break;
    }

    break;

  case 2: // Rubro-Negra
    printf("\nInserindo 10.000 elementos na Rubro Negra\n");
    elementos10000("10000.txt");

    // agora inserir cada elemento na RUBRO
    // Inicializa árvore Rubro-Negra
    arv *arvoreRUBRO;
    int resRUBRO, escolha;

    arvoreRUBRO = criaArvoreRubro(); // Cria árvore Rubro-Negra

    tempRBIIN = clock();
    resRUBRO = processaCargaRubro(arvoreRUBRO, "10000.txt", 1, &rotacoesRBIN, &rotacoesRBRE);
    tempRBFIN = clock();
    tempoRBIN = timediff(tempRBIIN, tempRBFIN); // Calcula tempo de inserção

    if (resRUBRO == -2) {
      printf("Erro ao abrir o arquivo de insercao");
      return 0;
    }
    if (resRUBRO == 0) {
      printf("Erro na insercao");
      return 0;
    }

    tabelaInsercaoRubro(tempoRBIN, rotacoesRBIN); // Mostra resultados da inserção

    printf("\n1 - Remover Elementos\n2 - Encontrar Elementos\n"
           "\nEscolha o que deseja fazer agora: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("\nRemovendo 10.000 elementos na RUBRO\n");

      tempRBIRE = clock();
      resRUBRO = processaCargaRubro(arvoreRUBRO, "10000.txt", 2, &rotacoesRBIN, &rotacoesRBRE);
      tempRBFRE = clock();
      tempoRBRE = timediff(tempRBIRE, tempRBFRE);  // Calcula tempo de remoção

      if (resRUBRO == -2) {
        printf("Erro ao abrir o arquivo de remocao");
        return 0;
      }
      if (resRUBRO == 0) {
        printf("Erro na remocao");
        return 0;
      }

      tabelaRemocaoRubro(tempoRBRE, rotacoesRBRE); // Mostra resultados da remoção

      printf("Qtd de elementos: %d\n", getNumElementosRubro(arvoreRUBRO));
      free(arvoreRUBRO);
      break;

    case 2: // Buscar elementos
      printf("\nEscolhendo 1.000 elementos aleatórios na RUBRO\n");
      selecionar1000Elementos("10000.txt", "1000.txt");

      tempRBIBU = clock();
      buscaElementosEmArquivoRubro(arvoreRUBRO, "1000.txt");
      tempRBFBU = clock();
      tempoRBBU = timediff(tempRBIBU, tempRBFBU); // Calcula tempo de busca

      tabelaBuscaRubro(tempoRBBU); // Mostra resultados da busca

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

void tabelaInsercaoAVL(float tempoAVLIN, long int rotacoesAVLIN){

  printf("===============================\n");
  printf("TABELA DE INSERCAO AVL\n");
  printf("Tempo: %f segundos\n", tempoAVLIN);
  printf("Rotacoes: %ld\n", rotacoesAVLIN);

  printf("\n");
  
}

void tabelaRemocaoAVL(float tempoAVLRE, long int rotacoesAVLRE){

  printf("===============================\n");
  printf("TABELA DE REMOCAO AVL\n");
  printf("Tempo: %f segundos\n", tempoAVLRE);
  printf("Rotacoes: %ld\n", rotacoesAVLRE);

  printf("\n");

}

void tabelaBuscaAVL(float tempoAVLBU){

  printf("===============================\n");
  printf("TABELA DE BUSCA AVL\n");
  printf("Tempo: %f segundos\n", tempoAVLBU);

  printf("\n");

}

void tabelaInsercaoRubro(float tempoRBIN, long int rotacoesRBIN){

  printf("===============================\n");
  printf("TABELA DE INSERCAO RUBRO NEGRA\n");
  printf("Tempo: %f segundos\n", tempoRBIN);
  printf("Rotacoes: %ld\n", rotacoesRBIN);

  printf("\n");

}

void tabelaRemocaoRubro(float tempoRBRE, long int rotacoesRBRE){

  printf("===============================\n");
  printf("TABELA DE REMOCAO RUBRO NEGRA\n");
  printf("Tempo: %f segundos\n", tempoRBRE);
  printf("Rotacoes: %ld\n", rotacoesRBRE);

  printf("\n");

}

void tabelaBuscaRubro(float tempoRBBU){

  printf("===============================\n");
  printf("TABELA DE BUSCA AVL\n");
  printf("Tempo: %f segundos\n", tempoRBBU);

  printf("\n");

}

// Gera arquivo com 10.000 elementos ordenados
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

// Função para embaralhar array
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

// Seleciona 1000 elementos aleatórios do arquivo "10000.txt"
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

// Calcula a diferença de tempo
double timediff(clock_t tempI, clock_t tempF) {

  double diff;
  diff = ((double)tempF - tempI) / CLOCKS_PER_SEC * 1000;
  return diff;
}