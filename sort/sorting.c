#include <stdio.h>
#include <stdlib.h>  /* random, srandom */
#include <time.h>    /* time */
typedef int element_type; /*データの型*/
clock_t s, e; /* clock_t は int とほぼ同じ */
double cpu;
void gendata(int a[], int n, int w)
{
  int i;
  for(i = 0; i < n; i++)
    a[i] = random() % w;
}
void bubble_sort(element_type data[],int n){
  int i,j,tmp;
  s = clock();
  for (i = 0; i < n; i++) {
    for (j=n-1; j>i; j--)
      if(data[j-1] > data[j]){
        tmp = data[j];
        data[j] = data[j-1];
        data[j-1] = tmp;
      }
  }
  e = clock();
}
void selection_sort(element_type data[],int n){
  int i,j,tmp;
  s = clock();
  for(i = 0;i<n-1;i++)
    for(j=i+1;j<n;j++)
     if(data[i]>data[j]){
       tmp = data[i];
       data[i] = data[j];
       data[j] = tmp;
     }
  e = clock();
}
void insertion_sort(element_type data[],int n){
  int i,j;
  element_type tmp;
  s = clock();
  for(i=1;i<n;i++){
    tmp = data[i];
    for(j=i; j>0 && data[j-1]>tmp; j--)
      data[j] = data[j-1];
    data[j] = tmp;
  }
  e = clock();
}
int main(int argc, char *argv[])
{
  int datanum = 100000, width = 100000;
  int data[datanum];
  int i;

  srandom(time(NULL)); /* initialize random */

  gendata(data, datanum, width);

  //bubble_sort(data,datanum);

  //selection_sort(data,datanum);

  insertion_sort(data,datanum);

  cpu = (double)(e - s)/CLOCKS_PER_SEC;
/*
  for(i = 0; i < datanum; i++)
    printf("%d\n", data[i]);
*/
  printf("%f\n",cpu);

  return 0;
}
