#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../ds-terminal/terminal.h"

typedef struct Queue{
  unsigned int size;
  int head;
  int tail;
  int* buffer; 
}Queue;

Queue* create_queue();

void enqueue();
void dequeue();
void print_queue();

int full();
int empty();

void setup_terminal();

int main(int argc, char* argv[]){
  if (argc != 2){
    printf("Please execute the file with the stack size as an argument.\nE.g. ./stack 2\n");
    exit(0);
  }

  unsigned int size = (unsigned int) atoi(argv[1]);

  Queue* queue = create_queue(size);

  setup_terminal();
	init_terminal(queue);
}

Queue* create_queue(unsigned int size){
  Queue* queue = (Queue*) malloc(size * sizeof(Queue));
	queue->size = size;
  queue->head = -1;
  queue->tail = -1;
  queue->buffer = (int*) malloc(size * sizeof(int));
}

void enqueue(Queue* queue, int n){
  if(full(queue)){
    printf("The queue is full.\n");
    return;
  }
  if(queue->head == -1){
      queue->buffer[++queue->head] = n;
      queue->tail++;
  }
  else{
		queue->tail = (queue->tail + 1) % queue->size;
	  queue->buffer[queue->tail] = n;
	}

	print_queue(queue);
}

void dequeue(Queue* queue, int n){
  if(empty(queue)){
    printf("The queue is empty.\n");
    return;
  }
  printf("%d\n", queue->buffer[queue->head]);
	if(queue->head == queue->tail)  queue->head = queue->tail = -1;
  else  queue->head = (queue->head + 1) % queue->size;
  print_queue(queue);
}

void print_queue(Queue* queue){
  unsigned int i;
  printf("[");
  if(queue->head != -1){
    i = queue->head;
    if(queue->head == queue->tail){
      printf("%d", queue->buffer[queue->head]);

    }
    else{
      _Bool flag = 0;
      while(!flag){
        if(i == queue->tail) flag = 1;
        
        printf("%d", queue->buffer[i]);
        if (i != queue->tail) printf(", ");
        i = (i + 1) % queue->size;
      }
    }
  }
  printf("]\n");
}

int full(Queue* queue){
	if((queue->tail == queue->size-1 && queue->head == 0 )|| queue->head-queue->tail == 1) return 1;
	return 0;
}

int empty(Queue* queue){
  if(queue->head == -1) return 1;
  return 0;
}

void setup_terminal(){
  add_command((unsigned long int) &enqueue, "enqueue", 1);
  add_command((unsigned long int) &dequeue, "dequeue", 0);
  add_command((unsigned long 	int) &print_queue, "print_queue", 0);
}