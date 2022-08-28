#include <stdio.h>
#include <string.h>

/*
    Fiz algumas alterações nas nomenclaturas e retirei aquela documentação extensa.
    Procurei deixar as funções mais específicas do que as funções da versão anterior, agora o fluxo de atendimento está melhor dividido em várias funções menores.
    Essa divisão se fez necessária pois me deparei com muitas funções recebendo muitos parâmetros, então tentei deixar a função menor, e receber o mínimo de parâmetros.

*/

typedef struct {
  int id, idade;
  char nome[30], UF[3];
} cidadao;

typedef struct
{
  int id_cid, senha;
  char servico_solicitado, prioridade[20];
} solicitacao_de_atendimento;

typedef struct
{
  int id_cid, mesa, senha;
  char servidor[30], prioridade[20], servico_solicitado;
} atendimento;

/* menus */
    void menu_pinricpal(char *op) {
        printf("\nAtendimento ao Cidadão\n");
        printf("----------------------\n");
        printf("1 - Cidadão\n2 - Gerar Senha\n3 - Atendimento\n4 - Relatórios\nS - Sair\n");
        scanf(" %c", op);
    }

    void menu_cidadao(char *op_cid) {
        printf("\nCidadão\n");
        printf("----------------------\n");
        printf("1 - Cadastrar Cidadao\n2 - Pesquisar por código\n3 - Alterar informação\n4 - Remover\n0 - Voltar\n");
        scanf(" %c", op_cid);
    }

    void menu_atualiza_cidadao(char *op_at_cid) {
        printf("\nAtualiza Informação\n");
        printf("----------------------\n");
        printf("1 - Atualizar Nome\n2 - Atualizar Idade\n3 - Atualizar UF\n0 - Voltar\n");
        scanf(" %c", op_at_cid);
    }

    void menu_relatorios(char *op_rel) {
        printf("\nRelatórios\n");
        printf("----------------------\n");
        printf("\n1 - Cidadão Cadastrados\n2 - Senhas Não Atendidas\n3 - Atendimentos Realzados\n0 - Voltar\n");
        scanf(" %c", op_rel);
    }
/* menus */

/* cidadão */

    int pesquisaCidadaoPorID(cidadao cidadaos[], int *tam_cid, int id) {
        int i, indice;
        indice=-1;
        for(i=0;i< *tam_cid;i++) {
            if(cidadaos[i].id == id)
                indice=i;
        }
        return indice;
    }

    void lerCidadaosDoArquivo(cidadao cidadaos[], int *tam_cid) {
        int i;
        FILE *arq;
        arq = fopen("cidadaos.csv", "r");
        if(arq == NULL) {
            printf("Não foi possível abrir o arquivo cidadãos.txt\n");
        } else {
            fscanf(arq, "%d\n", tam_cid);
            for(i=0;i < *tam_cid;i++) {
            fscanf(arq, "%d;%[^;];%d;%s\n", &cidadaos[i].id, cidadaos[i].nome, &cidadaos[i].idade, cidadaos[i].UF);
            }
            fclose(arq);
        }
    }

    void escreveCidadao(FILE *stream, cidadao c) {
        fprintf(stream, "%d;%s;%d;%s\n", c.id, c.nome, c.idade, c.UF);
    }

    void escreveVetorCidadaos(FILE *stream, cidadao cidadaos[], int tam_cid) {
    int i;
        fprintf(stream, "%d\n", tam_cid);
    for(i=0;i<tam_cid;i++) {
        escreveCidadao(stream, cidadaos[i]);
    } 
    }

    cidadao leCidadao() {
        cidadao c;
        printf("Nome: ");
        scanf(" %[^\n]", c.nome);
        printf("Idade: ");
        scanf("%d", &c.idade);
        printf("UF: ");
        scanf("%s", c.UF);
        return c;
    
    }

    void salvaCidadao(cidadao cidadaos[], int *tam_cid) {
        int id;
        cidadao c;
        printf("ID: ");
        scanf("%d", &id);
        if(pesquisaCidadaoPorID(cidadaos, tam_cid, id) != -1) {
            printf("\nCidadão já cadastrado com esse mesmo ID. Por favor tente outro.\n");
        } else {
            c = leCidadao();
            c.id = id;
            cidadaos[*tam_cid] = c;
            *tam_cid = *tam_cid + 1;
        }
    }
 
    void atualiza(cidadao cidadaos[], cidadao c, int indice) {
        cidadaos[indice] = c;
    }

    void atualizaNome(cidadao cidadaos[], int *tam_cid) {
        int id, indice;
        cidadao c;
        printf("ID: ");
        scanf("%d", &id);

        indice = pesquisaCidadaoPorID(cidadaos, tam_cid, id);
        c = cidadaos[indice];
        if(indice != -1) {
            printf("Novo Nome: ");
            scanf(" %[^\n]", c.nome);
            atualiza(cidadaos, c, indice);
        } else {
            printf("Cidadão não encontrado ou removido.\n");
        }
    }

    void atualizaIdade(cidadao cidadaos[], int *tam_cid) {
        int id, indice;
        cidadao c;
        printf("ID: ");
        scanf("%d", &id);

        indice = pesquisaCidadaoPorID(cidadaos, tam_cid, id);
        c = cidadaos[indice];
        if(indice != -1) {
            printf("Nova Idade: ");
            scanf("%d", &c.idade);
            atualiza(cidadaos, c, indice);
        } else {
            printf("Cidadão não encontrado ou removido.\n");
        }
    }

    void atualizaUF(cidadao cidadaos[], int *tam_cid) {
        int id, indice;
        cidadao c;
        printf("ID: ");
        scanf("%d", &id);

        indice = pesquisaCidadaoPorID(cidadaos, tam_cid, id);
        c = cidadaos[indice];
        if(indice != -1) {
            printf("Nova Idade: ");
            scanf(" %s", c.UF);
            atualiza(cidadaos, c, indice);
        } else {
            printf("Cidadão não encontrado ou removido.\n");
        }
    }

    void trocaCidadao(cidadao *a, cidadao *b) {
        cidadao aux;
        aux = *a;
        *a = *b;
        *b = aux;
    }
    
    void ordenarCidadaos(cidadao cidadaos[], int tam_cid) {
        int i, j;
        for(i=0;i<tam_cid;i++) {
            for(j=i+1;j<tam_cid;j++) {
                if(cidadaos[i].id > cidadaos[j].id) {
                    trocaCidadao(&cidadaos[i], &cidadaos[j]);
                }
            }
        }    
    }
   
    int removeCidadao(cidadao cidadaos[], int *tam_cid) {
        int i, id;
        int indice;
        printf("ID: ");
        scanf("%d", &id);
        indice = pesquisaCidadaoPorID(cidadaos, tam_cid, id);
        if(indice != -1) {
            for (i = indice; i - 1 < *tam_cid; i++) {
                trocaCidadao(&cidadaos[i], &cidadaos[i + 1]);
            }
            *tam_cid = *tam_cid - 1;
            printf("Cidadão Removido com sucesso.\n");
            return 0;
        } else {
            printf("Cidadão não encontrado ou removido.\n");
            return 1;
        }
    }

/* cidadão */

/* senha */
    void lerSolicitacaoDeAtendimento(solicitacao_de_atendimento *s_at, cidadao cidadaos[], int *tam_cid) {
        int id, indice;
        printf("ID: ");
        scanf("%d", &id);
        indice = pesquisaCidadaoPorID(cidadaos, tam_cid, id);
        if(indice != -1) {
            s_at->id_cid = cidadaos[indice].id;
            printf("Serviço solicitado: ");
            scanf(" %c", &s_at->servico_solicitado);
        } else {
            printf("Cidadão não encontrado ou removido.\n");
        }
    }

    void definirPreferenciaDaSenha(solicitacao_de_atendimento *s_at, cidadao cidadaos[], int *tam_cid) {
        int indice;
        indice = pesquisaCidadaoPorID(cidadaos, tam_cid, s_at->id_cid);
        if(indice != -1) {
            if(cidadaos[indice].idade >= 65) {
                sprintf(s_at->prioridade, "Preferencial");
            } else {
                sprintf(s_at->prioridade, "Não Preferencial");
            }
        } else {
            printf("Cidadão não encontrado ou removido.\n");
        }
    }

    void gerarSenha(solicitacao_de_atendimento *s_at, int tam_fila) {
        s_at->senha=tam_fila+1;
    }

    void adicionarNaFila(solicitacao_de_atendimento s_at, solicitacao_de_atendimento fila[], int *tam_fila) {
        fila[*tam_fila] = s_at;
        (*tam_fila)++;
    }

    void escreverSenha(FILE *stream, solicitacao_de_atendimento senha) {
        fprintf(stream, "ID_CID: %d;PRIORIDADE: %s;SENHA: %d;SERVIÇO SOLICITADO: %c\n", senha.id_cid, senha.prioridade, senha.senha, senha.servico_solicitado);
    }
    
    void escreverFila(FILE *stream, solicitacao_de_atendimento fila[], int tam_fila, solicitacao_de_atendimento fila_preferencial[], int tam_fila_preferencial) {
        int i;
        fprintf(stream, "%d;\n", tam_fila_preferencial);
        fprintf(stream, "%d;\n", tam_fila);
        for(i=0; i<tam_fila_preferencial;i++) {
            escreverSenha(stream, fila_preferencial[i]);
        }
         for(i=0; i<tam_fila;i++) {
            escreverSenha(stream, fila[i]);
        }
    }

/* senha */

/* atendimento ao cidadao */
    atendimento iniciarAtendimento() {
        atendimento at;
        printf("Servidor: ");
        scanf(" %[^\n]", at.servidor);
        printf("Mesa: ");
        scanf("%d",  &at.mesa);
        return at;
    }

    void definirProximaSenha(solicitacao_de_atendimento fila[], int tam_fila, solicitacao_de_atendimento fila_preferencial[], int tam_fila_preferencial, atendimento *at) {
        if(tam_fila_preferencial > 0) {
            /* atender o primeiro cidadao da fila preferencial*/
            at->id_cid = fila_preferencial[0].id_cid;
            at->senha = fila_preferencial[0].senha;
            strcpy(at->prioridade, fila_preferencial[0].prioridade);
            at->servico_solicitado = fila_preferencial[0].servico_solicitado;
        } else {
            /* atender o primeiro cidadao da fila */
            at->id_cid = fila[0].id_cid;
            at->senha = fila[0].senha;
            strcpy(at->prioridade, fila[0].prioridade);
            at->servico_solicitado = fila[0].servico_solicitado;
        }
    }

    void chamarProximaSenha(atendimento at) {
    printf("\nPróxima senha a ser atendida: %d\n", at.senha);
    printf("Tipo de sertviço: %c\tMesa: %d\n", at.servico_solicitado, at.mesa);

}

    void deslocaSenhas(solicitacao_de_atendimento fila[], int *tam_fila) {
        int i;
        for(i=0;i<*tam_fila;i++) {
            fila[i] = fila[i+1];
        }
        (*tam_fila)--;
    }

    void fechaAtendimento(atendimento at, atendimento atendimentos_realizados[], int *tam_at_rlzd) {
        atendimentos_realizados[*tam_at_rlzd] = at;
        (*tam_at_rlzd)++;
    }

    void escreverAtendimento(FILE *stream, atendimento at) {
        fprintf(stream, "ID_CID: %d;MESA: %d;SENHA: %d;SERVIDOR: %s;PRIORIDADE: %s;SERVICO_SOLICITADO: %c\n", at.id_cid, at.mesa, at.senha, at.servidor, at.prioridade, at.servico_solicitado);
    }

    void trocaAtendimento(atendimento *a, atendimento *b) {
        atendimento aux;
        aux = *a;
        *a = *b;
        *b = aux;
    }

    void ordenarAtendimento(atendimento atendimentos[], int tam_at_rlzd) {
        int i, j;
        for(i=0;i<tam_at_rlzd;i++) {
            for(j=i+1;j<tam_at_rlzd;j++) {
                if(atendimentos[i].senha > atendimentos[j].senha) {
                    trocaAtendimento(&atendimentos[i], &atendimentos[j]);

                }
            }
        }
    }

/* atendimento ao cidadao */
int main(void) {
    cidadao cidadaos[500];
    int tam_cid, indice_cid, id, tam_fila, tam_fila_preferencial, tam_at_rlzd, i;
    char op, op_cid, op_at_cid, op_rel;
    int senhas_na_fila;
    solicitacao_de_atendimento fila[100], fila_preferencial[100], s_at;
    atendimento at, atendimentos_realizados[500];
    FILE *arq;

    tam_cid = 0;
    tam_fila=0;
    tam_fila_preferencial=0;
    senhas_na_fila = 0;
    tam_at_rlzd=0;

    lerCidadaosDoArquivo(cidadaos, &tam_cid);
    
    do {
        menu_pinricpal(&op);

        if(op == '1') {
            menu_cidadao(&op_cid);
            switch (op_cid){
            case '1':
                /* cadasatrar cidadao */
                salvaCidadao(cidadaos, &tam_cid);
                break;
            case '2':
                /* Pesquisar por ID*/
                printf("ID: " );
                scanf("%d", &id);
                indice_cid = pesquisaCidadaoPorID(cidadaos, &tam_cid, id);
                if(indice_cid == -1) {
                    printf("\nUsuário não cadastrado ou excluído.\n");
                } else {
                    printf("\n");
                    escreveCidadao(stdout, cidadaos[indice_cid]);
                }
                break;
            case '3':
                menu_atualiza_cidadao(&op_at_cid);
                switch (op_at_cid) {
                case  '1':
                    /* Atualiza nome */
                    atualizaNome(cidadaos, &tam_cid);
                    break;
                case  '2':
                    /* Atualiza idade */
                    atualizaIdade(cidadaos, &tam_cid);
                    break;
                case  '3':
                    /* Atualiza UF */
                    atualizaUF(cidadaos, &tam_cid);
                    break;
                case  '0':
                    /* Voltar */
                    break;
                }
                break;
            case '4':
                /* Remover */ 
                removeCidadao(cidadaos, &tam_cid);
                break;
            case '0':
                break;
            }
        }

        if(op ==  '2') {
            if((tam_fila + tam_fila_preferencial) <= 100) {
                lerSolicitacaoDeAtendimento(&s_at, cidadaos, &tam_cid);
                definirPreferenciaDaSenha(&s_at, cidadaos, &tam_cid);
                if(strcmp(s_at.prioridade,"Preferencial") == 0)  {
                    gerarSenha(&s_at, tam_fila_preferencial);
                    adicionarNaFila(s_at,fila_preferencial, &tam_fila_preferencial); 
                    senhas_na_fila++;
                } else {
                    gerarSenha(&s_at, tam_fila);
                    adicionarNaFila(s_at,fila, &tam_fila); 
                    senhas_na_fila++;
                }
            } else
                printf("Hoje já atingiu 100 solicitações de atendimento.");
        }

        if(op == '3') {
            /* realizar atendimento */
            if(senhas_na_fila > 0) {
                at = iniciarAtendimento();
                definirProximaSenha(fila,tam_fila, fila_preferencial,tam_fila_preferencial,&at);
                chamarProximaSenha(at);
                if(tam_fila_preferencial>0) {
                    deslocaSenhas(fila_preferencial, &tam_fila_preferencial);
                } else {
                    deslocaSenhas(fila, &tam_fila);
                }
                fechaAtendimento(at, atendimentos_realizados,&tam_at_rlzd);
                senhas_na_fila--;
            } else {
                printf("\nAinda não há pessoas na fila para serem atendidas.\n");
            }

        }

        if(op == '4') {
            /* relatorios */
            menu_relatorios(&op_rel);
            switch (op_rel)
            {
            case '1':
                /* cidadaos cadastrados */
                arq = fopen("cidadaos.csv", "w");
                if(arq == NULL) {
                    printf("Não foi possível abrir o arquivo cidadaos.csv");
                } else {
                    escreveVetorCidadaos(arq, cidadaos, tam_cid);
                    fclose(arq);
                }
                break;
            case '2':
                /* senhas nao atendidas*/
                arq = fopen("proximas.csv", "w");
                if(arq == NULL) {
                    printf("Não foi possível abrir o arquivo proximas.csv");
                } else {
                    escreverFila(arq, fila, tam_fila, fila_preferencial, tam_fila_preferencial);
                    fclose(arq);
                }
                break;
            case '3':
                /* atendimentos realizados */
                ordenarAtendimento(atendimentos_realizados, tam_at_rlzd);
                /*DOCUMENTOS*/
                arq = fopen("documentos.csv", "w");
                if(arq == NULL) {
                    printf("Não foi possível abrir o arquivo documentos.csv");
                } else {
                    /*procurar apenas os atendimentos realizados pelo serviço de DOCUMENTOS*/
                    for(i=0;i<tam_at_rlzd;i++) {
                        if(atendimentos_realizados[i].servico_solicitado == 'D') {
                            escreverAtendimento(arq, atendimentos_realizados[i]);
                        }
                    }     
                    fclose(arq);
                }
                /*DOCUMENTOS*/
                
                /*TRANSPORTE*/
                arq = fopen("transporte.csv", "w");
                if(arq == NULL) {
                    printf("Não foi possível abrir o arquivo transporte.csv");
                } else {
                    /*procurar apenas os atendimentos realizados pelo serviço de TRANSPORTE*/
                    for(i=0;i<tam_at_rlzd;i++) {
                        if(atendimentos_realizados[i].servico_solicitado == 'T') {
                            escreverAtendimento(arq, atendimentos_realizados[i]);
                        }
                    }     
                    fclose(arq);
                }
                /*TRANSPORTE*/

                /*TRANSPORTE*/
                arq = fopen("moradia.csv", "w");
                if(arq == NULL) {
                    printf("Não foi possível abrir o arquivo transporte.csv");
                } else {
                    /*procurar apenas os atendimentos realizados pelo serviço de TRANSPORTE*/
                    for(i=0;i<tam_at_rlzd;i++) {
                        if(atendimentos_realizados[i].servico_solicitado == 'M') {
                            escreverAtendimento(arq, atendimentos_realizados[i]);
                        }
                    }     
                    fclose(arq);
                }
                /*TRANSPORTE*/
                
            
            default:
                break;
            }
        }
        /* saída */
        if(op=='s' || op == 'S') {
            if(senhas_na_fila > 0) {
                printf("\nAinda tem pessoas na fila para serem atendidas.\n");

            } else {
                printf("\nTchau Tchau...\n");
                arq = fopen("cidadaos.csv", "w");
                if(arq == NULL)
                    printf("\nNão foi possível abrir o arquivo cidadaos.csv.\n");
                else {
                    ordenarCidadaos(cidadaos, tam_cid);
                    escreveVetorCidadaos(arq, cidadaos, tam_cid);
                    fclose(arq);
                } 

                break;
            }
        }
        /* saída */
        
    } while(op != 's' || senhas_na_fila > 0);
        

    return 0;
}