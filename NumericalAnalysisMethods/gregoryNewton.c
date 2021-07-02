#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double**  createMatrix(int N, int M) {
	
	int i, j;
	double** mat = (double**)calloc(N , sizeof(double*));

	for (i=0; i<N; ++i)
	{
		   mat[i] = (double*)calloc(M , sizeof(double));		
	}
	
	return mat;

}

void enterpolation(double** mat, double x0, double h, int n){
	 
	 int j, i, k, fact;
	 double x, temp, temp2, sum;
	 double** forwardDif = createMatrix(n, n);
	
	 i = 0;
	 while(i >= 0){
	 	if(i == 0){ 
	 		for(j=0; j<n-1; j++)
	 			forwardDif[i][j] = mat[j+1][1] - mat[j][1];
	 }
	 	else{ 
	 		for(j=0;j<n-1-i;j++)
	 			forwardDif[i][j] = forwardDif[i-1][j+1] - forwardDif[i-1][j];
	 }
	 
	 if(forwardDif[i][0] == forwardDif[i][1]) {
	 	temp2 = i;
	 	i = -1;
	 }
	 
	 else i++;
	 }
	 
	 i = temp2;

	 printf("\n\n Hangi x degeri icin cevabi bulmak istiyorsunuz : ");
	 scanf("%lf",&x);
	 
	 sum = mat[0][1];

	 for(j=1; j<=i+1; j++){
	 	fact=1;
		for(k=1; k<=j; k++) {
		 	fact *= k;
		}
	 
	 	temp=1;
	 
		for(k=0; k<j; k++)  {
		 	temp *= x - mat[k][0];
		 }
	 	 	
	 	sum += (temp/pow(h,j)) * (forwardDif[j-1][0]/fact);
	 
	 }
	 printf("\n\nF(%.2lf) = %.2lf\n",x, sum);
}

int main() {
	double** mat;
	int n, i;
	double x0, h;
	
	printf("n : "); scanf("%d", &n);
	printf("x0 : "); scanf("%lf", &x0);
	printf("h : ");	scanf("%lf", &h);
	
	mat = createMatrix(n, 2);
	
	printf("\n\n");
	
	for(i = 0; i < n; i++) {
		mat[i][0] = x0 + i * h;
		printf("F(%.2lf) : ", x0 + i * h);
		scanf("%lf", &mat[i][1]);
	}

	enterpolation(mat, x0, h, n);
	
}
