#include <stdlib.h>
typedef struct lista {
  int info;
  struct lista *prox;
} Lista;

Lista* inicializar(){
  return NULL;
}

void inserir(Lista** l, int i){
  Lista* novo = (Lista*)malloc(sizeof(Lista));
  novo->info=i;
  novo->prox=*l;
  *l= novo;
}