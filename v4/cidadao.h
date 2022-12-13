typedef struct {
  int codigo, idade;
  char nome[30], uf[3];
} cidadao;

typedef struct celula {
  cidadao dados;
  struct celula *prox;
} celula;

void insereEmOrder(celula **lista, cidadao dados) {
  celula *nova = (celula *) malloc(sizeof(celula));
  if(nova) {
    celula *p, *q;
    nova->dados = dados;
    p = NULL; q = *lista;
    while(q && strcmp(dados.nome, q->dados.nome)) {
      p = q;
      q = q->prox;
    }
    nova->prox = q;
    if(p == NULL){
      *lista = nova;
    } else {
      p->prox = nova;
    }
  }
}

void carregaCidadaos(celula **lista) {
  FILE *arq = fopen("cidadaos.data", "r");
  if(arq) {
    cidadao dados;
    int status = fscanf(arq, "%d;%[^;];%d;%[^\n]\n",&(dados.codigo),dados.nome,&(dados.idade),dados.uf);
    while(status != -1) {
      insereEmOrder(lista, dados);
      status = fscanf(arq, "%d;%[^;];%d;%[^\n]\n",&(dados.codigo),dados.nome,&(dados.idade),dados.uf);
    }
    fclose(arq);
  } else {
    fprintf(stderr, "Erro ao abrir o arquivo 'cidadaos.data'.\n");
  }
}

void salvaCidadaos(celula *lista, char arquivo[]) {
  FILE *arq = fopen(arquivo, "w");
  if(arq) {
    while(lista) {
      fprintf(arq, "%d;%s;%d;%s\n",lista->dados.codigo,lista->dados.nome,lista->dados.idade,lista->dados.uf);
      lista = lista->prox;
    }
  } else {
    fprintf(stderr, "Erro ao abrir o arquivo '%s'.\n", arquivo);
  }
}
celula *buscaCidadao(celula *lista, int codigo) {
  if(lista == NULL) {
    return NULL;
  }
  if(lista->dados.codigo == codigo) {
    return lista;
  }
  return buscaCidadao(lista->prox, codigo);
}