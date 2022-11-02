#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidadaos.h"


int main(void) {
  Cidadao *lista, dados, *temp;
  char op, op_sub;
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
  _mostraCidadaos(lista);
  salvarCidadaos(lista);
  return 0;
}