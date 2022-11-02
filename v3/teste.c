#include <stdio.h>

void carrega() {
  FILE *arq;
  int status, x;
  arq = fopen("teste.data" ,"r");
  if(arq) {
    status = fscanf(arq, "%d\n", &x);
    while(status != -1) {
      printf("read: %d\n", x);
      status = fscanf(arq, "%d\n", &x);
    }
    fclose(arq);
  }
}

int main(void) {
  carrega();
  return 0;
}