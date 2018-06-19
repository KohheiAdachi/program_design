#include <stdio.h>
#include <stdlib.h>  /* random, srandom */
#include <time.h>    /* time */
typedef int element_type; /*データの型*/

void gendata(int a[], int n, int w)
{
  int i;
  for(i = 0; i < n; i++)
    a[i] = random() % w;
}
void bubble_sort(element_type data[],int n){
  int i,j,tmp;
  for (i = 0; i < n; i++) {
    for (j=n-1; j>i; j--)
      if(data[j-1] > data[j]){
        tmp = data[j];
        data[j] = data[j-1];
        data[j-1] = tmp;
      }
  }
}
void selection_sort(element_type data[],int n){
  int i,j,tmp;
  for(i = 0;i<n-1;i++)
    for(j=i+1;j<n;j++)
     if(data[i]>data[j]){
       tmp = data[i];
       data[i] = data[j];
       data[j] = tmp;
     }
}
void insertion_sort(element_type data[],int n){
  int i,j;
  element_type tmp;
  for(i=1;i<n;i++){
    tmp = data[i];
    for(j=i; j>0 && data[j-1]>tmp; j--)
      data[j] = data[j-1];
    data[j] = tmp;
  }
}
int main(int argc, char *argv[])
{
  int datanum = 1000, width = 1000;
  int data[datanum];
  int i;

  srandom(time(NULL)); /* initialize random */

  gendata(data, datanum, width);

  bubble_sort(data,datanum);

  //selection_sort(data,datanum);

  //insertion_sort(data,datanum);

  for(i = 0; i < datanum; i++)
    printf("%d\n", data[i]);


  return 0;
}
