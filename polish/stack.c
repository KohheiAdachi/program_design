#include "stack.h"
//スタックをカラにする
void makenull(stack *s){
  s->top = 0;
  return;
}
//要素ｘをスタックにpushする
void push(int x,stack *s){
  s->elements[s->top]=x;
  return;
}
//スタックのtop要素をpopする
int pop(stack *s){
  return(s->elements[s->top])
}
//スタックが空かどうかを判定する
int isempty(stack *s){
  if(s->top>1){
    return 0;
  }
  else{
    return -1;
  }
}
