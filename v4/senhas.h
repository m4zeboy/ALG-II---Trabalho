typedef struct  {
  int numero;
  cidadao dados;
} senha;

typedef struct elemento {
  senha senha;
  struct elemento *prox;
}elemento;

void carregaContadorDeSenhas(int *contador) {
  FILE *arq = fopen("contadorDeSenhas.data", "r");
  if(arq) {
    int status = fscanf(arq, "%d", contador);
    if(status == -1) {
      *contador = 0;
    }
    fclose(arq);
  } else {
    fprintf(stderr, "Nao foi possivel abrir o arquivo 'contadorDeSenhas.data'");
      *contador = 0;
  }
}

void salvarContadorDeSenhas(int contador) {
  FILE *arq = fopen("contadorDeSenhas.data", "w");
  if(arq) {
    fprintf(arq,"%d", contador);
    fclose(arq);
  } else {
    fprintf(stderr, "Nao foi possivel abrir o arquivo 'contadorDeSenhas.data'");
  }
}
