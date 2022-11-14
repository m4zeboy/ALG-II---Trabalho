#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidadaos.h"
#include "senhas.h"

int main(void) {
  Cidadao *cidadaos, dados, *temp;
  char op,  op_sub, op_at;
  int contadorDeSenhas, sair;
  Senha senhaDados, *fila, *filaP, *proxima, *stemp;
  Atedimento atTemp, *documentos, *transporte, *moradia;
  /* sair é inicializado com zero pois, de início não tem senha na fila portanto o usuário PODE sair do programa. */
  sair = 0;
  cidadaos=NULL;
  fila=NULL;
  filaP=NULL;
  /* listas de atendimentos realizados */
  documentos = NULL;
  transporte = NULL;
  moradia = NULL;
  
  carregaCidadaos(&cidadaos);
  carregarContadorDeSenhas(&contadorDeSenhas);
  do {
    printf("1 CIDADAO\n2 GERAR SENHA\n3 ATENDIMENTO AO CIDADAO\n4 RELATORIOS\nS SAIR\n");
    scanf(" %c", &op);
    if(op == '1') {
      do {
        printf("1 CADASTRAR\n2 PESQUISAR POR CODIGO\n3 ATUALIZAR CADASTRO\n4 EXCLUIR CADASTRO\n0 VOLTAR\n");
        scanf(" %c", &op_sub);

        switch (op_sub) {
          case '1':
          /* 1. cadastrar */
            printf("Codigo: ");
            scanf("%d", &(dados.codigo));
            if(buscaCidadao(cidadaos, dados.codigo) != NULL) {
              fprintf(stderr, "Cidadao ja cadastrado com esse codigo.\n");
            } else {
              /* cadastrar cidadão novo*/
              printf("Nome: ");
              scanf(" %[^\n]", dados.nome);
              printf("Idade: ");
              scanf("%d", &(dados.idade));
              printf("Estado: ");
              scanf(" %[^\n]", dados.estado);
              insereCidadaoEmOrdem(&cidadaos, dados);
            }
            break;
          case '2':
          /* 2. pesquisar por codigo */
            printf("Codigo: ");
            scanf("%d", &(dados.codigo));
            temp = buscaCidadao(cidadaos, dados.codigo);
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
                  temp = buscaCidadao(cidadaos, dados.codigo);
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
                  temp = buscaCidadao(cidadaos, dados.codigo);
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
                  temp = buscaCidadao(cidadaos, dados.codigo);
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
            temp = buscaCidadao(cidadaos, dados.codigo);
            if(temp->idade >= 65) {
              /* verificar se o cidadão está na fila preferencial */
              stemp = buscaCidadaoNaFila(filaP, dados.codigo);
            } else {
              /* verificar se o cidadão está na fila */
              stemp = buscaCidadaoNaFila(fila, dados.codigo);
            }
            if(stemp == NULL) {
              /* Pode excluir */
              excluiCadastro(&cidadaos, dados.codigo);
            } else {
              /* Não pode excluir, o cidadao está esperando na fila. */
              fprintf(stderr,"Nao e possivel escluir o cadastro do cidadao, porque ele esta esperando na fila.\n");
            }
            break;
          default:
            if(op_sub != '0') {
              printf("Opção Inválida\n");
            }
            break;
        }
      } while(op_sub != '0');
    }
    if(op == '2') {
      printf("Codigo: ");
      scanf("%d", &(dados.codigo));
      temp = buscaCidadao(cidadaos, dados.codigo);
      if(temp) {
        contadorDeSenhas = contadorDeSenhas + 1;
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
        /* sair é incrementado */
        sair = sair + 1;
      } else {
        fprintf(stderr, "Cidadao nao encontrado.\n");
      }
    }
    if(op == '3') {
      printf("Nome do Servidor Publico: ");
      scanf(" %[^\n]", atTemp.servidor);
      printf("Mesa disponivel: ");
      scanf("%d", &(atTemp.mesa));
      if(filaP == NULL) {
        proxima = desenfileirar(&fila);
      } else {
        proxima = desenfileirar(&filaP);
      }
      atTemp.chave = proxima->chave;
      atTemp.codigoCidadao = proxima->codigoCidadao;
      strcpy(atTemp.servico, proxima->servico);
      printf("proxima senha: %d - servico: %s\n", proxima->chave, atTemp.servico);
      free(proxima);
      if(strcmp(atTemp.servico, "documentos") == 0) {
        /* salvar na lista de documentos */
        registrarAtendimento(&documentos, atTemp);
      } else if(strcmp(atTemp.servico, "moradia") == 0) {
        /* salvar na lista de moradia */
        registrarAtendimento(&moradia, atTemp);
      } else if(strcmp(atTemp.servico, "transporte") == 0) {
        /* salvar na lista de transporte */
        registrarAtendimento(&transporte, atTemp);
      }
      sair = sair - 1;
    }
    if(op == '4') {
      /* relatorios */
      do {
        printf("1 CIDADAOS CADASTRADOS\n2 CIDADAOS NAO ATENDIDOS\n3 ATENDIMENTOS REALIZADOS\n0 VOLTAR\n");
        scanf(" %c", &op_sub);
        switch (op_sub) {
        case '1':
        /* RELATORIO DE CIDADAOS CADASTRADOS */
          relatorioCidadaosCadastrados(cidadaos);
          printf("Confira o arquivo 'cidadaos.csv'.\n");
          break;
        case '2':
        /* RELATORIO DE CIDADAOS NAO ATENDIDOS */
          relatorioProximos(fila, filaP, cidadaos);
          printf("Confira o arquivo 'proximos.csv'.\n");
          break;
        case '3': 
        /* RELATORIO DE TODOS OS CIDADAOS ATENDIDOS */
          relatorioAtendimentos(documentos, "documentos.csv", cidadaos);
          relatorioAtendimentos(moradia, "moradia.csv", cidadaos);
          relatorioAtendimentos(transporte, "transporte.csv", cidadaos);
          printf("Confira o arquivos 'documentos.csv', 'moradia.csv' e 'transporte.csv'.\n");
        break;
        default:
          if(op_sub != '0') {
            fprintf(stderr, "Opção invalida.\n");
          }
          break;
        }
      } while(op_sub != '0');
    }
    if((op == 's' || op == 'S') && sair == 0) {
      break;
    }
  } while(1);
  /* persistencia dos dados */
  salvarCidadaos(cidadaos);
  salvarContadorDeSenhas(contadorDeSenhas);
  persistenciaAtendimentos(documentos, "documentos.data");
  persistenciaAtendimentos(moradia, "moradia.data");
  persistenciaAtendimentos(transporte, "transporte.data");
  return 0;
}