#ifndef STACK_SIZE
#define STACK_SIZE 100
#endif
typedef struct{
  int elements[STACK_SIZE];
  int top;
}stack;

void makenull(stack *s);
void push(int x,stack *s);
int pop(stack *s);
int isempty(stack *s);
