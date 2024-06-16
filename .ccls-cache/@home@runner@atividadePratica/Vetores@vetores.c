#include <stdio.h>
#include <stdlib.h>

int* geraAleatorios(int tam, int semente){
  int *vetor, i;

  // Aloca memória para o vetor de inteiros
  vetor = (int*) malloc(tam * sizeof(int));
  if(!vetor){
      printf("\nErro ao alocar memória");
      return NULL;
  }

  // Define a semente para a função rand()
  srand(semente);

  // Preenche o vetor com números aleatórios
  for(i = 0; i < tam; i++)
      vetor[i] = rand();

  return vetor;
}

int* geraQuaseOrdenados(int tam, int porcentagem){
  int *vetor, i, desordenados, pos1, pos2, aux;

  // Aloca memória para o vetor de inteiros
  vetor = (int*) malloc(tam * sizeof(int));
  if(!vetor){
      printf("\nErro ao alocar memória");
      return NULL;
  }

  // Preenche o vetor com números ordenados
  for(i = 0; i < tam; i++){
      vetor[i] = i;
  }

  // Calcula a quantidade de elementos a serem desordenados
  desordenados = (tam * porcentagem) / 100;

  // Faz trocas aleatórias para desordenar o vetor
  srand(time(NULL));
  for (i = 0; i < desordenados; i++) {
      pos1 = rand() % tam;
      pos2 = rand() % tam;

      // Troca os elementos
      aux = vetor[pos1];
      vetor[pos1] = vetor[pos2];
      vetor[pos2] = aux;
  }

  return vetor;
}

int* geraOrdenados(int tam, int ordem) {
  int *vetor;

  vetor = (int*)malloc(tam * sizeof(int));
  if (vetor == NULL) {
      printf("\nErro ao alocar memória");
      return NULL;
  }

  // Preenche o vetor em ordem crescente
  if (ordem == 0) {
      for (int i = 0; i < tam; i++) {
          vetor[i] = i;
      }
  }
      // Preenche o vetor em ordem decrescente
  else if (ordem == 1) {
      for (int i = 0; i < tam; i++) {
          vetor[i] = tam - 1 - i;
      }
  }
      // Valor de ordem inválido
  else {
      printf("Erro: Valor de ordem inválido.\n");
      free(vetor);
      return NULL;
  }

  return vetor;
}