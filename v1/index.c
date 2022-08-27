#include <stdio.h>
#include <string.h>

/*
Funções

Funções para manipular cidadãos

busca_indice_cidadao()
recebe o vetor e o tamanho de cidadaos e o id do cidadão que quer encontrar.
se encontrar devolve o indice.
senão devolve -1

troca_cidadão()
realiza a operação de inverter os valores de duas variáveis do tipo cidadao

cadastrar_cidadao()
recebe o vetor e o tamanho de cidadaos e faz o cadastro de um novo cidadão.
se o usuário informar um ID já cadastrado o programa retorna um erro.

exclui_cidadao()
recebe o vetor e o tamanho de cidadaos e dentro da função lê o ID do usuário que deseja apagar os dados.
se o usuário não for encontrado o programa exibe "Usuário não encontrado"

Funções de Atualizar Cidadao

temos 3: atualiza_nome(), atualiza_idade(), atualiza_uf().
todas elas funcionam da mesma forma, o que muda é o campo a ser atualizado.
recebe o vetor e o tamanho de cidadaos e dentro da função é lido o novo valor e atualizado.

Funções de print_menu() são meramente para exibir as mensagens dos menus, não tem nenhuma outra função além dessa.

Função de gerar_senha()
recebe a fila em questão, o tamanho da fila, o id do cidadão e uma variável senhas que computa o total de senhas (fila não preferencial + fila preferencial)

Funções de Atendimento

inicia_atendimento()
Recebe o vetor de atendimento, o tamanho desse vetor e o vetor da fila em que esse atendimento se encontra.
A fila (de pedidos) é passada para essa função pois o programa precisa de algumas informações que estão no pedido para salvar no atendimento como a senha, o cidadao (id) e o tipo de atendimento.
Essas informações são salvas pegando o pedido 0.

fecha_atendimento()
recebe a fila de atendimento e o tamanho.
o programa fecha um atendimento removendo ele da lista de atendimentos_solicitados (fila).
para remover ele desloca todos os itens uma casa a esquerda, removendo o primeiro item (indice 0), por isso sempre que o programa inicia um novo atendimento ele pega as informações do primeiro item da fila.

imprime_atendimento()
recebe o atendimento e o nome do cidadão e imprime na tela essas informações.

lista_atendimento_fechados()
recebe a lista de atendimentos fechados, o tamanho, a lista de cidadaos e o tamanho.
Para cada tipo de atendimento o sistema faz uma busca e os atendimentos que satisfazem a condição são exibidos em tela, como a senha é gerada por incremento os atendimentos já ficam ordenados da menor senha para a maior dentro de cada divisão.

Funcionamento do programa

O programa vai começar lendo a operação (op) e para cada possibilidade (1,2,3,4,s) o programa vai chamar as respectivas funções.

O programa conta com uma varável para o controle de saída: tem_pessoa_para_ser_atendida, inicialmente ela começa em 0, ao longo da execução, ao passo que cada novo atendimento é solicitado essa variável é incrementada, se o usuário informa op como 's' e a variável tem_pessoa_para_ser_atendida for > 0, o programa NÃO vai terminar e mostrará uma mensagem de erro.
Se tem_pessoa_para_ser_atendida for 0 o programa encerra.

*/

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
  int preferencial;
} atendimento_solicitado;

typedef struct
{
  char servidor[30];
  int senha;
  char tipo_atendimento;
  int preferencial;
  int id_cid;
  int mesa;
} atendimento;

void lerCidadaosDoArquivo(cidadao cidadaos[], int *tam)
{
  FILE *arq = fopen("cidadaos.csv", "r");
  int i;
  if (arq)
  {
    fscanf(arq, "%d\n", tam);
    for (i = 0; i < *tam; i++)
    {
      cidadao c;
      fscanf(arq, "\n%d, %[^,], %d, %[^;];\n", &c.id, c.nome, &c.idade, c.UF);
      cidadaos[i] = c;
    }
    fclose(arq);
  }
}

void escreverCidadaosNoArquivo(cidadao cidadaos[], int tam)
{
  FILE *arq = fopen("cidadaos.csv", "w");
  int i;
  if (arq)
  {
    fprintf(arq, "%d\n", tam);
    for (i = 0; i < tam; i++)
    {
      fprintf(arq, "%d, %s, %d, %s;\n", cidadaos[i].id, cidadaos[i].nome, cidadaos[i].idade, cidadaos[i].UF);
    }
    fclose(arq);
  }
}

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
    printf("NOME: %s\n", cidadaos[indice_cidadao].nome);
    printf("IDADE: %d\t UF: %s\n", cidadaos[indice_cidadao].idade, cidadaos[indice_cidadao].UF);
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
  if (i != -1)
  {
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  }
  else
  {
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
  if (i == -1)
  {
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  }
  else
  {
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
  if (i == -1)
  {
    printf("\nO Registro do cidadão não está cadastrado, ou foi excluído.\n");
  }
  else
  {
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
  printf("4 - RELATÓRIOS\n");
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

void lerSenhasNaoAtendidas(atendimento_solicitado fila_p[], atendimento_solicitado fila[], int *tam_fila, int *tam_fila_p, int *tem_pessoa_pra_ser_atendida)
{
  FILE *arq = fopen("senhas_nao_atendidas.csv", "r");
  int i;
  if (arq)
  {
    fscanf(arq, "%d\n", tam_fila);
    fscanf(arq, "%d\n", tam_fila_p);
    for (i = 0; i < *tam_fila; i++)
    {
      atendimento_solicitado at;
      fscanf(arq, "\n%d %c %d %d;\n", &at.id_cid, &at.tipo_atendimento, &at.senha, &at.preferencial);
      fila[i] = at;
      *tem_pessoa_pra_ser_atendida = *tem_pessoa_pra_ser_atendida + 1;
    }
    for (i = 0; i < *tam_fila_p; i++)
    {
      atendimento_solicitado at;
      fscanf(arq, "\n%d %c %d %d;\n", &at.id_cid, &at.tipo_atendimento, &at.senha, &at.preferencial);
      fila_p[i] = at;
      *tem_pessoa_pra_ser_atendida = *tem_pessoa_pra_ser_atendida + 1;
    }
    fclose(arq);
  }
}

void escreverSenhasNaoAtendidas(atendimento_solicitado fila_p[], atendimento_solicitado fila[], int tam_fila, int tam_fila_p) {
  FILE *arq = fopen("senhas_nao_atendidas.csv", "w");
  int i;
  if (arq)
  {
    fprintf(arq,"%d\n", tam_fila);
    fprintf(arq,"%d\n", tam_fila_p);
    for(i=0;i<tam_fila_p;i++) {
      fprintf(arq, "%d %c %d %d;\n", fila_p[i].id_cid, fila_p[i].tipo_atendimento, fila_p[i].senha, fila_p[i].preferencial);
    }
    for(i=0;i<tam_fila;i++) {
      fprintf(arq, "%d %c %d %d;\n", fila[i].id_cid, fila[i].tipo_atendimento, fila[i].senha, fila[i].preferencial);
    }
    
    fclose(arq);
  }
}

void troca_atendimento(atendimento *a, atendimento *b)
{
  atendimento aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void ordena_pela_senha(atendimento atendimentos[], int tam)
{
  int i, j;
  for (i = 0; i < tam; i++)
  {
    for (j = i + 1; j < tam - 1; j++)
    {
      if (atendimentos[i].senha > atendimentos[j].senha)
      {
        troca_atendimento(&atendimentos[i], &atendimentos[j]);
      }
    }
  }
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

void escreveAtendimentosRealizadosNoArquivo(atendimento atendimentos_realizados[], int tam_at, cidadao cidadaos[], int *tam_cid) {
  FILE *DOC = fopen("documentos.csv", "a");
  FILE *MOR = fopen("moradia.csv", "a");
  FILE *TRA = fopen("transporte.csv", "a");
  int i, indice_cidadao;
  if(DOC) {
    for(i=0;i<tam_at;i++) {
      indice_cidadao = busca_indice_cidadao(cidadaos, tam_cid, atendimentos_realizados[i].id_cid);
      if(atendimentos_realizados[i].tipo_atendimento == 'D')
        fprintf(DOC, "%d %s %s %d %d;\n", atendimentos_realizados[i].senha, cidadaos[indice_cidadao].nome, atendimentos_realizados[i].servidor, atendimentos_realizados[i].mesa, atendimentos_realizados[i].preferencial);
    }
  }
  fclose(DOC);

  if(MOR) {
    for(i=0;i<tam_at;i++) {
      indice_cidadao = busca_indice_cidadao(cidadaos, tam_cid, atendimentos_realizados[i].id_cid);
      if(atendimentos_realizados[i].tipo_atendimento == 'M')
        fprintf(MOR, "%d %s %s %d %d;\n", atendimentos_realizados[i].senha, cidadaos[indice_cidadao].nome, atendimentos_realizados[i].servidor, atendimentos_realizados[i].mesa, atendimentos_realizados[i].preferencial);
    }
  }
  fclose(MOR);

  if(TRA) {
    for(i=0;i<tam_at;i++) {
      indice_cidadao = busca_indice_cidadao(cidadaos, tam_cid, atendimentos_realizados[i].id_cid);
      if(atendimentos_realizados[i].tipo_atendimento == 'T')
        fprintf(TRA, "%d %s %s %d %d;\n", atendimentos_realizados[i].senha, cidadaos[indice_cidadao].nome, atendimentos_realizados[i].servidor, atendimentos_realizados[i].mesa, atendimentos_realizados[i].preferencial);
    }
  }
  fclose(TRA);

}

void imprime_atendimento(atendimento at, char nome[30])
{
  printf("Senha: %d - Cidadão: %s - Servidor: %s - Mesa: %d\n", at.senha, nome, at.servidor, at.mesa);
}

void lista_atendimento_fechados(atendimento atendimentos[], int tam, cidadao cidadaos[], int *tam_cid)
{
  int i, indice_cidadao;
  ordena_pela_senha(atendimentos, tam);
<<<<<<< HEAD:v1/index.c
  
=======

>>>>>>> 9947bd2a0a747342eec4ee4c86196e4cf433fb8b:index.c
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

void troca_atendimento(atendimento *a, atendimento *b) {
  atendimento aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void ordena_pela_senha(atendimento atendimentos[], int tam) {
  int i,j;
  for(i=0; i<tam;i++) {
    for(j=i+1;j<tam-1;j++) {
      if(atendimentos[i].senha > atendimentos[j].senha) {
        troca_atendimento(&atendimentos[i], &atendimentos[j]);
      }
    }
  }
}

int main(void)
{
  cidadao cidadaos[500];
  atendimento_solicitado fila[50], fila_p[50];
  atendimento atendimentos[100];
  int tam_cid, tam_fila, tam_fila_p, tam_at, tem_pessoa_para_ser_atendida, senhas, id, indice_cidadao;
  char op, op_cid, op_cid_at, op_rel;
  tam_cid = 0;
  tam_fila = 0;
  tam_fila_p = 0;
  senhas = 0;
  tam_at = 0;
  tem_pessoa_para_ser_atendida = 0;

  lerCidadaosDoArquivo(cidadaos, &tam_cid);
  lerSenhasNaoAtendidas(fila_p, fila, &tam_fila_p, &tam_fila, &tem_pessoa_para_ser_atendida);

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
            fila_p[tam_fila_p - 1].preferencial = 1;
            printf("\nAtendimento solicitado colocado na fila PREFERENCIAL.\n");
            tem_pessoa_para_ser_atendida++;
          }
          else
          {
            gerar_senha(fila, &tam_fila, id, &senhas);
            fila_p[tam_fila - 1].preferencial = 0;
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
        tem_pessoa_para_ser_atendida = tem_pessoa_para_ser_atendida - 1;
      }
      else
      {
        inicia_atendimento(atendimentos, &tam_at, fila);
        printf("\nPRÓXIMO ATENDIMENTO - SENHA %d\nServiço: %c\nMesa: %d\n", atendimentos[tam_at - 1].senha, atendimentos[tam_at - 1].tipo_atendimento, atendimentos[tam_at - 1].mesa);
        fecha_atendimento(fila, &tam_fila);
        tem_pessoa_para_ser_atendida = tem_pessoa_para_ser_atendida - 1;

      }
    }

    if (op == '4')
    {
      printf("\n1 - Cidadãos Cadastrados\n2 - Senhas não atendidas\n3 - Atendimentos Realizados\n0 - Voltar\n");
      scanf(" %c", &op_rel);
      switch (op_rel)
      {
      case '1':
        escreverCidadaosNoArquivo(cidadaos, tam_cid);
        break;
      case '2':
          escreverSenhasNaoAtendidas(fila_p, fila, tam_fila, tam_fila_p);
        break;
      case '3':
        escreveAtendimentosRealizadosNoArquivo(atendimentos, tam_at, cidadaos, &tam_cid);
        break;
      default:
        break;
      }
    }

    if (op == 's')
    {
      if (tem_pessoa_para_ser_atendida == 0)
      {
        escreverSenhasNaoAtendidas(fila_p, fila, tam_fila, tam_fila_p);
        printf("\nTchau Tchau.\n");
        break;
      }
      else
      {
        printf("\nAinda há %d pessoas para serem atendidas.\n", tem_pessoa_para_ser_atendida);
      }
    }
  } while (op != 's' || tem_pessoa_para_ser_atendida > 0);

  return 0;
}