#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int num1(char n){
  return (atoi(&n));
}

int number(char *expr,int *next){
  int value;

  if(!isdigit(expr[*next])){
    return -1;
  }else{
    value = num1(expr[*next]);
    (*next)++;
    while(isdigit(expr[*next])){
      //valueの計算
      (*next)++;
    }
    return value;
  }
}

//加算
void add(stack *storage, int *count){
    int a[2];
    storage_2acq(storage, a);
    //printf("add%d\n",a[1]+a[0]);
    push(a[1] + a[0], storage);
    (*count)++;
}

//減算
void sub(stack *storage, int *count){
    int a[2];
    storage_2acq(storage, a);
    //printf("sub%d\n",a[1]-a[0]);
    push(a[1] - a[0], storage);
    (*count)++;

}

//乗算
void multi(stack *storage, int *count){
    int a[2];
    storage_2acq(storage, a);
    //printf("multi%d\n",a[1]*a[0]);
    push(a[1] * a[0], storage);
    (*count)++;

}

//除算
void division(stack *storage, int *count){
    int a[2];
    storage_2acq(storage, a);
    //printf("division%d\n",a[1]/a[0]);
    push(a[1] / a[0], storage);
    (*count)++;

}

//符号を反転
void minus(stack *storage, int *count){
    int a;
    a = pop(storage) * -1;
    push(a, storage);
    (*count)++;
}


int valpolish(char *expr){

}
int main(int argc, char *argv[]){



}
