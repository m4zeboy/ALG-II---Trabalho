#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidadaos.h"
#include "senhas.h"

/* Desinged by Moisés Silva de Azevedo, São Paulo */

int main(void) {
  Cidadao *cidadaos, dados, *temp;
  char op,  op_sub, op_at;
  int contadorDeSenhas, sair;
  Senha senhaDados, *fila, *filaP, *proxima, *stemp;
  Atedimento atTemp, *documentos, *transporte, *moradia;
  /* Sair é inicializado com zero pois, de início não tem senha na fila portanto o usuário PODE sair do programa. */
  sair = 0;
  cidadaos=NULL;
  fila=NULL;
  filaP=NULL;
  /* Inicialização listas de atendimentos realizados */
  documentos = NULL;
  transporte = NULL;
  moradia = NULL;
  /* Carregar dados de execuções anteriores */
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
          /* 1. Cadastrar */
            printf("Codigo: ");
            scanf("%d", &(dados.codigo));
            if(buscaCidadao(cidadaos, dados.codigo) != NULL) {
              fprintf(stderr, "Cidadao ja cadastrado com esse codigo.\n");
            } else {
              /* Cadastrar cidadão */
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
          /* 2. Pesquisar por codigo */
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
          /* 3. Atualizar cadasatro */
            do {
              printf("1 NOME\n2 IDADE\n3 UF\n0 VOLTAR\n");
              scanf(" %c", &op_at);
              switch (op_at) {
                case '1':
                  /* Atualizar nome */
                  printf("Informe o codigo do cidadao: ");
                  scanf("%d", &(dados.codigo));
                  temp = buscaCidadao(cidadaos, dados.codigo);
                  if(temp != NULL) {
                    printf("Informe o novo nome: ");
                    scanf(" %[^\n]", dados.nome);
                    strcpy(temp->nome, dados.nome);
                    printf("Nome atualizado com sucesso.\n");
                  } else {
                   fprintf(stderr,"Cidadao nao encontrado.\n");
                  }
                  break;
                case '2': 
                  /* Atualizar idade */
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
                  /* Atualizar estado */
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
                  fprintf(stderr,"Opcao Invalida\n");
                  break;
              }
            } while(op_at != '0');
            break;
          case '4':
          /* Excluir cadastro */
            printf("Informe o codigo do cidadao: ");
            scanf("%d", &(dados.codigo));
            temp = buscaCidadao(cidadaos, dados.codigo);
            if(temp->idade >= 65) {
              /* Verificar se o cidadão está na fila preferencial */
              stemp = buscaCidadaoNaFila(filaP, dados.codigo);
            } else {
              /* Verificar se o cidadão está na fila não preferencial */
              stemp = buscaCidadaoNaFila(fila, dados.codigo);
            }
            if(stemp == NULL) {
              /* Pode excluir */
              excluiCadastro(&cidadaos, dados.codigo);
            } else {
              /* Não pode excluir, o cidadao está esperando na fila. */
              fprintf(stderr,"Nao e possivel excluir o cadastro do cidadao, porque ele esta esperando na fila.\n");
            }
            break;
          default:
            if(op_sub != '0') {
              printf("Opção Inválida\n");
            }
            break;
        }
      } while(op_sub != '0');
    } else if(op == '2') {
      printf("Codigo: ");
      scanf("%d", &(dados.codigo));
      temp = buscaCidadao(cidadaos, dados.codigo);
      if(temp) {
        contadorDeSenhas = contadorDeSenhas + 1;
        senhaDados.chave = contadorDeSenhas;
        senhaDados.codigoCidadao = dados.codigo;
        printf("Informe o servico requisitado: ");
        scanf(" %s", senhaDados.servico);
        /* Verificar se o cidadao é preferencial ou não */
        if(temp->idade >= 65) {
          printf("Senha inserida na Fila Preferencial\n");
          enfileirar(&filaP, senhaDados);
        } else {
          printf("Senha inserida na Fila Nao Preferencial\n");
          enfileirar(&fila, senhaDados);
        }
        /* Sair é incrementado */
        sair = sair + 1;
      } else {
        fprintf(stderr, "Cidadao nao encontrado.\n");
      }
    } else if(op == '3') {
      printf("Nome do Servidor Publico: ");
      scanf(" %[^\n]", atTemp.servidor);
      printf("Mesa disponivel: ");
      scanf("%d", &(atTemp.mesa));
      if(filaP == NULL) {
        proxima = desenfileirar(&fila);
      } else {
        proxima = desenfileirar(&filaP);
      }
      /* Salvar dados do atendimento */
      atTemp.chave = proxima->chave;
      atTemp.codigoCidadao = proxima->codigoCidadao;
      strcpy(atTemp.servico, proxima->servico);
      printf("Proxima Senha: %d - Servico: %s - Mesa: %d\n", proxima->chave, atTemp.servico, atTemp.mesa);
      free(proxima);
      /* Registrar o atendimento na lista de acordo com o servico requisitado */
      if(strcmp(atTemp.servico, "documentos") == 0) {
        /* Salvar na lista de documentos */
        registrarAtendimento(&documentos, atTemp);
      } else if(strcmp(atTemp.servico, "moradia") == 0) {
        /* Salvar na lista de moradia */
        registrarAtendimento(&moradia, atTemp);
      } else if(strcmp(atTemp.servico, "transporte") == 0) {
        /* Salvar na lista de transporte */
        registrarAtendimento(&transporte, atTemp);
      }
      sair = sair - 1;
    } else if(op == '4') {
      /* Relatorios */
      do {
        printf("1 CIDADAOS CADASTRADOS\n2 CIDADAOS NAO ATENDIDOS\n3 ATENDIMENTOS REALIZADOS\n0 VOLTAR\n");
        scanf(" %c", &op_sub);
        switch (op_sub) {
        case '1':
        /* Relatório de cidadãos cadastrados */
          salvarCidadaos(cidadaos, "cidadaos.csv");
          printf("Confira o arquivo 'cidadaos.csv'.\n");
          break;
        case '2':
        /* Relatório de cidadãos não atendidos */
          relatorioProximos(fila, filaP, cidadaos);
          printf("Confira o arquivo 'proximos.csv'.\n");
          break;
        case '3': 
        /* Relatório de todos os cidadãos atendidos */
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
    } else if(op == 's' || op == 'S') {
      if(sair == 0) {
        break;
      } else {
        printf("Ainda tem cidadaos na fila.\n");
      }
    } else {
      fprintf(stderr, "Opção inválida.\n");
    }
  } while(1);
  /* Persistencia dos dados */
  salvarCidadaos(cidadaos, "cidadaos.data");
  salvarContadorDeSenhas(contadorDeSenhas);
  salvarAtendimentos(documentos, "documentos.data");
  salvarAtendimentos(moradia, "moradia.data");
  salvarAtendimentos(transporte, "transporte.data");
  return 0;
}