#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../terminal.h"

typedef struct Stack {
  unsigned int size;
  int top;
  int* buffer;
}Stack;

Stack* stack;

// Public Functions

int pop();
int push();
int top();
void printStack();

// Private Functions

Stack* createStack();
void setupTerminal();
int empty();

int main (int argc, char* argv[]){
  if (argc != 2){
    printf("Please execute the file with the stack size as an argument.\nE.g. ./stack 2\n");
    exit(0);
  }

  unsigned int size = (unsigned int) atoi(argv[1]);
  stack = createStack(size);

  setupTerminal();
  initTerminal(stack);
}

Stack* createStack(unsigned int size){
  Stack* stack = (Stack*) malloc(size * sizeof(Stack));
  stack->size = size;
  stack->top = -1;
  stack->buffer = (int*) malloc(size * sizeof(int));
  return stack;
}

void setupTerminal(){
  addCommand("int",   (unsigned long int) &pop,         "pop",        0);
  addCommand("int",   (unsigned long int) &push,        "push",       1);
  addCommand("int",   (unsigned long int) &top,         "top",        0);
  addCommand("void",  (unsigned long int) &printStack,  "printStack", 0);
}

int pop(Stack* stack){
  if (!empty(stack)){
    printf("%d\n", stack->buffer[stack->top--]);
    printStack(stack);
    return 1;
  }

  else printf("The stack is empty.\n");
  return 0;
}

int push(Stack* stack, int n){
  if (stack->top == stack->size-1){
    printf("The stack is full.\n");
    return 0;
  }
  
  stack->buffer[++stack->top] = n;
  printStack(stack);
  return 1; 
}

int empty(Stack* stack){
  if(stack->top == -1) return 1;
  else return 0;
}

int top(Stack* stack){
  if(!empty(stack)){
    printf("%d\n", stack->buffer[stack->top]);
    return 1;
  }
  
  else  printf("The stack is empty\n");
  return 0;
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
