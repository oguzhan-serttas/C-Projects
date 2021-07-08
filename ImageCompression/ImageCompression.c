
/* This program encode and decode the PGM file using RLE and 
allows the user to change the data of the PGM while the PGM is in encoded format*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100
#define MAX2 1000


typedef struct PGM {
	char type[3];
	int row;
	int column;
	int maxValue;
	int** data;
}PGM;

struct encodedData {
	
	struct encodedData* next;
	int frequency;
	int colorCode;
	
};

typedef struct encodedPGM {
	
	int row;
	int column;
	struct encodedData* head;
	
}encodedPGM;


int**  createMatrix(int N, int M);
void printMatrix(int N, int M, int** mat);
encodedPGM* initEncodedPGM();
void readPGM(PGM* pgm, char* fileName, FILE* fp);
void encodePGM(PGM* pgm, FILE* fp);
void readEncodedPGM(encodedPGM* pgmEncoded, FILE* fp);
void printEncodedPGM(struct encodedPGM* pgmEncoded);
int encodedPgmControl(struct encodedPGM* pgmEncoded);
void writeDecodedPGM(PGM* pgm, FILE* fp);
void decodePGM(encodedPGM* pgmEncoded, FILE* fp);
void changeColorCode(int oldColor, int newColor, FILE* fp);
void printHistogram(FILE* fp);
void changePixel(int row, int column, int colorCode, FILE* fp);

int main() {

	FILE* filePointer;
	int selection, flag = 1, oldColor, newColor, row, column, colorCode;
	char fileName[30];
	PGM* pgm = (PGM*)calloc(1, sizeof(PGM)); 
	struct encodedPGM* pgmEncoded = initEncodedPGM();
	
	if (pgm == NULL) {
		printf("Allocation error");
		exit(1);
	}
	
	
	
	
	while(flag == 1) {
		printf("\nMenu : \n");
		printf("1 : Encode operation\n");
		printf("2 : Decode operation\n");
		printf("3 : Change color code\n");
		printf("4 : Change pixel\n");
		printf("5 : Print Histogram\n");
		printf("6 : Exit\n");
		
		scanf("%d", &selection);
		switch(selection) {
			case 1:	// encode operation 
				printf("File Name : ");
				scanf("%s", fileName);
					
				readPGM(pgm, fileName, filePointer);
				encodePGM(pgm, filePointer);				
				break;
				
			case 2:	//decode
				decodePGM(pgmEncoded, filePointer);	
				break;
			
			case 3:	//changeColorCode
				printf("\nOld Color : "); scanf("%d", &oldColor);
				printf("New Color : "); scanf("%d", &newColor);
				
				changeColorCode(oldColor, newColor, filePointer);
				break;
			
			case 4://changePixel
				printf("row : "); scanf("%d", &row);
				printf("column : "); scanf("%d", &column);
				printf("Color Code : "); scanf("%d", &colorCode);
				changePixel(row, column, colorCode, filePointer);
				break;
				
			case 5://printHistogram
				printHistogram(filePointer);
				break;
			default:
				flag = 0;
				
		}
	
	}
	
	free(pgm);
	free(pgmEncoded);

	
}



int**  createMatrix(int N, int M) {
	
	int i, j;
	int** mat = (int**)calloc(N , sizeof(int*));
	
	if (mat == NULL) {
		printf("Allocation error");
		exit(1);
	}

	for (i=0; i<N; ++i)
	{
		   mat[i] = (int*)calloc(M , sizeof(int));	
		   
		   if (mat[i] == NULL) {
				printf("Allocation error");
				exit(1);
			}	
	}
		
	return mat;

}


void printMatrix(int N, int M, int** mat) {
	int i, j;
	printf("\n");
	for (i = 0; i < N; ++i) {
    	for (j = 0; j < M; ++j) {
       		printf("%.3d ", mat[i][j]);
   	 	}
   	 	printf("\n");
	}
}

encodedPGM* initEncodedPGM() {
	
	encodedPGM* pgm = (encodedPGM* )malloc(sizeof(encodedPGM));
			
	if (pgm == NULL) {
		printf("Allocation error");
		exit(1);
	}
	
	pgm->head = NULL;
	
	return pgm;
}

void readPGM(PGM* pgm, char* fileName, FILE* fp){
	
	char* buffer = (char*)calloc(MAX , sizeof(char*));
	int i, j;
	
	if (buffer == NULL) {
		printf("Allocation error");
		exit(1);
	}

	fp = fopen(fileName, "r");
	
	if (!fp) {
        printf("Error: Unable to open file %s.\n\n", fileName);
        exit(1);
      }
	
	fgets(buffer, MAX, fp);
	strcpy(pgm->type , buffer);
	
	if(strcmp(pgm->type , "P2\n") != 0) {
		printf("This file is not in P2 type !!");
		exit(1);
	}
	
	fgets(buffer, MAX, fp);
	pgm->column = atoi(strtok(buffer, " "));
	pgm->row = atoi(strtok(NULL, " "));
	
	fgets(buffer, MAX, fp);
	pgm->maxValue = atoi(buffer);
	
	pgm->data = createMatrix(pgm->row, pgm->column);
	
	i = 0;
	while(fgets(buffer, MAX, fp)) {
		
		pgm->data[i][0] = atoi(strtok(buffer, " "));
    	
		for(j = 1; j < pgm->column; j++) {
    		pgm->data[i][j] = atoi(strtok(NULL, " "));
		}
		
		i++;
	}
	
	printf("PGM File is successfully read \n\n");
	printf("%s", pgm->type);
	printf("%d %d\n", pgm->column, pgm->row);
	printf("%d", pgm->maxValue);
	printMatrix(pgm->row, pgm->column, pgm->data);
	
	free(buffer);
	fclose (fp);
		
}

void encodePGM(PGM* pgm, FILE* fp) {
	
	int prev, i, j, counter = 0;
	
	fp = fopen ("test_encoded.txt","w");
	
	if (!fp) {
        printf("Error: Unable to open file test_encoded.txt.\n\n");
        exit(1);
    }
    
    printf("\nEncoded pgm data : ");
	 
    fprintf(fp, "%d %d ", pgm->row, pgm->column);
    printf("\n%d %d ", pgm->row, pgm->column);
    
    prev = pgm->data[0][0];
    
    for(i = 0; i < pgm->row; i++){
       for(j = 0; j < pgm->column; j++) {
       		if(pgm->data[i][j] == prev) {
      			counter++;
			  }
			else {
			    fprintf(fp, "%d %d ", counter, prev);
			    printf("%d %d ", counter, prev);
			  	prev = pgm->data[i][j];
			  	counter = 1;
			  }
	   }
   }
   
   	fprintf(fp, "%d %d ", counter, prev);
  	printf("%d %d ", counter, prev);

   	
    fclose (fp);
}

void readEncodedPGM(encodedPGM* pgmEncoded, FILE* fp) {
	
	fp = fopen("test_encoded.txt", "r");
	char* token;
	int i;
	struct encodedData* prev, *cur;
	
	if (!fp) {
        printf("Error: Unable to open file test_encoded.txt.\n\n");
        exit(1);
      }
      
    char* buffer = (char* )malloc((MAX2) * sizeof(char));
    
	if (buffer == NULL) {
		printf("Allocation error");
		exit(1);
	}
	
	fgets(buffer, MAX2, fp);
	

	pgmEncoded->row = atoi(strtok(buffer, " "));
	pgmEncoded->column = atoi(strtok(NULL, " "));

	
	
	pgmEncoded->head = (struct encodedData*)malloc(sizeof(struct encodedData));
	pgmEncoded->head->frequency = atoi(strtok(NULL, " "));
	token = strtok(NULL, " ");
	pgmEncoded->head->colorCode = atoi(token);
	prev = pgmEncoded->head;
	prev->next = NULL;
	i = 0;
	token = strtok(NULL, " ");
	while (token != NULL)
    {
       	
	    if( i % 2 == 0) {
	       	cur  = (struct encodedData*)malloc(sizeof(struct encodedData));
	       	cur->frequency = atoi(token);
	       	cur->next = NULL;
	  
		} 
		else {
			cur->colorCode = atoi(token);
			prev->next = cur;
			prev = cur;
				
		}
    	
    	 
        i++;
        token = strtok(NULL, " ");
    }
    

   

    free(buffer);
    fclose(fp);
}

void printEncodedPGM(struct encodedPGM* pgmEncoded) {
	struct encodedData* temp = pgmEncoded->head;

	
	printf("\nEncodedPGM : \n");
	printf("%d %d ", pgmEncoded->row, pgmEncoded->column);
	

	while(temp != NULL) {			
		printf("%d ", temp->frequency);
		printf("%d ", temp->colorCode);
		temp = temp->next;
	}
	
	printf("\n");
}


int encodedPgmControl(struct encodedPGM* pgmEncoded) {
	
	struct encodedData* cur = pgmEncoded->head;
	int prevColorCode;
	
	int size = pgmEncoded->row * pgmEncoded->column;
	int sumOfFreq = 0;
	int colorCode;
	
	printf("\n\nControl Steps : \n");
	
	sumOfFreq += cur->frequency;
	printf("\n\nsumOfFreq = %d , expectedSize = %d\n", sumOfFreq, size);
	if(sumOfFreq > size) {
		printf("Frequency is bigger than size ! \n");
		return 1;
	}
	colorCode = cur->colorCode;
	printf("colorCode = %d\n", colorCode);
	if(colorCode > 255 || colorCode < 0) {
		printf("Invalid colorCode \n");
		return 1;
	}
	
	prevColorCode = colorCode;
	cur = cur->next;
	
	while(cur != NULL) {
		
		sumOfFreq += cur->frequency;
		printf("\n\n\nsumOfFreq = %d , expectedSize = %d \n", sumOfFreq, size);		
		if(sumOfFreq > size) {
			printf("Frequency is bigger than size ! \n");
			return 1;
		}
		
		colorCode = cur->colorCode;
		printf("colorCode = %d\n", colorCode);	
		if(colorCode > 255 || colorCode < 0) {
			printf("Invalid colorCode \n");
			return 1;
		}
		
		printf("Prev Color Code : %d  , Current Color Code : %d\n", prevColorCode, colorCode);
		if(prevColorCode == colorCode) {
			printf("Wrong encoding !! \n");
			return 1;
		}
		
		prevColorCode = colorCode;
		cur = cur->next;
	}
	
	printf("\nControl operation is successful\n");
	return 0;
}


	
void writeDecodedPGM(PGM* pgm, FILE* fp) {
	
	int i, j;
	
	fp = fopen("test_decoded.pgm", "w");
	
	if (!fp) {
        printf("Error: Unable to open file test_decoded.pgm.\n\n");
        exit(1);
      }
	
	fprintf(fp, "%s", pgm->type);
	fprintf(fp, "%d %d\n", pgm->column, pgm->row);
	fprintf(fp, "%d\n", pgm->maxValue);
	
	for(i = 0; i < pgm->row; i++) {
		for(j = 0; j < pgm->column; j++) {
			fprintf(fp, "%d ", pgm->data[i][j]);
		}
		fprintf(fp, "\n");
	}
	
	printf("\n\nDecoded pgm : \n");
	
	printMatrix(pgm->row, pgm->column, pgm->data);
	
	fclose(fp);
}


void decodePGM(encodedPGM* pgmEncoded, FILE* fp) {
	
	int i, j;
	struct encodedData* cur;
	PGM* pgm = (PGM*)calloc(1, sizeof(PGM)); 
	
	readEncodedPGM(pgmEncoded, fp);
	if(encodedPgmControl(pgmEncoded) == 1) {
		printf("\nencoded PGM file is not valid!!\n");
		return;
	}
	
	
	strcpy(pgm->type , "P2\n");	
	pgm->column = pgmEncoded->column;
	pgm->row = pgmEncoded->row;
	pgm->maxValue = 255;	
	pgm->data = createMatrix(pgm->row, pgm->column);
	
	cur = pgmEncoded->head;

	int counter = 0;
	for(i = 0; i < pgm->row; i++) {
		for(j = 0; j < pgm->column; j++) {
			
			if(cur->frequency > counter) {
				pgm->data[i][j] = cur->colorCode;
				counter++;
			}
			else {
				cur = cur->next;
				pgm->data[i][j] = cur->colorCode;
				counter = 1;
			}
		
		}
	}

	writeDecodedPGM(pgm, fp);
	
	
	for (i = 0; i < pgm->row; i++) {
		free(pgm->data[i]);
	}
	
	free(pgm->data);	
	free(pgm);//
}

void changeColorCode(int oldColor, int newColor, FILE* fp) {
	
	struct encodedData* temp, *temp2, *prev = NULL;	
	encodedPGM* pgmEncoded = initEncodedPGM();
	readEncodedPGM(pgmEncoded, fp);
	
	if(newColor > 255 || newColor < 0) {
		printf("\n\nInvalid new Color !!\n\n");
		return;
	}
	
	fp = fopen ("test_encoded.txt","w");
	
	if (!fp) {
        printf("Error: Unable to open file test_encoded.txt.\n\n");
        exit(1);
    }
	

	
	fprintf(fp, "%d %d ", pgmEncoded->row, pgmEncoded->column);
	
	temp = pgmEncoded->head;

	while(temp != NULL) {			
		if(temp->colorCode == oldColor) {
			temp->colorCode = newColor;
		}
		
		if(prev != NULL && prev->colorCode == temp->colorCode) {
			prev->frequency += temp->frequency;
			temp2 = temp;
			prev->next = temp->next;
			temp = prev;
			free(temp2);
		}
		
		prev = temp;
		temp = temp->next;
	}
	
	printEncodedPGM(pgmEncoded);
	
	temp = pgmEncoded->head;
	
	while(temp != NULL) {
		fprintf(fp, "%d %d ", temp->frequency, temp->colorCode);
		prev = temp;
		temp = temp->next;
		free(prev);
	}
	
	free(pgmEncoded);
	fclose(fp);	
}


void printHistogram(FILE* fp) {
	
	struct encodedData* head = (struct encodedData*)malloc(sizeof(struct encodedData));
	struct encodedData* cur;
	struct encodedData* temp;
	struct encodedData* temp2;
	struct encodedData* prev;
	encodedPGM* pgmEncoded = initEncodedPGM();

	readEncodedPGM(pgmEncoded, fp);
	cur = pgmEncoded->head;

	head->colorCode = cur->colorCode;
	head->frequency = cur->frequency;
	head->next = NULL;

	cur = cur->next;

	while(cur != NULL) {
		temp = head;
		
		if(cur->colorCode < temp->colorCode ) {
			temp2 = (struct encodedData*)malloc(sizeof(struct encodedData));
			temp2->colorCode = cur->colorCode;
			temp2->frequency = cur->frequency;
			temp2->next = head;
			head = temp2;
		}
		else {
			
			while(temp != NULL && cur->colorCode > temp->colorCode) {
				prev = temp;
				temp = temp->next;
			}
			
			if(temp == NULL) {
				temp2 = (struct encodedData*)malloc(sizeof(struct encodedData));
				temp2->colorCode = cur->colorCode;
				temp2->frequency = cur->frequency;
				temp2->next = NULL;
				prev->next = temp2;
			}
			else if(cur->colorCode < temp->colorCode){
				temp2 = (struct encodedData*)malloc(sizeof(struct encodedData));
				temp2->colorCode = cur->colorCode;
				temp2->frequency = cur->frequency;
				temp2->next = temp;
				prev->next = temp2;
			}
			else {
				temp->frequency += cur->frequency;
			}
		}
		
		cur = cur->next;
	}
	
	printf("\nHistogram : \n");	
	temp = head;
	while(temp != NULL) {	
		printf("\nColor Code : %d , Freq : %d\n", temp->colorCode, temp->frequency);		
		temp = temp->next;
	}
	
	printf("\n");
	
	
}


void changePixel(int row, int column, int colorCode, FILE* fp) {
	
	int orderCount;
	struct encodedData* cur;
	struct encodedData* prev = NULL;
	struct encodedData* temp;
	struct encodedData* temp2;
	encodedPGM* pgmEncoded = initEncodedPGM();	
	readEncodedPGM(pgmEncoded, fp);
	
	if(pgmEncoded->row <= row || pgmEncoded->column <= column) {
		printf("\n\nInvalid input !! \n\n");
		return;
	}
		
	fp = fopen ("test_encoded.txt","w");
	
	if (!fp) {
        printf("Error: Unable to open file test_encoded.txt.\n\n");
        exit(1);
    }	
		
	cur = pgmEncoded->head;
	orderCount = row * pgmEncoded->column + column + 1;
	
	
	while(cur != NULL && orderCount > 0) {
		
		if(orderCount - cur->frequency <= 0 && colorCode != cur->colorCode) {
			if(orderCount == 1) {
				
				temp = (struct encodedData*)malloc(sizeof(struct encodedData));
				temp->colorCode = colorCode;
				temp->frequency = 1;
				
			
				if(prev != NULL) {
					prev->next = temp;				
				}
				else {
					pgmEncoded->head = temp;
					
				}
				
				temp->next = cur;
				cur->frequency -= 1;
				if(cur->frequency == 0) {
					temp2 = cur;
					temp->next = cur->next;
					free(cur);
				}			
			}
			else if(orderCount == cur->frequency) {
				temp = (struct encodedData*)malloc(sizeof(struct encodedData));
				temp->colorCode = colorCode;
				temp->frequency = 1;
				temp->next = cur->next;
				
				cur->next = temp;
				cur->frequency -= 1;
			}
			else {
				temp = (struct encodedData*)malloc(sizeof(struct encodedData));
				temp->colorCode = colorCode;
				temp->frequency = 1;
				
				temp2 = (struct encodedData*)malloc(sizeof(struct encodedData));
				temp2->colorCode = cur->colorCode;
				temp2->frequency = cur->frequency - orderCount;
				
				cur->frequency = orderCount - 1;
				
				temp2->next = cur->next;
				cur->next = temp;
				temp->next = temp2; 
				
			}
			
			orderCount = -1;
		}
		
		prev = pgmEncoded->head;
		if(orderCount <= 0) {
			temp = prev;
			temp = temp->next;
			while(temp != NULL) {
				if(prev->colorCode == temp->colorCode) {
					prev->frequency += temp->frequency;
					temp2 = temp;
					prev->next = temp->next;
					temp = prev;
					free(temp2);
				}
				
				prev = temp;
				temp = temp->next;
			}
		} 
		
	
		
		orderCount = orderCount - cur->frequency;
		prev = cur;
		cur = cur->next;
	}
	

	printEncodedPGM(pgmEncoded);
	
	fprintf(fp, "%d %d ", pgmEncoded->row, pgmEncoded->column);
	
	temp = pgmEncoded->head;

	while(temp != NULL) {						
		fprintf(fp, "%d %d ", temp->frequency, temp->colorCode);
		
		temp = temp->next;
	}

	
	fclose(fp);
}
