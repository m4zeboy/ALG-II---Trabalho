#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidadaos.h"
#include "senhas.h"

int main(void) {
  Cidadao *lista, dados, *temp;
  char op,  op_sub, op_at;
  int contadorDeSenhas;
  Senha *senhaTemp, senhaDados, *fila, *filaP;
  lista=NULL;
  fila=NULL;
  filaP=NULL;
  carregaCidadaos(&lista);
  carregarContadorDeSenhas(&contadorDeSenhas);
  do {
    printf("1 CIDADAO\n2 GERAR SENHA\n3 ATENDIMENTO AO CIDADAO\n4 RELATORIOS\nS SAIR\n");
    scanf(" %c", &op);
    if(op == '1') {
      do {
        printf("1 CADASTRAR\n2 PESQUISAR POR CODIGO\n3 ATUALIZAR CADASTRO\n4 EXCLUIR CADASTRO\n0 VOLTAR\n");
        scanf(" %c", &op_sub);

        switch (op_sub){
          case '1':
          /* 1. cadastrar */
            printf("Codigo: ");
            scanf("%d", &(dados.codigo));
            if(buscaCidadao(lista, dados.codigo) != NULL) {
              fprintf(stderr, "Cidadao ja cadastrado com esse codigo.\n");
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
            break;
          case '2':
          /* 2. pesquisar por codigo */
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
              fprintf(stderr, "Cidadao nao encontrado.\n");
            }
            break;
          case '3':
          /* 3. atualizar cadasatro */
            do {
              printf("1 NOME\n2 IDADE\n3 UF\n0 VOLTAR\n");
              scanf(" %c", &op_at);
              switch (op_at) {
                case '1':
                  /* atualizar nome */
                  printf("Informe o codigo do cidadao: ");
                  scanf("%d", &(dados.codigo));
                  temp = buscaCidadao(lista, dados.codigo);
                  if(temp != NULL) {
                    printf("Informe o novo nome: ");
                    scanf(" %[^\n]", dados.nome);
                    strcpy(temp->nome, dados.nome);
                    printf("Nome atualizado com sucesso.\n");
                  } else {
                    printf("Cidadao nao encontrado.\n");
                  }
                  break;
                case '2': 
                  /* atualizar idade */
                  printf("Informe o codigo do cidadao: ");
                  scanf("%d", &(dados.codigo));
                  temp = buscaCidadao(lista, dados.codigo);
                  if(temp != NULL) {
                    printf("Informe a nova idade: ");
                    scanf("%d", &(dados.idade));
                    temp->idade = dados.idade;
                    printf("Idadae atualizada com sucesso.\n");
                  } else {
                    fprintf(stderr, "Cidadao nao encontrado.\n");
                  }
                break;   
                case '3':
                  /* atualizar estado */
                  printf("Informe o codigo do cidadao: ");
                  scanf("%d", &(dados.codigo));
                  temp = buscaCidadao(lista, dados.codigo);
                  if(temp != NULL) {
                    printf("Informe o novo estado: ");
                    scanf(" %[^\n]", dados.estado);
                    strcpy(temp->estado, dados.estado);
                    printf("Estado atualizado com sucesso.\n");
                  } else {
                    fprintf(stderr, "Cidadao nao encontrado.\n");
                  }
                break;             
                default:
                  printf("Opcao Invalida\n");
                  break;
              }
            } while(op_at != '0');
            break;
          case '4':
          /* excluir cadastro */
            printf("Informe o codigo do cidadao: ");
            scanf("%d", &(dados.codigo));
            excluiCadastro(&lista, dados.codigo);
            break;
          default:
            break;
        }
      } while(op_sub != '0');
    }

    if(op == '2') {
      printf("Codigo: ");
      scanf("%d", &(dados.codigo));
      temp = buscaCidadao(lista, dados.codigo);
      if(temp) {
        gerarSenha(&contadorDeSenhas);
        senhaDados.chave = contadorDeSenhas;
        senhaDados.codigoCidadao = dados.codigo;
        printf("Informe o servico requisitado: ");
        scanf(" %s", senhaDados.servico);
        /* verificar em qual fila colocar */
        if(temp->idade >= 65) {
          printf("FILA PREFERENCIAL\n");
          enfileirar(&filaP, senhaDados);
        } else {
          printf("FILA NAO PREFERENCIAL\n");
          enfileirar(&fila, senhaDados);
        }
      } else {
        fprintf(stderr, "Cidadao nao encontrado.\n");
      }
    }
  
    if(op == '4') {
      do {

        printf("1 CIDADAOS CADASTRADOS\n2 CIDADAOS NAO ATENDIDOS\n3 ATENDIMENTOS REALIZADOS\n0 VOLTAR");
        scanf(" %c", &op_sub);
        switch (op_sub)
        {
        case '1':
          cidadaosCadastrados(lista);
          printf("Confira o arquivo 'cidadaos.csv'.\n");
          break;
        
        default:
          if(op_sub != 0) {
            fprintf(stderr, "Opção invalida.\n");
          }
          break;
        }
      } while(op_sub != '0');
      /* relatorios */
      mostrarFila(filaP);
      mostrarFila(fila);
    }
  } while(op != 's' && op != 'S');
  salvarCidadaos(lista);
  salvarContadorDeSenhas(contadorDeSenhas);
  return 0;
}