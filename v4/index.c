#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidadao.h"

int main(void) {
  celula *lista = NULL;
  char op;
  carregaCidadaos(&lista);
  do {
    system("cls");
    printf("1. CIDADAOS\nS. SAIR\n");
    scanf(" %c", &op);
    if(op == '1') {
      char op_cid;
      cidadao dados;
      system("cls");
      do {
        printf("1. CADASTRAR\n2. PESQUISAR POR CODIGO\n3. EXCLUIR CADASTRO\n0. VOLTAR\n");
        scanf(" %c", &op_cid);
        if(op_cid == '1') {
          system("cls");
          printf("Codigo: ");
          scanf("%d", &(dados.codigo));
          if(buscaCidadao(lista, dados.codigo)) {
            fprintf(stderr,"Cidadao ja existe com esse codigo.\n");
          } else {
            printf("Nome: ");
            scanf(" %[^\n]", dados.nome);
            printf("Idade: ");
            scanf("%d", &(dados.idade));
            printf("UF: ");
            scanf(" %[^\n]", dados.uf);
            insereEmOrder(&lista, dados);
          }
        } else if(op_cid == '2') {
        celula *temp;
        int codigo;
        system("cls");
        printf("Codigo: ");
        scanf("%d", &codigo);
        temp = buscaCidadao(lista, codigo);
        if(temp == NULL) {
          fprintf(stderr,"Cidadao nao encontrado.\n");
        } else {
          printf("Codigo: %d\tNome: %s\tIdade: %d\tUF: %s\n", temp->dados.codigo, temp->dados.nome, temp->dados.idade, temp->dados.uf);
        }
      } else if(op_cid == '3') {
        int codigo;
        printf("Codigo: ");
        scanf("%d", &codigo);
        buscaRemove(&lista, codigo);
      }

    } while(op_cid != '0');
    } else if(op == 'S' || op == 's') {
      break;
    }
  } while(1);
  salvaCidadaos(lista, "cidadaos.data");
  return 0;
}