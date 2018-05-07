#include "stack.h"
//スタックをカラにする
void makenull(stack *s){
  s->top = 0;
  return;
}
//要素ｘをスタックにpushする
void push(int x,stack *s){
  s->elements[s->top] = x;
  s->top++;
  return;
}
//スタックのtop要素をpopする
int pop(stack *s){
  s->top--;
  return(s->elements[s->top]);
}
//スタックが空かどうかを判定する
int isempty(stack *s){
  if(s->top < 1){
    return 1;
  }
  else{
    return 0;
  }
}
