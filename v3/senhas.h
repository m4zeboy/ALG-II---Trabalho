typedef struct senha {
  int codigoCidadao, chave;
  char servico[12];
  struct senha *prox;
} Senha;

typedef struct atedimento {
  int codigoCidadao, chave, mesa;
  char servico[12], servidor[30];
  struct atedimento *prox;
} Atedimento;

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

void mostrarFila(Senha *fila) {
  if(fila) {
    printf("chave: %d; servico: %s\n", fila->chave, fila->servico);
    mostrarFila(fila->prox);
  }
}

void relatorioProximos(Senha *fila, Senha *filaP, Cidadao *lista) {
  FILE *arq;
  Cidadao *temp;
  char pref[20];
  arq = fopen("proximos.csv", "w");
  if(arq) {
   while(filaP) {
      temp = buscaCidadao(lista, filaP->codigoCidadao);
      strcpy(pref, "PREFERENCIAL");
      fprintf(arq, "%d;%s;%s;%s\n",
        filaP->chave,
        fila->servico,
        temp->nome,
        pref
      );
      filaP = filaP->prox;

    }
    while(fila) {
      temp = buscaCidadao(lista, fila->codigoCidadao);
      strcpy(pref, "NAO PREFERENCIAL");
      fprintf(arq, "%d;%s;%s;%s\n",
        fila->chave,
        fila->servico,
        temp->nome,
        pref
      );
      fila = fila->prox;

    }
    fclose(arq);
  } else {
    fprintf(stderr, "Nao foi possivel abrir o arquivo: proximos.csv.\n");
  }
}

Senha *desenfileirar(Senha **fila) {
  /* desenfileirar o primeiro elemento */
  Senha *remove;
  remove = *fila;
  *fila = (*fila)->prox;
  return remove;
}

Senha *buscaCidadaoNaFila(Senha *fila, int codigo) {
  if(fila == NULL)
    return NULL;
  if(fila->codigoCidadao == codigo)
    return fila;
  return buscaCidadaoNaFila(fila->prox, codigo);
} 

void copiaDadosDeAtendimento(Atedimento *nova, Atedimento dados) {
  nova->chave = dados.chave;
  nova->codigoCidadao = dados.codigoCidadao;
  nova->mesa = dados.mesa;
  strcpy(nova->servico, dados.servico);
  strcpy(nova->servidor, dados.servidor);
  nova->prox = NULL;
}

void registrarAtendimento(Atedimento **lista, Atedimento dados) {
  Atedimento *nova, *p, *q;
  nova = (Atedimento *) malloc(sizeof(Atedimento));
  if(nova) {
    copiaDadosDeAtendimento(nova, dados);
    p = NULL; q = *lista;
    while (q) {
      p = q;
      q = q->prox;
    }
    p->prox = nova;
  } else {
    fprintf(stderr, "Erro ao alocar memória.\n");
  }
}