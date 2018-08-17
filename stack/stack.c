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
  Stack* stack = createStack(size);
  interface(stack);
}

void interface(Stack* stack){
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
    else if (!strcmp(command, "pop")) pop(stack);
    else if (!strcmp(command, "push")) push(stack, n);
    else if (!strcmp(command, "empty")) printf("%d\n", empty(stack));
    else if (!strcmp(command, "top")) printf("%d\n", top(stack));
    else if (!strcmp(command, "printStack")) printStack(stack);
    else {
      printf("Invalid Command.\n");
    }
 
    memset(command, 0, sizeof(command));
    memset(argument, 0, sizeof(argument));
 }
}

Stack* createStack(unsigned int size){
  Stack* stack = (Stack*) malloc(size * sizeof(Stack));
  stack->size = size;
  stack->top = -1;
  stack->buffer = (int*) malloc(size * sizeof(int));
  return stack;
}

int pop(Stack* stack){
  if (!empty(stack)){
    stack->top--;
    printStack(stack);
    return 1;
  }

  else printf("The stack is empty.\n");
  return 0;
}

_Bool push(Stack* stack, int n){
  if (stack->top == stack->size-1){
    printf("The stack is full.\n");
    return false;
  }
  
  stack->buffer[++stack->top] = n;
  printStack(stack);
  return true; 
}

_Bool empty(Stack* stack){
  if(stack->top == -1) return true;
  else return false;
}

int top(Stack* stack){
  return stack->buffer[stack->top];
}

void printStack(Stack* stack){
  unsigned int i;
  printf("[");
  for (i = 0; i < stack->top+1; i++){
    printf("%u", stack->buffer[i]);
    if (i != stack->top) printf(", ");
  }
  printf("]\n");
}
