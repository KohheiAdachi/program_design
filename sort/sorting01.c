#include <stdio.h>
#include <stdlib.h>  /* random, srandom */
#include <time.h>    /* time */
#include <string.h>
typedef int element_type; /*データの型*/
clock_t s, e; /* clock_t は int とほぼ同じ */
double cpu_b,cpu_s,cpu_i,cpu_q,cpu_m,cpu_qd;
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
//find_pivot
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
//partition
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
//クイックソート
void quick_sort(element_type data[],int i,int j){
  int pivotindex,k;
  pivotindex = find_pivot(data,i,j);
  if(pivotindex >= 0){
    k = partition(data,i,j,data[pivotindex]);
    quick_sort(data,i,k-1);
    quick_sort(data,k,j);
  }
}
//マージソート
void Msort(element_type Data[],element_type tmp[],int left,int right){
    int mid,i,j,k;
    if(left>=right)
        return;

    mid = (left+right)/2;
    Msort(Data,tmp,left,mid);
    Msort(Data,tmp,mid+1,right);

    for(i=left;i<=mid;i++)
        tmp[i]=Data[i];
    for(i=mid+1,j=right;i<=right;i++,j--)
        tmp[i]=Data[j];

    i=left;
    j=right;

    for(k=left;k<=right;k++){
        if(tmp[i]<=tmp[j]){
            Data[k]=tmp[i];
            i++;
        }
        else{
            Data[k]=tmp[j];
            j--;
        }
    }
}
//比較用の関数 cmp
int cmp( const void *p, const void *q ) {
    return *(int*)p - *(int*)q;
}

int main(int argc, char *argv[])
{
/*
  int datanum = 100000 ,width = 100;
  int data[datanum];
  int data_b[datanum],data_s[datanum],data_i[datanum];
  int i;
  srandom(time(NULL));


  for(i=1;i<=10;i++){
    datanum = i * 10000;
    printf("datanum:%d\n",datanum);
    gendata(data, datanum, width);

    //配列のコピー
    memcpy(data_s, data, sizeof(int) * datanum);
    memcpy(data_i, data, sizeof(int) * datanum);



  bubble_sort(data,datanum);
  cpu_b = (double)(e - s)/CLOCKS_PER_SEC;
  printf("bubble_sort: %f\n",cpu_b);

  selection_sort(data_s,datanum);
  cpu_s = (double)(e - s)/CLOCKS_PER_SEC;
  printf("selection_sort: %f\n",cpu_s);

  insertion_sort(data_i,datanum);
  cpu_i = (double)(e - s)/CLOCKS_PER_SEC;
  printf("insertion_sort: %f\n",cpu_i);


  bubble_sort(data,datanum);
  cpu_b = (double)(e - s)/CLOCKS_PER_SEC;
  printf("%f,",cpu_b);

  selection_sort(data_s,datanum);
  cpu_s = (double)(e - s)/CLOCKS_PER_SEC;
  printf("%f",cpu_s);

  insertion_sort(data_i,datanum);
  cpu_i = (double)(e - s)/CLOCKS_PER_SEC;
  printf(",%f\n",cpu_i);
}
*/
int datanum = 100000*1000;
//int datanum = 10000;
int width = 100;
int i;
element_type *ori_data,*m_data,*tmp,*q_data,*dq_data;
/*
tmp = (int *)malloc(sizeof(int)*datanum);
ori_data = (int *)malloc(sizeof(int)*datanum);
m_data = (int *)malloc(sizeof(int)*datanum);
q_data = (int *)malloc(sizeof(int)*datanum);
*/
  printf("datanum,Msort,qsort,D_qsort\n");
  for(i=1;i<=1000;i+=10){
    datanum = i * 100000;
    printf("datanum:%d\n",datanum);
    //printf("%d,",datanum);
    tmp = (int *)malloc(sizeof(int)*datanum);
    ori_data = (int *)malloc(sizeof(int)*datanum);
    m_data = (int *)malloc(sizeof(int)*datanum);
    q_data = (int *)malloc(sizeof(int)*datanum);
    dq_data = (int *)malloc(sizeof(int)*datanum);

    gendata(ori_data, datanum, width);

    memcpy(m_data, ori_data, sizeof(int) * datanum);
    memcpy(q_data, ori_data, sizeof(int) * datanum);
    memcpy(dq_data, ori_data, sizeof(int) * datanum);



    s = clock();
    Msort(m_data,tmp,0,datanum-1);
    free(m_data);
    free(tmp);
    e = clock();
    cpu_m = (double)(e - s)/CLOCKS_PER_SEC;
    printf("Merge_sort: %f\n",cpu_m);
    //printf("%f,",cpu_m);


    s = clock();
    quick_sort(q_data,0,datanum-1);
    free(q_data);
    e = clock();
    cpu_q = (double)(e - s)/CLOCKS_PER_SEC;
    printf("quick_sort: %f\n",cpu_q);
    //printf("%f,",cpu_q);

    s = clock();
    qsort((void *)dq_data,datanum,sizeof(dq_data[0]),cmp);
    free(dq_data);
    e = clock();
    cpu_qd = (double)(e - s)/CLOCKS_PER_SEC;
    printf("d_quick_sort: %f\n",cpu_qd);
    //printf("%f\n",cpu_qd);

    free(ori_data);



}
/*
  for(i = 0; i < datanum; i++)
    printf("%d\n", data[i]);
*/

  return 0;
}
