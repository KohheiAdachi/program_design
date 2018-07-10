#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count = 0;

int r_comb(int n,int m)
{
  count++;
  if(m == 0 || m == n)
    return 1;
  else
    return r_comb(n-1,m) + r_comb(n-1,m-1);
}

int d_comb(int n,int m){
  
}

int main (){

}
