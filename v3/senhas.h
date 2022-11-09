typedef struct senha {
  int codigoCidadao, chave;
  char servico[12];
  struct senha *prox;
} Senha;

void enfileirar(Senha **fila, Senha dados) {
  Senha *nova, *p, *q;
  nova = (Senha *) malloc(sizeof(Senha));
  if(nova) {
    /* copiar os dados para o nova */
    nova->chave = dados.chave;
    nova->codigoCidadao = dados.codigoCidadao;
    strcpy(nova->servico, dados.servico);
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


void carregarContadorDeSenhas(int *contadorDeSenhas) {
  FILE *arq;
  int status;
  arq = fopen("contadorDeSenhas.data", "r");
  if(arq) {
    status = fscanf(arq, "%d", contadorDeSenhas);
    if(status == -1) {
      *contadorDeSenhas = 0; 
    }
  } else {
    printf("Falaha ao abrir o arquivo 'contadorDeSenhas.data'.\n");
  }
}

void salvarContadorDeSenhas(int contadorDeSenhas) {
  FILE *arq;
  arq = fopen("contadorDeSenhas.data", "w");
  if(arq) {
    fprintf(arq, "%d", contadorDeSenhas);
  } else {
    printf("Falaha ao abrir o arquivo 'contadorDeSenhas.data'.\n");
  }
}

void gerarSenha(int *contadorDeSenhas) {
  *contadorDeSenhas = (*contadorDeSenhas) + 1;
}

void mostrarFila(Senha *fila) {
  if(fila) {
    printf("chave: %d; servico: %s\n", fila->chave, fila->servico);
    mostrarFila(fila->prox);
  }
}