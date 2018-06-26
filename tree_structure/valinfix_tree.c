#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLENGTH 100 //入力の最大長

#include "mem_util.h"
//#define free(A) printf("free = %p\n",A)

int ERR = 0; //エラーを見つけた時，1をセットする
typedef struct _node{
  enum {LEAF,INTERNAL} kind; /*葉か内部かの区別(enumは列挙子)*/
  int value; /*値(葉のとき)*/
  struct _node *leftchild,*rightchild; /*左の子，右の子(内部のとき)*/
  char operater; /*演算子(内部のとき)*/
}node,*tree;
//葉を作る
tree create_leaf(int v){
  tree t;
  t = (tree)malloc(sizeof(node)); /*メモリ割り当て(malloc)*/
  t->kind = LEAF;
  t->value = v;
  t->leftchild = NULL; //左
  t->rightchild = NULL; //右
  return t;
}
//内部ノードの作成
tree create_internal(char op,tree sub1,tree sub2){
  tree t;
  t = (tree)malloc(sizeof(node));
  t->kind = INTERNAL;
  t->operater = op;
  t->leftchild = sub1; //左
  t->rightchild = sub2; //右
  return t;
}
//メモリーの解放
void free_tree(tree t){
  if(t==NULL) return;
  if(t->leftchild != NULL) free_tree(t->leftchild);
  if(t->rightchild != NULL) free_tree(t->rightchild);
  free(t);
}




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
tree number(char *expr,int *p){
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
        return create_leaf(value);
    }
    else{
      error(expr,*p,"未定義の文字");
    }
  }
  return create_leaf(value);
}
/*式の処理(再帰処理)*/

tree infix_to_tree0(char *expr,int *p){
  tree x,y; //部分式の評価結果
  char op; //演算子
  if(expr[*p] != '(') /*単純な数*/
    return number(expr,p);
  else {
    (*p)++;
      if(expr[*p] == '-'){ /*単項演算*/
        (*p)++;
        x = infix_to_tree0(expr,p);
        if(expr[*p] == ')'){
          (*p)++;
          return create_internal('-',NULL,x);
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");
          return NULL;
        }
      }
    else{
      x = infix_to_tree0(expr,p);
      op = expr[*p];
      if ((op != '+' && (op != '-') && (op != '*') && (op != '/'))){
        error(expr,*p,"演算子が必要");
      }
      else{

      //2項演算の処理をする
      if(op == '+'){
        (*p)++;
        y = infix_to_tree0(expr,p);
        //x += y;
        if(expr[*p] == ')'){
          (*p)++;
          return create_internal('+',x,y);
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");
        }
      }
      else if (op == '-'){
        (*p)++;
        y = infix_to_tree0(expr,p);
        //x -= y;
        if(expr[*p] == ')'){
          (*p)++;
          return create_internal('-',x,y);
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");

        }
      }
      else if (op == '*'){
        (*p)++;
        y = infix_to_tree0(expr,p);
        //x *= y;
        if(expr[*p] == ')'){
          (*p)++;
          return create_internal('*',x,y);
        }
        else{
          error(expr,*p,"括弧の対応が取れてない");

        }
      }
      else if (op == '/'){
        (*p)++;
        y = infix_to_tree0(expr,p);
        //x /= y;
        if(expr[*p] == ')'){
          (*p)++;
          return create_internal('/',x,y);
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

tree infix_to_tree(char *expr){
  int p;
  tree t;
  p = 0;
  ERR = 0;  //エラーをリセット

  t = infix_to_tree0(expr,&p);
  //入力式の最後(\n)まで見れているかチェック
  if(expr[p] != '\n'){
    error(expr, p, "括弧の対応が取れてない");
    return NULL;
  }
  else{
    return t;
  }

  return NULL;
}
//前置
void preorder_list(tree t){
  //演算子(内部)
  if (t == NULL) {
    return;
  }
  if(t->kind == INTERNAL){
    if(t->leftchild == NULL){
      printf("m");
    }
    else{
    printf("%c",t->operater);
  }
  }

  if(t->kind == LEAF){
    printf("%d", t->value);
  }

  if(t->leftchild != NULL){
    printf(",");
    preorder_list(t->leftchild);
  }
  if(t->rightchild != NULL){
    printf(",");
    preorder_list(t->rightchild);
  }
}
//中置
void inorder_list(tree t){
  if (t == NULL) {
    return;
  }
  if(t->leftchild != NULL){
    printf("(");
    inorder_list(t->leftchild);
  }
  //演算子
  if(t->kind == INTERNAL){
    if(t->leftchild == NULL){
      printf("(");
    }
      printf("%c",t->operater);


  }
  //数値
  else if(t->kind == LEAF){
    printf("%d",t->value);
  }
  if(t->rightchild != NULL){
    inorder_list(t->rightchild);
    printf(")");
  }
}
//後置
void postorder_list(tree t){
  if (t == NULL) {
    return;
  }
  if(t->leftchild != NULL){
    postorder_list(t->leftchild);
    printf(",");
  }
  if(t->rightchild != NULL){
    postorder_list(t->rightchild);
    printf(",");
  }

  if(t->kind == INTERNAL){
    if(t->leftchild == NULL){
      printf("m");
    }
    else{
      printf("%c",t->operater);
    }
  }
  else if(t->kind == LEAF){
    printf("%d",t->value);
  }
}


int main(int argc,char *argv[]){
  char expr[MAXLENGTH];
  tree t;

  fprintf(stderr, "Expression = ");
  while((fgets(expr,MAXLENGTH,stdin) != NULL) && (expr[0] != '\n')){
    t = infix_to_tree(expr);
    if(!ERR){
      //preorder
      printf("preorder: ");
      preorder_list(t);
      printf("\n");
      //inorder
      printf("inorder: ");
      inorder_list(t);
      printf("\n");
      //postorder
      printf("postorder: ");
      postorder_list(t);
      printf("\n");
    }
    free_tree(t);
    fprintf(stderr, "Expression = ");
  }

  return 0;
}
