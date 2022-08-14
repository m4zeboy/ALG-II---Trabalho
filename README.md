# Alg2 - Atividade 1 - Documentação

Moisés Silva de Azevedo

## Tipos de dados

```
cidadão {
  id
  nome
  idade
  UF
}
```

```
atendimento solicitado {
  id do cidadão
  tipo do atendimento
  documentos
  transporte
  moradia
  senha
  numero gerado automaticamente por um contador
}
```

```
atendimento {
  nome do servidor
  senha
  tipo do atendimento
  documentos
  transporte
  moradia
  id do cidadão
  mesa em que foi realizado o atendimento
}
```

## Funções

Funções para manipular cidadãos

- **busca_indice_cidadao()**
recebe o vetor e o tamanho de cidadaos e o id do cidadão que quer encontrar.
se encontrar devolve o indice.
senão devolve -1

- **troca_cidadão()**
realiza a operação de inverter os valores de duas variáveis do tipo cidadao

- **cadastrar_cidadao()**
recebe o vetor e o tamanho de cidadaos e faz o cadastro de um novo cidadão.
se o usuário informar um ID já cadastrado o programa retorna um erro.

- **exclui_cidadao()**
recebe o vetor e o tamanho de cidadaos e dentro da função lê o ID do usuário que deseja apagar os dados.
se o usuário não for encontrado o programa exibe "Usuário não encontrado"

Funções de Atualizar Cidadao

- temos 3: **atualiza_nome()**, **atualiza_idade()**, **atualiza_uf()**.
todas elas funcionam da mesma forma, o que muda é o campo a ser atualizado.
recebe o vetor e o tamanho de cidadaos e dentro da função é lido o novo valor e atualizado.

Funções de **print_menu()** são meramente para exibir as mensagens dos menus, não tem nenhuma outra função além dessa.

Função de **gerar_senha()**
recebe a fila em questão, o tamanho da fila, o id do cidadão e uma variável senhas que computa o total de senhas (fila não preferencial + fila preferencial)

Funções de Atendimento

- **inicia_atendimento()**
Recebe o vetor de atendimento, o tamanho desse vetor e o vetor da fila em que esse atendimento se encontra.
A fila (de pedidos) é passada para essa função pois o programa precisa de algumas informações que estão no pedido para salvar no atendimento como a senha, o cidadao (id) e o tipo de atendimento.
Essas informações são salvas pegando o pedido 0.

- **fecha_atendimento()**
recebe a fila de atendimento e o tamanho.
o programa fecha um atendimento removendo ele da lista de atendimentos_solicitados (fila).
para remover ele desloca todos os itens uma casa a esquerda, removendo o primeiro item (indice 0), por isso sempre que o programa inicia um novo atendimento ele pega as informações do primeiro item da fila.

- **imprime_atendimento()**
recebe o atendimento e o nome do cidadão e imprime na tela essas informações.

- **lista_atendimento_fechados()**
recebe a lista de atendimentos fechados, o tamanho, a lista de cidadaos e o tamanho.
Para cada tipo de atendimento o sistema faz uma busca e os atendimentos que satisfazem a condição são exibidos em tela, como a senha é gerada por incremento os atendimentos já ficam ordenados da menor senha para a maior dentro de cada divisão.

## Funcionamento do programa

O programa vai começar lendo a operação (op) e para cada possibilidade (1,2,3,4,s) o programa vai chamar as respectivas funções.

O programa conta com uma varável para o controle de saída: tem_pessoa_para_ser_atendida, inicialmente ela começa em 0, ao longo da execução, ao passo que cada novo atendimento é solicitado essa variável é incrementada, se o usuário informa op como 's' e a variável tem_pessoa_para_ser_atendida for > 0, o programa não vai terminar e mostrará uma mensagem de erro.
Se tem_pessoa_para_ser_atendida for 0 o programa encerra.