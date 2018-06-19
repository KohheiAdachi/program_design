#include <stdio.h>
#include <stdlib.h>  /* random, srandom */
#include <time.h>    /* time */

void gendata(int a[], int n, int w)
{
  int i;
  for(i = 0; i < n; i++)
    a[i] = random() % w;
}

int main(int argc, char *argv[])
{
  int datanum = 10, width = 5;
  int data[datanum];
  int i;

  srandom(time(NULL)); /* initialize random */

  gendata(data, datanum, width);

  
  for(i = 0; i < datanum; i++)
    printf("%d\n", data[i]);


  return 0;
}
