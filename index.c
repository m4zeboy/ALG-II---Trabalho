#include <stdio.h>
#include <string.h>

typedef struct {
  int id;
  char nome[30];
  int idade;
  char UF[3];
} cidadao;

void troca(cidadao *a, cidadao *b) {
  cidadao aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void cadastrar_cidadao(cidadao cidadadaos[500], int *tam) {
  printf("\nCADASTRAR CIDADÃO\n");
  printf("ID: \n");
  scanf("%d", &cidadadaos[*tam].id);
  printf("NOME: \n");
  scanf(" %[^\n]", cidadadaos[*tam].nome);
  printf("IDADE: \n");
  scanf("%d", &cidadadaos[*tam].idade);
  printf("UF: \n");
  scanf("%s", cidadadaos[*tam].UF);
  *tam=*tam+1;
}

int busca_indice_cidadao(int id, cidadao cidadaos[500], int *tam) {
  int i, indice_cidadao;
  indice_cidadao = -1;
  for(i=0;i<*tam;i++) {
    if(cidadaos[i].id == id) {
      indice_cidadao = i;
    }
  }
  return indice_cidadao;
}

void imprime_cidadao(cidadao cidadaos[500], int indice_cidadao) {
  if(indice_cidadao == -1) {
    printf("Cidadão não cadastrado.");
  } else {
    printf("CIDADÃO - %d\n", cidadaos[indice_cidadao].id);
    printf("NOME: %s\t IDADE: %d\t UF: %s\n", cidadaos[indice_cidadao].nome, cidadaos[indice_cidadao].idade, cidadaos[indice_cidadao].UF);
  }
}

void exclui_cidadao(cidadao cidadaos[500], int *tam, int id) {
  int indice_cidadao = busca_indice_cidadao(id, cidadaos, tam);
  int i;
  if(indice_cidadao == -1) {
    printf("Cidadão não cadastrado.");
  } else {
    for(i=indice_cidadao;i-1<*tam;i++) {
      troca(&cidadaos[i], &cidadaos[i+1]); 
    }
    *tam = *tam -1;
  }
}

void atualiza_nome(cidadao cidadaos[500], int *tam, int id) {
  int i = busca_indice_cidadao(id, cidadaos, tam);
  printf("Digite novo nome: ");
  scanf(" %[^\n]", cidadaos[i].nome);
}

void atualiza_idade(cidadao cidadaos[500], int *tam, int id) {
  int i = busca_indice_cidadao(id, cidadaos, tam);
  printf("Digite nova idade: ");
  scanf("%d", &cidadaos[i].idade);
}

void atualiza_uf(cidadao cidadaos[500], int *tam, int id) {
  int i = busca_indice_cidadao(id, cidadaos, tam);
  printf("Digite nova UF: ");
  scanf(" %s", cidadaos[i].UF);
}

int main(void) {
  cidadao cidadaos[500];
  int qtd_cidadao, id, indice_cidadadao;
  int cidadao, gerar_senha, atend, sair;
  char op[20];
  char op_cidadao[20];
  int cadastrar, excluir, imprime, atualiza, at_nome, at_idade, at_uf;
  qtd_cidadao = 0;
  do {
    scanf(" %[^\n]", op);
    cidadao = strcmp(op, "cidadao");
    atend = strcmp(op, "atendimento");
    gerar_senha = strcmp(op, "gerar senha");
    sair = strcmp(op, "sair");

    if(cidadao == 0) {
      scanf(" %[^\n]", op_cidadao);
      cadastrar = strcmp(op_cidadao, "cadastrar");
      excluir = strcmp(op_cidadao, "excluir");
      imprime = strcmp(op_cidadao, "imprime");
      atualiza = strcmp(op_cidadao, "atualiza");
    }

  } while(sair != 0);


  return 0;
}