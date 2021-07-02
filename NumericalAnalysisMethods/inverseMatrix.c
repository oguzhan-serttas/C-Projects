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

double** createUnitMatrix(int N) {
	int i;
	double** mat = (double**)calloc(N , sizeof(double*));

	for (i=0; i<N; ++i)
	{
		   mat[i] = (double*)calloc(N , sizeof(double));		
	}
	
	for(i = 0; i < N; i++) {
		mat[i][i] = 1;
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

void inverseMatrix() {
	double** mat;
	double** unitMat;
	double ratio;
	double* temp;
	int N, i , j, k, flag = 0;
	
	printf("N sayisini giriniz (satir ve sutun boyutu) : ");
	scanf("%d", &N);
	
	mat = createMatrix(N);
	printMatrix(N, mat);
	
	unitMat = createUnitMatrix(N);
	
	if(mat[0][0] == 0) {	//ilk eleman 0 ise baþka bir satýrla yer deðiþtir
		i = 0; 
		while(i < N && flag == 0) {
			i++;
			if(mat[i][0] != 0) {
				temp = mat[0];
				mat[0] = mat[i];
				mat[i] = temp;
				temp = unitMat[0];
				unitMat[0] = unitMat[i];
				unitMat[i] = temp;
				flag = 1;
			}
		}
	}
	
	printMatrix(N, mat);
	
	for(i = 0; i < N; i++) {
	
		ratio = mat[i][i];		
		for(j = 0; j < N; j++) {	// mat[i][i] ' nin 1 yapýlmasý
			mat[i][j] = mat[i][j] / ratio;
			unitMat[i][j] = unitMat[i][j] / ratio;
		}
		
		for(k = 0; k < N; k++) {
			if(k != i) {
				ratio = mat[k][i];	//deðer kaybolmasýn diye ratio ' da tuttum
				for(j = 0; j < N; j++) {
					mat[k][j] =  mat[k][j] - mat[i][j] * ratio;
					unitMat[k][j] = unitMat[k][j] - unitMat[i][j] * ratio;
				}
			}
		}	
		
	}
	
	printf("\nMatrisimizin son hali : \n");
	printMatrix(N, mat);
	printf("\nMatrisin tersi : \n");
	printMatrix(N, unitMat);
	
}


int main() {
	
	inverseMatrix();
}
