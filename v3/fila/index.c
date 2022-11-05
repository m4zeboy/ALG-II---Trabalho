#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct senha {
  int chave;
  struct senha *prox;
} Senha;

void enfileirar(Senha **fila, int chave) {
  Senha *nova, *p, *q;
  nova = (Senha *) malloc(sizeof(Senha));
  if(nova) {
    /* copiar os dados para o nova */
    nova->chave = chave;
    nova->prox = NULL;
    p = NULL; q = *fila;
    while(q) {
      p = q;
      q = q->prox;
    }
    if(p == NULL) {
      *fila = nova;
    } else {
      p->prox = nova;
      nova->prox = NULL;
    }
  } else {
    fprintf(stderr, "Erro ao alocar memória.\n");
  }
}

void mostraFila(Senha *fila) {
  if(fila) {
    printf("chave: %d\n", fila->chave);
    mostraFila(fila->prox);
  }
}


int main(void){
  Senha *fila;
  fila = NULL;
  enfileirar(&fila, 1);
  enfileirar(&fila, 2);
  enfileirar(&fila, 3);
  enfileirar(&fila, 4);
  mostraFila(fila);
  return 0;
}