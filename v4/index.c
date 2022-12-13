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
    printf("1. CIDADAOS\n");
    scanf(" %c", &op);
    if(op == '1') {
      char op_cid;
      cidadao dados;
      system("cls");
      printf("1. CADASTRAR\n");
      scanf(" %c", &op_cid);
      if(op_cid == '1') {
        printf("Código: ");
        scanf("%d", &(dados.codigo));
        if(buscaCidadao(lista, dados.codigo)) {
          fprintf(stderr,"Cidadão já existe com esse código.\n");
        } else {
          
        }
      }
    } else if(op == 's') {
      break;
    }
  } while(1);
  salvaCidadaos(lista, "cidadaos.data");
  return 0;
}