#include <stdio.h>
#include <stdlib.h>  /* random, srandom */
#include <time.h>    /* time */
#include <string.h>
typedef int element_type; /*データの型*/
clock_t s, e; /* clock_t は int とほぼ同じ */
double cpu_b,cpu_s,cpu_i;
void quick_sort(element_type data[],int i,int j);

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
int find_pivot(element_type data[],int i,int j){
  int k;
  for(k=i+1;k<=j;k++){
    if(data[i] != data[k]){
      if(data[i]>data[k]){
        return i;
      }
      else{
        return k;
      }
  }
}
  return -1;
}

int partition(element_type data[],int i,int j,element_type pivot){
 int left,right;
 int tmp;
 left = i;
 right = j;
 //printf("%d\n",pivot);
 do {
   if(data[left]<pivot){
     left++;
   }
   if(data[right]>=pivot){
     right--;
   }
   if(left<right){
     //printf("%d \n",data[left]);
     tmp = data[left];
     data[left] = data[right];
     data[right] = tmp;
   }
 } while(left<=right);
 return left;
}
void quick_sort(element_type data[],int i,int j){
  int pivotindex,k;
  pivotindex = find_pivot(data,i,j);
  if(pivotindex >= 0){
    k = partition(data,i,j,data[pivotindex]);
    quick_sort(data,i,k-1);
    quick_sort(data,k,j);
  }
}
int main(int argc, char *argv[])
{
  int datanum = 10 ,width = 100;
  int data[datanum];
  int data_b[datanum],data_s[datanum],data_i[datanum];
  int i;

  srandom(time(NULL)); /* initialize random */



//  for(i=1;i<=10;i++){
  //  datanum = i * 10000;
    printf("datanum:%d\n",datanum);
    gendata(data, datanum, width);

    //配列のコピー
//    memcpy(data_s, data, sizeof(int) * datanum);
//    memcpy(data_i, data, sizeof(int) * datanum);

    quick_sort(data,0,datanum-1);
    for(i = 0; i < datanum; i++)
      printf("%d\n", data[i]);




/*
  bubble_sort(data,datanum);
  cpu_b = (double)(e - s)/CLOCKS_PER_SEC;
  printf("bubble_sort: %f\n",cpu_b);
  selection_sort(data_s,datanum);
  cpu_s = (double)(e - s)/CLOCKS_PER_SEC;
  printf("selection_sort: %f\n",cpu_s);
  insertion_sort(data_i,datanum);
  cpu_i = (double)(e - s)/CLOCKS_PER_SEC;
  printf("insertion_sort: %f\n",cpu_i);
*/
/*
  bubble_sort(data,datanum);
  cpu_b = (double)(e - s)/CLOCKS_PER_SEC;
  printf("%f,",cpu_b);
  selection_sort(data_s,datanum);
  cpu_s = (double)(e - s)/CLOCKS_PER_SEC;
  printf("%f",cpu_s);
  insertion_sort(data_i,datanum);
  cpu_i = (double)(e - s)/CLOCKS_PER_SEC;
  printf(",%f\n",cpu_i);
*/




//}

/*
  for(i = 0; i < datanum; i++)
    printf("%d\n", data[i]);
*/

  return 0;
}
