# Documentação

## Tipos de Dados

O sistema funciona com os seguintes tipos de dados

**cidadão**
  id, nome, idade, uf
vetor de cidadaos

**pedido**
  id do cididadao, tipo de atendimento, senha
vetor de pedidos

## Funções:

```troca(cidadao *a, cidadao *b):```
    recebe dois parametros do tipo cidadao POR REFERÊNCIA e faz a troca de dois cidadãos, isso ajuda na hora de exlcuir um cidadao.

```cadastrar_cidadao(cidadao cidadadaos[500], int *tam)```
    recebe o vetor de cidadãos e o tamanho do vetor de cidadãos, este último por REFERÊNCIA.
    faz a leitura dos dados do cidadão na posição tam e no final acrescenta um na variável tam.