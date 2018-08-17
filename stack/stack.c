#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Stack {
  unsigned int size;
  int top;
  int* buffer;
}Stack;

Stack* createStack();
int pop();
_Bool push();
_Bool empty();
int top();
void printStack();
void interface();

int main (int argc, char* argv[]){
  if (argc != 2){
    printf("Please execute the file with the stack size as an argument.\nE.g. ./stack 2\n");
    exit(0);
  }

  unsigned int size = (unsigned int) atoi(argv[1]);
  Stack* buffer = createStack(size);
  interface(buffer);
}

void interface(Stack* buffer){
  char str[28];
  char command[15];
  char argument[10];

  while(1){
    printf(">> ");
    fgets(str, sizeof str, stdin);
 
    int i = 0;
    int j = 0;
    int n;

    if(str[0] == '\n') continue;
 
    while(str[i]!='(')  command[j++] = str[i++];
 
    i++;
    j = 0;
 
    while(str[i]!=')')  argument[j++] = str[i++];
 
    n = atoi(argument);
 
    if (!strcmp(command, "quit")) exit(0);
    else if (!strcmp(command, "pop")) pop(buffer);
    else if (!strcmp(command, "push")) push(buffer, n);
    else if (!strcmp(command, "empty")) printf("%d\n", empty(buffer));
    else if (!strcmp(command, "top")) printf("%d\n", top(buffer));
    else if (!strcmp(command, "printStack")) printStack(buffer);
    else {
      printf("Invalid Command.\n");
    }
 
    memset(command, 0, sizeof(command));
    memset(argument, 0, sizeof(argument));
 }
}

Stack* createStack(unsigned int size){
  Stack* buffer = (Stack*) malloc(size * sizeof(Stack));
  buffer->size = size;
  buffer->top = -1;
  buffer->buffer = (int*) malloc(size * sizeof(int));
  return buffer;
}

int pop(Stack* buffer){
  if (!empty()){
    buffer->top--;
    printStack(buffer);
    return 1;
  }

  else printf("The stack is empty.\n");
  return 0;
}

_Bool push(Stack* buffer, int n){
  if (buffer->top == buffer->size-1){
    printf("The stack is full.\n");
    return false;
  }
  
  buffer->buffer[++buffer->top] = n;
  printStack(buffer);
  return true; 
}

_Bool empty(Stack* buffer){
  if(buffer->top == -1) return true;
  else return false;
}

int top(Stack* buffer){
  return buffer->buffer[buffer->top];
}

void printStack(Stack* buffer){
  unsigned int i;
  printf("[");
  for (i = 0; i < buffer->top+1; i++){
    printf("%u", buffer->buffer[i]);
    if (i != buffer->top) printf(", ");
  }
  printf("]\n");
}
