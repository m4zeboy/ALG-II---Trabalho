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

/* Recebe os dados da senha e insere no fim da lista */
void enfileirar(Senha **fila, Senha dados);
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

/* Recebe o pontiero do contador de senhas, abre o arquivo e lê o número que está gravado no arquivo, se o arquivo estiver vazio, o contador recebe o valor 0*/
void carregarContadorDeSenhas(int *contadorDeSenhas);
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

/* Salva o contador de senhas no arquivo */
void salvarContadorDeSenhas(int contadorDeSenhas);
void salvarContadorDeSenhas(int contadorDeSenhas) {
  FILE *arq;
  arq = fopen("contadorDeSenhas.data", "w");
  if(arq) {
    fprintf(arq, "%d", contadorDeSenhas);
  } else {
    printf("Falaha ao abrir o arquivo 'contadorDeSenhas.data'.\n");
  }
}

/* Recebe os ponteiros para o início das duas filas e o ponteiro para o começo da lista de cidadãos. abre o arquivo proximos.csv e percorre cada fila, em cada iteração busca o cidadao e escreve os dados. */
void relatorioProximos(Senha *fila, Senha *filaP, Cidadao *lista);
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

/* Recebe o ponteiro para o começo da fila, remove o primeiro elemento e o retorna. a liberação de memória é feito na função principal */
Senha *desenfileirar(Senha **fila);
Senha *desenfileirar(Senha **fila) {
  /* desenfileirar o primeiro elemento */
  Senha *remove;
  remove = *fila;
  *fila = (*fila)->prox;
  return remove;
}

/* Função recursiva que recebe uma fila e um código de cidadão e devolve o ponteiro caso encontre uma senha com o campo codigoCidadão correspondete ao parâmetro código informado, se não retona NULL */
Senha *buscaCidadaoNaFila(Senha *fila, int codigo) {
Senha *buscaCidadaoNaFila(Senha *fila, int codigo);
  if(fila == NULL)
    return NULL;
  if(fila->codigoCidadao == codigo)
    return fila;
  return buscaCidadaoNaFila(fila->prox, codigo);
} 

/* Recebe a lista de atendimento e os dados do atendimento. cria um atendimento, copia os dados e insere na lista ordenado pela senha (campo chave) */
void registrarAtendimento(Atedimento **lista, Atedimento dados);
void registrarAtendimento(Atedimento **lista, Atedimento dados) {
  /* A função principal fica responsável com a lógica de escolher a lista de atendimento (documentos, moradia, transporte) */
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

/* A função gera o relátorio dos atendimentos realizados. Recebe a lista de atendimentos, o nome do arquivo e lista de cidadãos. abre o arquivo, percorre a lista, a cada iteração busca as informações do respectivo cidadão e imprime no arquivo  */
void relatorioAtendimentos(Atedimento *lista, char nomeDoArquivo[], Cidadao *listaCidadaos);
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

/* Muito parecida com a função anterior, só não recebe a lista de cidadãos, pois guarda no arquivo somente os dados da struct Atendimento. Preserva os dados das execuções anteriores pois não usa a flag write "w", mas usa a flag append "a"*/
void salvarAtendimentos(Atedimento *lista, char nomeDoArquivo[]);
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