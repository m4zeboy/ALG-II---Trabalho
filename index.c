#include <stdio.h>
#include <string.h>

typedef struct
{
  int id;
  char nome[30];
  int idade;
  char UF[3];
} cidadao;

typedef struct
{
  int id_cid;
  char tipo_atendimento;
  int senha;
} atendimento_solicitado;

typedef struct
{
  char servidor[30];
  int senha;
  char tipo_atendimento;
  int id_cid;
  int mesa;
} atendimento;

int busca_indice_cidadao(cidadao cidadaos[500], int *tam, int id)
{
  int i, indice_cidadao;
  indice_cidadao = -1;
  for (i = 0; i < *tam; i++)
  {
    if (cidadaos[i].id == id)
    {
      indice_cidadao = i;
    }
  }
  return indice_cidadao;
}

void troca_cidadao(cidadao *a, cidadao *b)
{
  cidadao aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void cadastrar_cidadao(cidadao cidadaos[500], int *tam)
{
  int id, cidadao_ja_existe;
  printf("\nCADASTRAR CIDADÃO\n");
  printf("ID: ");
  scanf("%d", &id);
  cidadao_ja_existe = busca_indice_cidadao(cidadaos, tam, id);
  if (cidadao_ja_existe != -1)
  {
    printf("\nERRO. Já existe um cidadão cadastrado com esse mesmo ID.\n");
  }
  else
  {
    cidadaos[*tam].id = id;
    printf("\nNOME: ");
    scanf(" %[^\n]", cidadaos[*tam].nome);
    printf("\nIDADE: ");
    scanf("%d", &cidadaos[*tam].idade);
    printf("\nUF: ");
    scanf("%s", cidadaos[*tam].UF);
    *tam = *tam + 1;
    printf("\nCidadão Cadastrado\n");
  }
}

void imprime_cidadao(cidadao cidadaos[500], int *tam)
{
  int id, indice_cidadao;
  printf("\nInforme o ID do cidadão: ");
  scanf("%d", &id);
  indice_cidadao = busca_indice_cidadao(cidadaos, tam, id);
  if (indice_cidadao == -1)
  {
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  }
  else
  {
    printf("\nCIDADÃO - %d\n", cidadaos[indice_cidadao].id);
    printf("NOME: %s\t IDADE: %d\t UF: %s\n\n", cidadaos[indice_cidadao].nome, cidadaos[indice_cidadao].idade, cidadaos[indice_cidadao].UF);
  }
}

void exclui_cidadao(cidadao cidadaos[500], int *tam)
{
  int indice_cidadao, i, id;
  printf("\nInforme o ID do Cidadão: ");
  scanf("%d", &id);
  indice_cidadao = busca_indice_cidadao(cidadaos, tam, id);
  if (indice_cidadao == -1)
  {
    printf("\nCidadão não cadastrado.\n");
  }
  else
  {
    for (i = indice_cidadao; i - 1 < *tam; i++)
    {
      troca_cidadao(&cidadaos[i], &cidadaos[i + 1]);
    }
    *tam = *tam - 1;
    printf("\nCadastro Excluído\n");
  }
}

void atualiza_nome(cidadao cidadaos[500], int *tam)
{
  int i, id;
  printf("\nInforme o ID do cidadão: ");
  scanf("%d", &id);
  i = busca_indice_cidadao(cidadaos, tam, id);
  if(i!= -1) {
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  } else {
    printf("\nDigite novo nome: ");
    scanf(" %[^\n]", cidadaos[i].nome);
    printf("\nCadastro atualizado\n");
  }
}

void atualiza_idade(cidadao cidadaos[500], int *tam)
{
  int i, id;
  printf("\nInforme o ID do cidadão: ");
  scanf("%d", &id);
  i = busca_indice_cidadao(cidadaos, tam, id);
  if(i==-1) {
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  } else {
    printf("Digite nova idade: ");
    scanf("%d", &cidadaos[i].idade);
    printf("\nCadastro atualizado\n");
  }
}

void atualiza_uf(cidadao cidadaos[500], int *tam)
{
  int i, id;
  printf("\nInforme o ID do cidadão: ");
  scanf("%d", &id);
  i = busca_indice_cidadao(cidadaos, tam, id);
  if(i==-1) {
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  } else {
    printf("Digite nova UF: ");
    scanf(" %s", cidadaos[i].UF);
    printf("\nCadastro atualizado\n");
  }
}

void print_menu()
{
  printf("\nAtendimento ao Cidadao\n-----------------------\n");
  printf("1 - CIDADÃO\n");
  printf("2 - GERAR SENHA\n");
  printf("3 - ATENDIMENTO AO CIDADAO\n");
  printf("S - SAIR\n");
}

void print_menu_cidadao()
{
  printf("\n1 - Cadastrar\n");
  printf("2 - Pesquisar por Código\n");
  printf("3 - Atualizar Cadastro\n");
  printf("4 - Excluir Cadastro\n");
  printf("0 - Voltar\n");
}

void print_menu_atualiza_cidadao()
{
  printf("\nEscolha o campo a ser atualizado: \n");
  printf("1 - Nome\n");
  printf("2 - Idade\n");
  printf("3 - UF\n");
}

void gerar_senha(atendimento_solicitado fila[], int *qtd_fila, int id, int *senhas)
{
  fila[*qtd_fila].senha = *senhas + 1;
  fila[*qtd_fila].id_cid = id;
  printf("\nInforme o tipo de atendimento: \nD - DOCUMENTOS\nT - TRANSPORTE\nM - MORADIA\n");
  scanf(" %c", &fila[*qtd_fila].tipo_atendimento);
  *qtd_fila = *qtd_fila + 1;
  *senhas = *senhas + 1;
}

void inicia_atendimento(atendimento atendimentos[], int *tam, atendimento_solicitado fila[])
{
  printf("\nDiga o nome do servidor: ");
  scanf(" %[^\n]", atendimentos[*tam].servidor);
  printf("\nInforme o número da mesa: ");
  scanf("%d", &atendimentos[*tam].mesa);
  atendimentos[*tam].senha = fila[0].senha;
  atendimentos[*tam].id_cid = fila[0].id_cid;
  atendimentos[*tam].tipo_atendimento = fila[0].tipo_atendimento;
  *tam = *tam + 1;
}

void fecha_atendimento(atendimento_solicitado fila[], int *tam)
{
  int i;
  for (i = 0; i < *tam - 1; i++)
  {
    fila[i] = fila[i + 1];
  }
  *tam = *tam - 1;
}

void imprime_atendimento(atendimento at, char nome[30])
{
  printf("Senha: %d - Cidadão: %s - Servidor: %s - Mesa: %d\n", at.senha, nome, at.servidor, at.mesa);
}

void lista_atendimento_fechados(atendimento atendimentos[], int tam, cidadao cidadaos[], int *tam_cid)
{
  int i, indice_cidadao;
  printf("\nAtendimentos Realizados\n");
  printf("DOCUMENTOS: \n");
  for (i = 0; i < tam; i++)
  {
    indice_cidadao = busca_indice_cidadao(cidadaos, tam_cid, atendimentos[i].id_cid);
    if (atendimentos[i].tipo_atendimento == 'D')
    {
      imprime_atendimento(atendimentos[i], cidadaos[indice_cidadao].nome);
    }
  }
  printf("\nTRANSPORTE: \n");
  for (i = 0; i < tam; i++)
  {
    indice_cidadao = busca_indice_cidadao(cidadaos, tam_cid, atendimentos[i].id_cid);
    if (atendimentos[i].tipo_atendimento == 'T')
    {
      imprime_atendimento(atendimentos[i], cidadaos[indice_cidadao].nome);
    }
  }
  printf("\nMORADIA: \n");
  for (i = 0; i < tam; i++)
  {
    indice_cidadao = busca_indice_cidadao(cidadaos, tam_cid, atendimentos[i].id_cid);
    if (atendimentos[i].tipo_atendimento == 'M')
    {
      imprime_atendimento(atendimentos[i], cidadaos[indice_cidadao].nome);
    }
  }
}

int main(void)
{
  cidadao cidadaos[500];
  atendimento_solicitado fila[50], fila_p[50];
  atendimento atendimentos[100];
  int tam_cid, tam_fila, tam_fila_p, tam_at, tem_pessoa_para_ser_atendida, senhas, id, indice_cidadao;
  char op, op_cid, op_cid_at;
  tam_cid = 0;
  tam_fila = 0;
  tam_fila_p = 0;
  senhas = 0;
  tam_at = 0;
  tem_pessoa_para_ser_atendida = 0;

  do
  {
    print_menu();
    scanf(" %c", &op);
    if (op == '1')
    {
      print_menu_cidadao();
      scanf(" %c", &op_cid);
      switch (op_cid)
      {
      case '1':
        cadastrar_cidadao(cidadaos, &tam_cid);
        break;
      case '2':
        imprime_cidadao(cidadaos, &tam_cid);
        break;
      case '3':
        print_menu_atualiza_cidadao();
        scanf(" %c", &op_cid_at);
        if (op_cid_at == '1')
        {
          atualiza_nome(cidadaos, &tam_cid);
        }
        if (op_cid_at == '2')
        {
          atualiza_idade(cidadaos, &tam_cid);
        }
        if (op_cid_at == '3')
        {
          atualiza_uf(cidadaos, &tam_cid);
        }
        break;
      case '4':
        exclui_cidadao(cidadaos, &tam_cid);
        break;
      default:
        break;
      }
    }
    if (op == '2')
    {
      if (senhas == 100)
      {
        printf("Já foram solicitados 100 atendimentos hoje. Até amanhã.");
      }
      else
      {
        printf("\nInforme o ID do cidadão: ");
        scanf("%d", &id);
        indice_cidadao = busca_indice_cidadao(cidadaos, &tam_cid, id);
        if (indice_cidadao == -1)
        {
          printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
        }
        else
        {
          if (cidadaos[indice_cidadao].idade >= 65)
          {
            gerar_senha(fila_p, &tam_fila_p, id, &senhas);
            printf("\nAtendimento solicitado colocado na fila PREFERENCIAL.\n");
            tem_pessoa_para_ser_atendida++;
          }
          else
          {
            gerar_senha(fila, &tam_fila, id, &senhas);
            printf("\nAtendimento solicitado colocado na fila NÃO PREFERENCIAL.\n");
            tem_pessoa_para_ser_atendida++;
          }
        }
      }
    }
    if (op == '3')
    {
      if (tam_fila_p > 0)
      {
        inicia_atendimento(atendimentos, &tam_at, fila_p);
        printf("\nPRÓXIMO ATENDIMENTO - SENHA %d\nServiço: %c\nMesa: %d\n", atendimentos[tam_at - 1].senha, atendimentos[tam_at - 1].tipo_atendimento, atendimentos[tam_at - 1].mesa);
        fecha_atendimento(fila_p, &tam_fila_p);
        tem_pessoa_para_ser_atendida--;
      }
      else
      {
        inicia_atendimento(atendimentos, &tam_at, fila);
        printf("\nPRÓXIMO ATENDIMENTO - SENHA %d\nServiço: %c\nMesa: %d\n", atendimentos[tam_at - 1].senha, atendimentos[tam_at - 1].tipo_atendimento, atendimentos[tam_at - 1].mesa);
        fecha_atendimento(fila, &tam_fila);
        tem_pessoa_para_ser_atendida--;
      }
    }
    if (op == 's')
    {
      if (tem_pessoa_para_ser_atendida == 0)
      {
        lista_atendimento_fechados(atendimentos, tam_at, cidadaos, &tam_cid);
        break;
      }
      else
      {
        printf("\nAinda há %d pessoas para serem atendidas.\n", senhas);
      }
    }
  } while (op != 's' || tem_pessoa_para_ser_atendida > 0);

  return 0;
}