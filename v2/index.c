#include <stdio.h>

typedef struct {
  int id;
  char nome[30];
  int idade;
  char UF[3];
} cidadao;

/* menus */
    void menu_pinricpal(char *op) {
        printf("\nAtendimento ao Cidadão\n");
        printf("----------------------\n");
        printf("1 - Cidadão\n");
        printf("2 - Gerar Senha\n");
        printf("3 - Atendimento\n");
        printf("S - Sair\n");
        scanf(" %c", op);
    }

    void menu_cidadao(char *op_cid) {
        printf("\nCidadão\n");
        printf("----------------------\n");
        printf("1 - Cadastrar Cidadao\n");
        printf("2 - Pesquisar por código\n");
        printf("3 - Alterar informação\n");
        printf("4 - Remover\n");
        printf("0 - Voltar\n");
        scanf(" %c", op_cid);
    }

    void menu_atualiza_cidadao(char *op_at_cid) {
        printf("\nAtualiza Informação\n");
        printf("----------------------\n");
        printf("1 - Atualizar Nome\n");
        printf("2 - Atualizar Idade\n");
        printf("3 - Atualizar UF\n");
        printf("0 - Voltar\n");
        scanf(" %c", op_at_cid);
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

    void troca_cidadao(cidadao *a, cidadao *b) {
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
                    troca_cidadao(&cidadaos[i], &cidadaos[j]);
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
                troca_cidadao(&cidadaos[i], &cidadaos[i + 1]);
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

int main(void) {
    cidadao cidadaos[500];
    int tam_cid, indice_cid, id;
    char op, op_cid, op_at_cid;
    int senhas_na_fila;
    FILE *arq;

    tam_cid = 0;
    senhas_na_fila = 0;

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