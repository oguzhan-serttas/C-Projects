#include <stdio.h>
#include <stdlib.h>

double**  createMatrix(int N) {
	
	int i, j;
	double** mat = (double**)calloc(N , sizeof(double*));

	for (i=0; i<N; ++i)
	{
		   mat[i] = (double*)calloc(N , sizeof(double));		
	}
	
	printf("Matris degerlerini giriniz : \n\n");
	
	for (i = 0; i < N; ++i) {
    	for (j = 0; j < N; ++j) {
       		scanf("%lf", &mat[i][j]);
   	 	}
	}
	
	return mat;

}


void printMatrix(int N, double** mat) {
	int i, j;
	printf("\n");
	for (i = 0; i < N; ++i) {
    	for (j = 0; j < N; ++j) {
       		printf("%.2lf ", mat[i][j]);
   	 	}
   	 	printf("\n");
	}
}

void gaussElimination() {
	double** mat;
	double ratio;
	int N, i , j, k;
	double* mat2, *mat3;
	
	printf("N sayisini giriniz (bilinmeyenlerin sayisi) : ");
	scanf("%d", &N);
	
	
	mat = createMatrix(N);
	printMatrix(N, mat);
	
	mat2 = (double*)malloc(N * sizeof(double));
	
	printf("Sonuc matrisini giriniz : \n\n");
	for(i = 0; i < N; i++) {
		scanf("%lf", &mat2[i]);
	}	

	
	for(i = 0; i < N; i++) {
	
		ratio = mat[i][i];		
		for(j = 0; j < N; j++) {	// mat[i][i] ' nin 1 yapýlmasý
			mat[i][j] = mat[i][j] / ratio;			
		}
		mat2[i] = mat2[i] / ratio;
		
	
		
		for(k = i + 1; k < N; k++) {
			
				ratio = mat[k][i];	//deðer kaybolmasýn diye ratio ' da tuttum
				for(j = 0; j < N; j++) {
					mat[k][j] =  mat[k][j] - mat[i][j] * ratio;
											
			}
				mat2[k] =  mat2[k] - mat2[i] * ratio;
		}
		

		
		
		
	}
	

	
	printf("\nMatrisimizin son hali : \n");
	printMatrix(N, mat);
	
	printf("\nSonuc matrisi : \n");
	for(i = 0; i < N; i++) {
		printf("%f", mat2[i]);
		printf("\n");
	}
	
	mat3 = (double*)malloc(N * sizeof(double));
	
	mat3[N-1] = mat2[N-1] / mat[N-1][N-1];
	
	for (i = N-2; i >= 0; i--) {
		mat3[i] = mat2[i];
		
		for( j = i + 1; j < N; j++) {
			mat3[i] = mat3[i] - mat[i][j] * mat3[j];
		}
		
		mat3[i] = mat3[i] / mat[i][i];
	}
	
	printf("\nCevaplar:\n");
	 for(i=0;i<N;i++)
	 {
	  	printf("sonuc[%d] = %0.3f\n",i, mat3[i]);
	 }
	
}


int main() {
	
	gaussElimination();
}
