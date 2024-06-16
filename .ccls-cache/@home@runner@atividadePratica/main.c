//
// Danilo Alexandre Pereira 15/06/2024
//

#include "AVL/avl.h"
#include "Rubro/rubro.h"
#include "Testes/teste.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  printf("Vamos fazer tres testes:\n\nInserir 10000 elementos\nProcurar 1000 "
         "elementos\nRemover 10000 elementos\n\n");

  printf("Para cada teste sera mostrado o tempo decorrido e a quantidade de "
         "rotações executadas (quando houver)\n\n");
  printf("Comecando testes...");
  sleep(1);

  opcao();
  return 0;
}
