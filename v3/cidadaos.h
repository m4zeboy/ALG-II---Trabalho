/* Dados de cadastro do cidadao: código, nome, idade, estado. */
typedef struct cidadao {
  int codigo, idade;
  char nome[30], estado[3];
  struct cidadao *prox;
} Cidadao;

/* Recebe um código de um possível cidadão, procura na lista e devolve o ponteiro para o cidadao */
Cidadao *buscaCidadao(Cidadao *lista, int codigo);
Cidadao *buscaCidadao(Cidadao *lista, int codigo) {
  Cidadao *achado = lista;
  while(achado && achado->codigo != codigo) {
    achado=achado->prox;
  }
  return achado;
} 

/* Recebe os dados do cidadão e insere na lista ordenado pelo código. Essa função não tem a responsabilidade de verificar se o código informado já existe na lista, essa parte fica com a função principal */
void insereCidadaoEmOrdem(Cidadao **lista, Cidadao dados);
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

/* Recebe uma Lista vazia, abre o arquivo cidadaos.data, percorre o mesmo e insere na lista */
void carregaCidadaos(Cidadao **lista);
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
    fprintf(stderr,"Não foi possível abrir o arquivo cidadaos.data.\n");
  } 
}

/* Recebe o código de um possivel cidadão e exclui o cadastro (ajusta os ponteiros e libera memoria) */
void excluiCadastro(Cidadao **lista, int codigo);
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

/* Recebe a lista de cidadãos, abre o arquivo informado por parâmetro, percorre o mesmo e escreve um registro por linha */
void salvarCidadaos(Cidadao *lista, char *nomeDoArquivo);
void salvarCidadaos(Cidadao *lista, char *nomeDoArquivo) {
  FILE *arq;
  arq = fopen(nomeDoArquivo, "w");
  if(arq) {
    while(lista) {
      fprintf(arq,"%d;%s;%d;%s\n", lista->codigo, lista->nome, lista->idade, lista->estado);
      lista = lista->prox;
    }
    fclose(arq);
  } else {
    fprintf(stderr, "Não foi possível abrir o arquivo '%s'.\n", nomeDoArquivo);
  }
}