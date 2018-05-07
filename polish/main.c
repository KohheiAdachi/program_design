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
    //storage_2acq(storage, a);
    //printf("add%d\n",a[1]+a[0]);
    push(a[1] + a[0], storage);
    (*count)++;
}

//減算
void sub(stack *storage, int *count){
    int a[2];
  //  storage_2acq(storage, a);
    //printf("sub%d\n",a[1]-a[0]);
    push(a[1] - a[0], storage);
    (*count)++;

}

//乗算
void mul(stack *storage, int *count){
    int a[2];
  //  storage_2acq(storage, a);
    //printf("multi%d\n",a[1]*a[0]);
    push(a[1] * a[0], storage);
    (*count)++;

}

//除算
void division(stack *storage, int *count){
    int a[2];
  //  storage_2acq(storage, a);
    //printf("division%d\n",a[1]/a[0]);
    push(a[1] / a[0], storage);
    (*count)++;

}

//符号を反転
void min(stack *storage, int *count){
    int a;
    a = pop(storage) * -1;
    push(a, storage);
    (*count)++;
}


int Valpolish(char *EXPR){
    int temp,ans,count = 0;
    int size = strlen(EXPR);
    stack storage;
    makenull(&storage);

    while(count < size){
      if(isdigit(EXPR[count])){

      }
    }





}
int main(int argc, char *argv[]){
  int ans;

  //入力された逆ポーランド式を計算
  printf("expression = ?");
  ans = Valpolish(argv[1]);
  printf("%d\n",ans );

  return 0;

}
