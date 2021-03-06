#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 100 //入力の最大長

int ERR = 0; //エラーを見つけた時，1をセットする

void error(char *expr,int p,char *message){
  int i;
if(ERR == 0){
  fprintf(stderr, "%s\n",expr); //式を表示
  for(i = 0; i < p; i++) putc(' ',stderr);//エラーが見つかった位置を表示
  putc('^',stderr);putc('\n',stderr); //エラーメッセージを表示
  fprintf(stderr, "error:%s\n", message); //エラーフラグをセット
  ERR = 1;
}
}
/*数字1文字を対応する0〜9の数に変換*/
int num1(char n){
  return(n - '0');
}

/*数の処理*/
int number(char *expr,int *p){
  int value = 0;

  if(!isdigit(expr[*p])){
    error(expr,*p,"数が必要");
  }
  //数字が続くまでループする
  else{
    value = num1(expr[*p]);
    (*p)++;
    while(isdigit(expr[*p])){
      value = value * 10 + num1(expr[*p]);
      (*p)++;
    }
    //未定義の文字でエラーを出す
    if((expr[*p]) == '\n' || (expr[*p] == '(') || (expr[*p] == ')') || (expr[*p] == '+') || (expr[*p] == '-') || (expr[*p] == '*') || (expr[*p] == '/')){
        return value;
    }
    else{
      error(expr,*p,"未定義の文字");
    }
  }
  return value;
}
/*式の処理(再帰処理)*/

int valinfix0(char *expr,int *p){
  int x,y; //部分式の評価結果
  char op; //演算子

  if(expr[*p] != '(') /*単純な数*/
    return number(expr,p);
  else {
    (*p)++;
      if(expr[*p] == '-'){　/*単項演算*/
        (*p)++;
        x = valinfix0(expr,p) * -1;
        if(expr[*p] == ')'){
          (*p)++;
          return x;
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");
        }
      }
    else{
      x = valinfix0(expr,p);
      op = expr[*p];
      if ((op != '+' && (op != '-') && (op != '*') && (op != '/'))){
        error(expr,*p,"演算子が必要");
      }
      else{

      //2項演算の処理をする
      if(op == '+'){
        (*p)++;
        y = valinfix0(expr,p);
        x += y;
        if(expr[*p] == ')'){
          (*p)++;
          return x;
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");
        }
      }
      else if (op == '-'){
        (*p)++;
        y = valinfix0(expr,p);
        x -= y;
        if(expr[*p] == ')'){
          (*p)++;
          return x;
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");
        }
      }
      else if (op == '*'){
        (*p)++;
        y = valinfix0(expr,p);
        x *= y;
        if(expr[*p] == ')'){
          (*p)++;
          return x;
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");
        }
      }
      else if (op == '/'){
        (*p)++;
        y = valinfix0(expr,p);
        x /= y;
        if(expr[*p] == ')'){
          (*p)++;
          return x;
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");
        }
      }
    }
    }
  }
  return 0;
}

int valinfix(char *expr){
  int p,ans;

  p = 0;
  ERR = 0;  //エラーをリセット


  ans = valinfix0(expr,&p);
  //入力式の最後(\n)まで見れているかチェック
  if(expr[p] != '\n'){
    error(expr, p, "括弧の対応が取れてない");
  }
  else{
    return ans;
  }

  return valinfix0(expr,&p);
}
int main(int argc,char *argv[]){
  char expr[MAXLENGTH];
  int val;

  fprintf(stderr, "Expression = ");
  while((fgets(expr,MAXLENGTH,stdin) != NULL) && (expr[0] != '\n')){
    val = valinfix(expr);
    if(!ERR){
      printf("Value = %d\n",val);
    }
    fprintf(stderr, "Expression = ");
  }
  return 0;
}
