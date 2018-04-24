#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

int num1(char n){
  return (atoi(n))
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
int main(){
  
}
