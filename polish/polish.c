#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
int ERR = 0;
void error(char *m)
{
    ERR = 1;
    fprintf(stderr, "%s\n", m);
}
//数字１文字の文字列型からint型に変換
int num1(char n){
  int num;
  num = atoi(&n);
  return num;
}
//文字列型の数字ををint型に変換
int number(char *expr,int *next){
  int value;

  if(!isdigit(expr[*next])){
    error("numebr error");
    return 0;
  }
  else{
    value = num1(expr[*next]);
    (*next)++;
    //2桁以上の整数
    while(isdigit(expr[*next])){
      value = value * 10;
      value += num1(expr[*next]);
      (*next)++;
    }
    if(expr[*next] == ','){
      return value;
    }
    else{
      error("Comma error");
      return 0;
    }
  }
}
//スタックから2要素を取り出す
int storage_2pop(stack *storage,int *pop_element){
    int i;
    //2要素を取り出すかスタックが空になるまでスタックから要素を取り出す
    for (i = 0; i < 2 && !isempty(storage); i++) {
      pop_element[i] = pop(storage);
    }
    //スタックが空か2要素取り出せない場合エラー
    if(isempty(storage) && i < 2){
      error("stack empty error");
      return 1;
    }
    return 0;
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

//逆ポーランド式計算
int Valpolish(char *expr){
    int ans;
    int count = 0;
    int size = strlen(expr) - 1;
    stack storage;
    //スタックを空にする
    makenull(&storage);

    while(count < size && ERR != 1){
      if(isdigit(expr[count])){
          //スタックにプッシュする
          push(number(expr,&count),&storage);
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
          error("str error\n");
          return 0;
      }

      if(ERR){
        return 0;
      }
    }
    //スタックに残っている最後に1つを取り出す．
    ans = pop(&storage);
    //スタックを取り出して，スタックが空でない場合エラー
    if(!isempty(&storage)){
      error("stack error\n");
      return 0;
    }
    return ans;
}

int main(){
  int ans;
  char str[100];
    do{
    //入力された逆ポーランド式を計算
    printf("Expression = ? ");
    fgets(str,200,stdin);
    ans = Valpolish(str);
    if(ERR == 0 && str[0] != '\n')
      printf("Value = %d\n",ans);
    else
      ERR = 0;
    }while(str[0] != '\n');

  return 0;

}
