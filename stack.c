#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Pilha {
  unsigned int tamanho;
  int topo;
  int* pilha;
}Pilha;

Pilha* criarPilha();
int pop();
_Bool push();
_Bool vazio();
int topo();
void imprimirPilha();
void interface();

int main (int argc, char* argv[]){

  char str[28];
  char comando[15];
  char argumento[10];

  unsigned int tamanho = (unsigned int) atoi(argv[1]);

  Pilha* pilha = criarPilha(tamanho);

  interface(pilha);
}

void interface(Pilha* pilha){
  
  char str[28];
  char comando[15];
  char argumento[10];


  while(1){
 
    printf(">> ");
 
    fgets(str, sizeof str, stdin);
 
    int i = 0;
    int j = 0;
 
    if(str[0] == '\n') continue;
 
    while(str[i]!='(')  comando[j++] = str[i++];
 
    i++;
    j = 0;
 
    int n;
 
    while(str[i]!=')')  argumento[j++] = str[i++];
 
    n = atoi(argumento);
 
    if (!strcmp(comando, "quit")) exit(0);
    else if (!strcmp(comando, "pop")) pop(pilha);
    else if (!strcmp(comando, "push")) push(pilha, n);
    else if (!strcmp(comando, "vazio")) printf("%d\n", vazio(pilha));
    else if (!strcmp(comando, "topo")) printf("%d\n", topo(pilha));
    else if (!strcmp(comando, "imprimirPilha")) imprimirPilha(pilha);
    else {
      printf("Comando inválido.\n");
    }
 
    memset(comando, 0, sizeof(comando));
    memset(argumento, 0, sizeof(argumento));
 }
}

Pilha* criarPilha(unsigned int tamanho){
  Pilha* pilha = (Pilha*) malloc(tamanho * sizeof(Pilha));
  pilha->tamanho = tamanho;
  pilha->topo = -1;
  pilha->pilha = (int*) malloc(tamanho * sizeof(int));
  return pilha;
}

int pop(Pilha* pilha){
  if (!vazio()){
    pilha->topo--;
    imprimirPilha(pilha);
    return 1;
  }

  else printf("A pilha está vazia.\n");
  return 0;
}

_Bool push(Pilha* pilha, int n){
  
  if (pilha->topo == pilha->tamanho-1){
    printf("A pilha está cheia.\n");
    return false;
  }
  
  pilha->pilha[++pilha->topo] = n;
  imprimirPilha(pilha);
  return true; 
}

_Bool vazio(Pilha* pilha){
  if(pilha->topo == -1) return true;
  else return false;
}

int topo(Pilha* pilha){
  return pilha->pilha[pilha->topo];
}

void imprimirPilha(Pilha* pilha){
  unsigned int i;
  printf("[");
  for (i = 0; i < pilha->topo+1; i++){
    printf("%u", pilha->pilha[i]);
    if (i != pilha->topo) printf(", ");
  }
  printf("]\n");
}
