#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
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
  base_matrix = malloc(sizeof(int) * n * n);

  if(m == 0){
    return 1;
  }

  for(i=0;i<n;i++){
    matrix[i] = base_matrix + i * n;
  }
  for(i = 0;i<=m;i++){
    matrix[0][i] = 1;
  }
  for(i = 0;i<=n-m;i++){
    matrix[i][0] = 1;
  }

  for(i = 1;i <= n - m; i++){
      for(j=1;j<=m;j++){
        matrix[i][j] = matrix[i][j-1] + matrix[i-1][j];
      }
  }
  return matrix[n-m][m];
  free(matrix);
  free(base_matrix);

}

int main(int argc, char const *argv[]) {

  int n,m;
  clock_t s,e;
  double rt,dt;
  if(argc != 2){
  n = atoi(argv[1]);
  m = atoi(argv[2]);

  s = clock();
  printf("r_comb:%d\n",r_comb(n,m));
  e = clock();
  rt = (double)(e-s)/CLOCKS_PER_SEC;
  printf("count:%d\n",count);
  printf("r_comb time:%lf\n",rt);

  s = clock();
  printf("d_comb:%d\n",d_comb(n,m));
  e = clock();
  dt = (double)(e-s)/CLOCKS_PER_SEC;
  printf("d_comb time:%lf\n",dt);
  }
  else{
    fprintf(stderr,"type:>%s n m \n",argv[0]);
		return 1;
  }



  return 0;
}
