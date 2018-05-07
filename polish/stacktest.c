#include <stdio.h>

#include "stack.h"

int main(void){
  stack a; //スタックAの宣言

  makenull(&a);
  push(1, &a);
  push(2, &a);
  push(3, &a);

  while(!isempty(&a))
    printf("%d\n",pop(&a) );

    return 0;

}
