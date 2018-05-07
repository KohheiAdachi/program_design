#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
/*
int num1(char n){
  int num;
  num = atoi(&n);

  return num;
}
*/

int num1(char n){

  return(n - '0');
}

int number(char *expr,int *next){
  int value;

  if(!isdigit(expr[*next])){

    exit(1);
  }
  else{
    value = num1(expr[*next]);
    (*next)++;
    //２桁以上の整数
    while(isdigit(expr[*next])){
      //valueの計算
      value = value * 10;
      value = num1(expr[*next]);
      (*next)++;
    }
    if(expr[*next] == ','){
      return value;
    }
    else{
      printf("カンマエラー\n");
      exit(1);
    }
  }
}
void storage_2pop(stack *storage,int *pop_element){
    int i;
    //2要素を取り出すかスタックが空になるまでスタックから要素を取り出す
    for (i = 0; i < 2 && !isempty(storage); i++) {
      pop_element[i] = pop(storage);
    }

    if(isempty(storage) && i < 2){
      printf("error\n");
      exit(1);
    }

}
//加算
void add(stack *storage, int *count){
    int a[2];
    storage_2pop(storage, a);
    push(a[1] + a[0], storage);
    (*count)++;
}

//減算
void sub(stack *storage, int *count){
    int a[2];
    storage_2pop(storage, a);

    push(a[1] - a[0], storage);
    (*count)++;

}

//乗算
void mul(stack *storage, int *count){
    int a[2];
    storage_2pop(storage, a);
    push(a[1] * a[0], storage);
    (*count)++;

}

//除算
void division(stack *storage, int *count){
    int a[2];
    storage_2pop(storage, a);
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


int Valpolish(char *expr){
    int ans;
    int tmp;
    int count = 0;
    int size = strlen(expr);
    stack storage;
    makenull(&storage);

    while(count < size){
      //printf("%c",expr[count]);
      if(isdigit(expr[count])){
          tmp = number(expr,&count);
          push(tmp,&storage);
      }
      else if(expr[count] == '+'){
          add(&storage,&count);
      }
      else if(expr[count] == '-'){
          sub(&storage,&count);
      }
      else if(expr[count] == '*'){
          mul(&storage,&count);
      }
      else if(expr[count] == '/'){
          division(&storage,&count);
      }
      else if(expr[count] == 'm'){
          min(&storage,&count);
      }
      else if(expr[count] == ','){
          count++;
      }
      else{
          printf("error\n");

          exit(1);
      }
    }

    ans = pop(&storage);

    if(!isempty(&storage)){
      printf("error\n");
      exit(1);
    }
    return ans;
}
int main(int argc, char *argv[]){
  int ans;

  if(argc < 2){
    fprintf(stderr, "引数エラー\n");
    return 1;
  }
  else{
    //入力された逆ポーランド式を計算
    printf("answer = ");
    ans = Valpolish(argv[1]);
    printf("%d\n",ans );
  }

  return 0;

}
