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
    fclose(arq);
  } else {
    fprintf(stderr, "Falaha ao abrir o arquivo 'contadorDeSenhas.data'.\n");
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

void registrarAtendimento(Atedimento **lista, Atedimento dados) {
  /* Essa função registra o atendimento na respectiva lista, documentos, transporte ou moradia, inserindo o novo registro em ordem pela senha (chave) */
  Atedimento *nova, *p, *q;
  nova = (Atedimento *) malloc(sizeof(Atedimento));
  if(nova) {
    
    nova->chave = dados.chave;
    nova->codigoCidadao = dados.codigoCidadao;
    nova->mesa = dados.mesa;
    strcpy(nova->servico, dados.servico);
    strcpy(nova->servidor, dados.servidor);

    p = NULL; q = *lista;
    while (q) {
      p = q;
      q = q->prox;
    }
    nova->prox = q;
    if(p == NULL) {
      *lista = nova;
    } else {
      p->prox = nova;
    }
  } else {
    fprintf(stderr, "Erro ao alocar memória.\n");
  }
}

void relatorioAtendimentos(Atedimento *lista, char nomeDoArquivo[], Cidadao *listaCidadaos) {
  FILE *arq;
  Atedimento *p;
  Cidadao *temp;
  arq = fopen(nomeDoArquivo, "a");
  if(arq) {
    p = lista;
    while(p) {
      /* buscar os dados do ciadao */
      temp = buscaCidadao(listaCidadaos, p->codigoCidadao);
      /* chave;nome;idade;nome_do_servidor;mesa*/
      fprintf(arq, "%d;%s;%d;%s;%d\n", p->chave,temp->nome,temp->idade,p->servidor, p->mesa);
      p = p->prox;
    }
    fclose(arq);
  } else {
    fprintf(stderr, "Falaha ao abrir o arquivo '%s'.\n", nomeDoArquivo);
  }
}

void salvarAtendimentos(Atedimento *lista, char nomeDoArquivo[]) {
  FILE *arq;
  Atedimento *p;
  arq = fopen(nomeDoArquivo, "a");
  if(arq) {
  p = lista;
  while(p) {
    /* chave;codigo_cidadao;servico;servidor;mesa*/
    fprintf(arq, "%d;%d;%s;%s;%d\n",p->chave,p->codigoCidadao,p->servico,p->servidor,p->mesa);
    p = p->prox;
  }
  fclose(arq);
  } else {
    fprintf(stderr, "Falaha ao abrir o arquivo '%s'.\n", nomeDoArquivo);
  }
}