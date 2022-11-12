typedef struct cidadao {
  int codigo, idade;
  char nome[30], estado[3];
  struct cidadao *prox;
} Cidadao;

Cidadao *buscaCidadao(Cidadao *lista, int codigo) {
  Cidadao *achado = lista;
  while(achado && achado->codigo != codigo) {
    achado=achado->prox;
  }
  return achado;
} 

void insereCidadaoEmOrdem(Cidadao **lista, Cidadao dados) {
  Cidadao *p, *q, *nova;
  p = NULL; q = *lista;
  while(q && q->codigo < dados.codigo) {
    p = q; 
    q = q->prox;
  }
  nova = (Cidadao *) malloc(sizeof(Cidadao));
  if(nova) {
    nova->codigo = dados.codigo;
    strcpy(nova->nome, dados.nome);
    nova->idade = dados.idade;
    strcpy(nova->estado, dados.estado);
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

void _mostraCidadaos(Cidadao *lista) {
  if(lista) {
    printf("Codigo: %d Nome: %s Idade: %d UF: %s\n", 
    lista->codigo,
    lista->nome,
    lista->idade,
    lista->estado
    );
    _mostraCidadaos(lista->prox);
  }
}

void carregaCidadaos(Cidadao **lista) {
  FILE *arq;
  Cidadao dados;
  int status;
  arq = fopen("cidadaos.data", "r");
  if(arq) {
    status = fscanf(
        arq,
        "%d;%[^;];%d;%[^\n]\n",
        &(dados.codigo),
        dados.nome,
        &(dados.idade),
        dados.estado
      );
    while(status != -1) {
      insereCidadaoEmOrdem(lista, dados);  
      status = fscanf(
        arq,
        "%d;%[^;];%d;%[^\n]\n",
        &(dados.codigo),
        dados.nome,
        &(dados.idade),
        dados.estado
      );
    }
    
    fclose(arq);
  } else {
    printf("Não foi possível abrir o arquivo cidadaos.data.\n");
  } 
}

void salvarCidadaos(Cidadao *lista) {
  FILE *arq;
  Cidadao *p;
  p = lista;
  arq = fopen("cidadaos.data", "w");
  if(arq) {
    while(p) {
      fprintf(
        arq,
        "%d;%s;%d;%s\n",
        p->codigo,
        p->nome,
        p->idade,
        p->estado
      );
      p = p->prox;
    }
    fclose(arq);
  } else {
    fprintf(stderr,"Não foi possível abrir o arquivo cidadaos.data.\n");
  } 
}

void excluiCadastro(Cidadao **lista, int codigo) {
  Cidadao *p, *q;
  p = NULL; q = *lista;
  while(q && q->codigo != codigo) {
    p = q;
    q = q->prox;
  }

  if (q != NULL) {
    if(p == NULL) {
      *lista = q->prox;
    } else {
      p->prox = q->prox;
    }
    free(q);
    printf("Cadastro excluido com sucesso.\n");
  } else {
    printf("Cidadao não encontrado.\n");
  }
}

void cidadaosCadastrados(Cidadao *lista) {
  FILE *arq;
  arq = fopen("cidadaos.csv", "w");
  if(arq) {
    while(lista) {
      fprintf(arq,"%d;%s;%d;%s\n", lista->codigo, lista->nome, lista->idade, lista->estado);
      lista = lista->prox;
    }
    fclose(arq);
  } else {
    fprintf(stderr, "Não foi possível abrir o arquivo cidadaos.csv.\n");
  }
}