typedef struct no no;
typedef struct avl avl;

//Função que cria e retorna uma estrutura do tipo árvore balanceada utilizando o algoritmo AVL
avl *criaArvore();

//Função que insere um elemento na árvore
//Retorna 1 se a inserção foi realizada com sucesso
//Retorna 0 se não foi possível realizar a inserção
int insereNo(avl *arv, int valor);

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Retorna -1 caso o elemento a ser removido não esteja na árvore
int removeNo(avl *arv, int valor);

//Função que imprime a árvore em ordem
//printf("%d - %d - %d\n",chave, pai, fb)
void imprimeOrdem(no *raiz);

//Função que imprime a árvore em pré-ordem
//printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
void imprimePreOrdem(no *raiz);

//Função que retorna a raiz da árvore
no *getRaiz(avl *arv);

//Função que retorna a quantidade de elementos da árvore
int getNumElementos(avl *arv);

//Função que verifica o desbalanceamento na inserção
void atualizaFB_insercao(avl *arv, no *novoNo);

//Função que faz o balanceamento após inseção
void balanceamento(avl *arv, no *noDesbal);

//Função que implementa a rotação à direita
void rotacaoDir(no *noDesbal);

//Função que implementa a rotação à esquerda
void rotacaoEsq(no *noDesbal);

//Função que verifica o desbalanceamento na remoção
void atualizaFB_remocao(avl *arv, no *pai, int chaveRemovida);
