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
  int i,j;
  int **matrix,*base_matrix;

  matrix = malloc(sizeof(int *)*n);
  base_matrix = malloc(sizeof(int)*n*n);

  if(m == 0){
    return 1;
  }

  for(i=0;i<n;i++){
    matrix[x] = base_matrix + i * n;
  }
  for(i = 0;i<=m;i++){
    matrix[0][i] = 1;
  }
  for(i = 0;i<=n-m;i++){
    matrix[i][0] = 1;
  }
  for(i = 0;i <=n-m;i++){
      for(j=1;j<=m;j++){
        matrix[i][j] = matrix[i][j-1] + matrix[i-1][j];
      }
  }
  return matrix[n-m][m];
  free(matrix);
  free(base_matrix);

}

int main(int argc, char const *argv[]) {
  
  return 0;
}
