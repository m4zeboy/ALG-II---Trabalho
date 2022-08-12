#include <stdio.h>
#include <string.h>

typedef struct {
  int id;
  char nome[30];
  int idade;
  char UF[3];
} cidadao;

typedef struct {
  int id_cid;
  char tipo_atendimento[15];
  int senha;
} pedido;

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
  printf("\nCidadão Cadastrado\n");
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
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  } else {
    printf("\nCIDADÃO - %d\n", cidadaos[indice_cidadao].id);
    printf("NOME: %s\t IDADE: %d\t UF: %s\n\n", cidadaos[indice_cidadao].nome, cidadaos[indice_cidadao].idade, cidadaos[indice_cidadao].UF);
  }
}

void exclui_cidadao(cidadao cidadaos[500], int *tam, int id) {
  int indice_cidadao = busca_indice_cidadao(id, cidadaos, tam);
  int i;
  if(indice_cidadao == -1) {
    printf("\nCidadão não cadastrado.\n");
  } else {
    for(i=indice_cidadao;i-1<*tam;i++) {
      troca(&cidadaos[i], &cidadaos[i+1]); 
    }
    *tam = *tam -1;
    printf("\nCadastro Excluído\n");
  }
}

void atualiza_nome(cidadao cidadaos[500], int *tam, int id) {
  int i = busca_indice_cidadao(id, cidadaos, tam);
  printf("Digite novo nome: ");
  scanf(" %[^\n]", cidadaos[i].nome);
  printf("\nCadastro atualizado\n");
}

void atualiza_idade(cidadao cidadaos[500], int *tam, int id) {
  int i = busca_indice_cidadao(id, cidadaos, tam);
  printf("Digite nova idade: ");
  scanf("%d", &cidadaos[i].idade);
  printf("\nCadastro atualizado\n");

}

void atualiza_uf(cidadao cidadaos[500], int *tam, int id) {
  int i = busca_indice_cidadao(id, cidadaos, tam);
  printf("Digite nova UF: ");
  scanf(" %s", cidadaos[i].UF);
  printf("\nCadastro atualizado\n");

}

void print_menu() {
  printf("\nAtendimento ao Cidadao\n-----------------------\n");
  printf("1 - CIDADÃO\n");
  printf("2 - GERAR SENHA\n");
  printf("3 - ATENDIMENTO AO CIDADAO\n");
  printf("S - SAIR\n");
}

void print_menu_cidadao() {
  printf("\n1 - Cadastrar\n");
  printf("2 - Pesquisar por Código\n");
  printf("3 - Atualizar Cadastro\n");
  printf("4 - Excluir Cadastro\n");
  printf("0 - Voltar\n");
}

void print_menu_atualiza_cidadao() {
  printf("\nEscolha o campo a ser atualizado: \n");
  printf("1 - Nome\n");
  printf("2 - Idade\n");
  printf("1 - UF\n");
}

void gerar_senha(pedido fila[], int *qtd_fila, int id) {
  fila[*qtd_fila].senha = *qtd_fila;
  fila[*qtd_fila].id_cid = id;
  printf("\nInforme o tipo de atendimento: \nDOCUMENTOS\nTRANSPORTE\nMORADIA\n");
  scanf(" %s", fila[*qtd_fila].tipo_atendimento);
  *qtd_fila = *qtd_fila + 1;
}

int main(void) {
  cidadao cidadaos[500];
  pedido fila[50];
  pedido fila_p[50];

  int qtd_cidadao, id, indice, qtd_fila, qtd_fila_p, total_senhas;
  char op_cid, op, op_at_cid;
  qtd_cidadao = 0;

  qtd_fila = 0;
  qtd_fila_p = 0;
  total_senhas = 0;
  
  do {
    print_menu();
    scanf(" %c", &op);
    if(op == '1'){
      print_menu_cidadao();
      scanf(" %c", &op_cid);
      if(op_cid == '1'){
        cadastrar_cidadao(cidadaos, &qtd_cidadao);
      }
      if(op_cid == '2') {
        printf("\nInforme o código do cidadão: ");
        scanf("%d", &id);
        indice = busca_indice_cidadao(id, cidadaos, &qtd_cidadao);
        imprime_cidadao(cidadaos, indice);
      }
      if(op_cid == '3') {
        print_menu_atualiza_cidadao();
        scanf(" %c", &op_at_cid);
        switch (op_at_cid){
        case '1':
          printf("\nInforme o código do cidadão: ");
          scanf("%d", &id);
          atualiza_nome(cidadaos, &qtd_cidadao, id);
          break;
        case '2':
          printf("\nInforme o código do cidadão: ");
          scanf("%d", &id);
          atualiza_idade(cidadaos, &qtd_cidadao, id);
        break;
        case '3':
          printf("\nInforme o código do cidadão: ");
          scanf("%d", &id);
          atualiza_uf(cidadaos, &qtd_cidadao, id);
        break;
        default:
          break;
        }
      }
      if(op_cid == '4') {
        printf("\nInforme o código do cidadão a ser excluído: ");
        scanf(" %d", &id);
        exclui_cidadao(cidadaos, &qtd_cidadao, id);
      }
      if(op_cid == '0') {
        print_menu();
        scanf(" %c", &op);
      }
    }
    
    if(op == '2') {
      if(total_senhas == 100) {
        printf("\n Já existem 100 pessoas na fila. Até amanhã.\n");
      } else {
        printf("\nInforme o código do cidadão: ");
        scanf("%d", &id);
        indice = busca_indice_cidadao(id, cidadaos, &qtd_cidadao);
        if(cidadaos[indice].idade >=65) {
          gerar_senha(fila_p, &qtd_fila_p, id);
          total_senhas = total_senhas + 1;
          printf("\nPedido adcionado na fila não preferencial.\n");
          printf("\n%d\n", qtd_fila_p);
        } else {
          gerar_senha(fila, &qtd_fila, id);
          total_senhas = total_senhas + 1;
          printf("\nPedido adcionado na fila preferencial.\n");
          printf("\n%d\n", qtd_fila);
        }
      }
    }

    if((op == 's' || op == 'S') && (qtd_fila > -1 || qtd_fila_p > -1)) { 
      printf("\nAinda há pessoas na fila para serem atendidas.\n");
    }
   
  } while((op != 's' || op != 'S') && (qtd_fila > -1 || qtd_fila_p > -1));


  return 0;
}