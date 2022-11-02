#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("Não foi possível abrir o arquivo cidadaos.data.\n");
  } 
}

int main(void) {
  Cidadao *lista, dados, *temp;
  char op,  op_sub;
  lista=NULL;
  carregaCidadaos(&lista);
  do {
    printf("1 CIDADAO\n2 GERAR SENHA\n3 ATENDIMENTO AO CIDADAO\n4 RELATORIOS\nS SAIR\n");
    scanf(" %c", &op);
    if(op == '1') {
      do {
        printf("1 CADASTRAR\n2 PESQUISAR POR CODIGO\n3 ATUALIZAR CADASTRO\n4 EXCLUIR CADASTRO\n0 VOLTAR\n");
        scanf(" %c", &op_sub);

        /* 1. cadastrar */
        if(op_sub == '1') {
          printf("Codigo: ");
          scanf("%d", &(dados.codigo));
          if(buscaCidadao(lista, dados.codigo) != NULL) {
            printf("Cidadao ja cadastrado com esse codigo.\n");
          } else {
            /* cadastrar cidadão novo*/
            printf("Nome: ");
            scanf(" %[^\n]", dados.nome);

            printf("Idade: ");
            scanf("%d", &(dados.idade));

            printf("Estado: ");
            scanf(" %[^\n]", dados.estado);

            insereCidadaoEmOrdem(&lista, dados);
          }
        }

        /* 2. pesquisar por codigo */
        if(op_sub == '2') {
          printf("Codigo: ");
          scanf("%d", &(dados.codigo));
          temp = buscaCidadao(lista, dados.codigo);
          if(temp != NULL) {
            printf("Codigo: %d Nome: %s Idade: %d UF: %s\n", 
            temp->codigo,
            temp->nome,
            temp->idade,
            temp->estado
          );
          } else {
            printf("Cidadao não encontrado.\n");
          }
        }
      } while(op_sub != '0');
    }

  } while(op != 's' && op != 'S');
  salvarCidadaos(lista);
  return 0;
}