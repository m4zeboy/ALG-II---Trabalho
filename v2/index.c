#include <stdio.h>

typedef struct {
  int id;
  char nome[30];
  int idade;
  char UF[3];
} cidadao;

/* menu principal */
void menu_pinricpal(char *op) {
    printf("\nAtendimento ao Cidadão\n");
    printf("----------------------\n");
    printf("1 - Cidadão\n");
    printf("2 - Gerar Senha\n");
    printf("3 - Atendimento\n");
    printf("S - Sair\n");
    scanf(" %c", op);
}
/* menu principal */

/* cidadão */

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

void salvaCidadao(cidadao cidadaos[], int *tam_cid, cidadao c) {
    c.id = *tam_cid + 1;
    cidadaos[*tam_cid] = c;
    *tam_cid = *tam_cid + 1;
}

int pesquisaCidadaoPorID(cidadao cidadaos[], int *tam_cid) {
    int i, indice, id;
    indice=-1;
    printf("ID: ");
    scanf("%d", &id);
    for(i=0;i< *tam_cid;i++) {
        if(cidadaos[i].id == id)
            indice=i;
    }
    return indice;
}

void troca_cidadao(cidadao *a, cidadao *b) {
    cidadao aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int removeCidadao(cidadao cidadaos[], int *tam_cid) {
    int i;
    int indice;
    printf("ID: ");
    indice = pesquisaCidadaoPorID(cidadaos, tam_cid);
    if(indice != -1) {
        for (i = indice; i - 1 < *tam_cid; i++) {
            troca_cidadao(&cidadaos[i], &cidadaos[i + 1]);
        }
        *tam_cid = *tam_cid - 1;
        printf("Cidadão Removido\n");
        return 0;
    } else {
        printf("Cidadão não encontrado ou removido.\n");
        return 1;
    }
}

/* cidadão */


int main(void) {
    cidadao cidadaos[500];
    int tam_cid;
    char op;
    int senhas_na_fila;

    tam_cid = 0;
    senhas_na_fila = 1;

    lerCidadaosDoArquivo(cidadaos, &tam_cid);
    
    do {
        menu_pinricpal(&op);
        if(op=='s' || op == 'S') {
            if(senhas_na_fila > 0) {
                printf("\nAinda tem pessoas na fila para serem atendidas.\n");

            } else {
                printf("\nTchau Tchau...\n");
                break;
            }
        }

    } while(op != 's' || senhas_na_fila > 0);
        

    return 0;
}







