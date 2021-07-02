#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double**  createMatrix(int N) {
	
	int i, j;
	double** mat = (double**)calloc(N , sizeof(double*));
	if(mat == NULL) {
		printf("Allocation error ");
		exit(1);
	}

	for (i=0; i<N; ++i)
	{
		   mat[i] = (double*)calloc(N , sizeof(double));
		   if(mat[i] == NULL) {
				printf("Allocation error ");
				exit(1);
		}		
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

void gaussSeidal() {
	double** mat;
	int N, i , j, k, step = 1;
	double* mat2, *values, *newValues;
	double epsilon, ratio, error, sum;
	
	printf("N sayisini giriniz (bilinmeyenlerin sayisi) : ");
	scanf("%d", &N);
	
	printf("Matrisi kosegendeki katsayilar carpimi max olacak sekilde giriniz ");
	mat = createMatrix(N);
	printMatrix(N, mat);
	
	mat2 = (double*)malloc(N * sizeof(double));
	values = (double*)calloc(N, sizeof(double));
	newValues = (double*)calloc(N, sizeof(double));
	
	printf("Sonuc matrisini giriniz : (matrisin sagdaki sonuc bolumu)\n\n");
	
	for(i = 0; i < N; i++) {
		scanf("%lf", &mat2[i]);
	}	

	printf("Hata oranini giriniz : ");
		scanf("%lf", &epsilon);

	printf("Degiskenlerin baslangic degerlerini giriniz : \n");
	
	for(i = 0; i < N; i++) {
		printf("x%d : ", i);
		scanf("%lf", &values[i]);
	}
	
	for(i = 0; i < N; i++) {
		ratio = mat[i][i];
		
		for(j = 0; j < N; j++) {
			mat[i][j] = mat[i][j] / ratio;
		}
		
		mat2[i] = mat2[i] / ratio;
		
	}
	
	printf("Step\t");
	for(i = 0; i < N; i++) {
		printf("x%d\t\t",i);
	}
	printf("Error");
	printf("\n");
	
	printf("%d\t", step);
	for(i = 0; i < N; i++) {
		printf("%f\t",values[i]);
	}
	printf("\n");
	
	do {
		for(i = 0; i < N; i++) {
			sum = 0;
			for(j = 0; j < i; j++) {
				sum -= mat[i][j] * newValues[j];
			}
			for(j = j + 1; j < N; j++) {
				sum -= mat[i][j] * values[j];
			}
			
			sum += mat2[i];
			newValues[i] = sum;
		}
		
		error = fabs(newValues[0] - values[0]);
		
		for(i = 1; i < N; i++) {
			if(fabs(newValues[i] - values[i]) > error) 
				error = fabs(newValues[i] - values[i]);
		}
		
		step++;
		
		printf("%d\t", step);
		for(i = 0; i < N; i++) {
			values[i] = newValues[i];
			printf("%f\t", newValues[i]);
		}
		printf("%f", error);
		printf("\n");
		
		
	}while(error > epsilon);
			
		
}

int main() {
	
	gaussSeidal();
}
