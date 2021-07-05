#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40

struct node {
	char str[MAX];
	int searchNum;
	struct node* next;
};

struct Graph {
	int numVertices;
	struct node** adjList;
};


struct node* createNode(char*, int);
struct Graph* createGraph();
void printGraph(struct Graph*);
struct Graph* mergeGraphs(struct Graph*, struct Graph*);
void printRelated(struct Graph*, char*);

int main() {
	char str[MAX];
	
	printf("ilk grafin olusturulma islemi : \n");
	struct Graph* graph1 = createGraph();
	printf("\nilk graf olusturuldu \n");
	printGraph(graph1);
	
	printf("\nikinci grafin olusturulma islemi :\n");
	struct Graph* graph2 = createGraph();
	printf("\nikinci graf olusturuldu \n");
	printGraph(graph2);
	
	printf("\nmerge islemi yapiliyor ... \n");
	graph1 = mergeGraphs(graph1, graph2);
	printf("\nmerge islemi tamamlandi. Elde edilen graf : \n");
	printGraph(graph1);
	
	printf("Sorgulanacak string : ");
	scanf(" %[^\n]%*c", str);

	 do{
		printRelated(graph1, str);
		if(strcmp(str, "exit") != 0) {
			printf("\nGrafin son hali : \n");
			printGraph(graph1);
		}	
		printf("Sorgulanacak string (cikis yapmak icin exit yazin) : ");
		scanf(" %[^\n]%*c", str);
	}while(strcmp(str,"exit") != 0);
	
}


struct node* createNode(char* str, int searchNum) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  if(newNode == NULL) {
  		printf("allocation error");
  		exit(1);
  }
  strcpy(newNode->str, str);
  newNode->searchNum = searchNum;
  newNode->next = NULL;
  return newNode;
}

struct Graph* createGraph() {
	int i;
	int vertices;
	int searchNum;
	char str[MAX];
	struct node* newNode;
	struct node* temp;
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	if(graph == NULL) {
  		printf("allocation error");
  		exit(1);
  }
	
	printf("Dugum sayisini giriniz : ");
	scanf("%d", &vertices);
	
	graph->numVertices = vertices;
	graph->adjList = (struct node**)malloc(vertices * sizeof(struct node*));
	if(graph->adjList == NULL) {
  		printf("allocation error");
  		exit(1);
  }
	
	
	
	printf("Sorgu string ' ini giriniz : ");
	scanf(" %[^\n]%*c", str);	
	printf("Sorgu sayisini giriniz : ");
	scanf("%d", &searchNum);
	
	newNode = createNode(str, searchNum);
	graph->adjList[0] = newNode;
	temp = newNode;
	
	for (i = 1; i < vertices; i++) {
		printf("%d. dugumun sorgu stringi : " , i);
		scanf(" %[^\n]%*c", str);	
		printf("%d. dugumun sorgu sayisini giriniz : ", i);
		scanf("%d", &searchNum);
		
		newNode = createNode(str, searchNum);
		newNode->next = createNode(graph->adjList[0]->str, graph->adjList[0]->searchNum);
		
		
		temp->next = createNode(str, searchNum);
		temp = temp->next;
		
		graph->adjList[i] = newNode;
	}
    
    return graph;
	
	
	
}

void printGraph(struct Graph* graph) {
	int i;
	struct node* temp;
  	for (i = 0; i < graph->numVertices; i++) {
    	temp = graph->adjList[i];
   	
    	while (temp) {
      		printf("%s (%d) -> ", temp->str, temp->searchNum);
      		temp = temp->next;
    	}
    	
	printf("\n");
  }
}

struct Graph* mergeGraphs(struct Graph* graph1, struct Graph* graph2) {
	struct node* temp1;
	struct node* temp2;
	struct node* cur;
	struct node* prev;
	int flag;
	int i, j;
	int counter = 0;
	
	
	i = 0;

	while(i < graph1->numVertices) {
		temp2 = graph2->adjList[0];
		temp1 = graph1->adjList[i];
		flag = 0;
		
		j = 0;
		while(flag == 0 && temp2 != NULL) {
			if(strcmp(temp1->str, temp2->str) == 0) {
				graph2->adjList[j]->searchNum = -graph2->adjList[j]->searchNum - 1;	//silinecek olan node ' larýn searchNum ' ýný negatife çevirerek iþaretledim
				flag = 1;
			}
			else {
				temp2 = temp2->next;
				j++;
			}
		}
		
		if(flag == 1) {	//flag = 1 ise ortak olan string bulunmuþtur
			counter++;	//ortak olan string sayýsýný gösteriyor
			temp2 = graph1->adjList[i];
			while(temp2->next != NULL) {
				temp2 = temp2->next;
			}
			temp2->next = createNode(graph2->adjList[0]->str, graph2->adjList[0]->searchNum);
		}

		
		i++;
		
	}
	
	graph1->numVertices += graph2->numVertices - counter;
	graph1->adjList = realloc(graph1->adjList,   graph1->numVertices * sizeof(struct node*));
	
	
	for(j = 0; j < graph2->numVertices; j++) {
		if(graph2->adjList[j]->searchNum < 0) {
			cur = graph2->adjList[j];
			while(cur != NULL) {
				prev = cur;
				cur = cur->next;
				free(prev);			//2. grafýn kullanýlmayacak düðümlerini free ediyorum
			}
		}
		else {
			graph1->adjList[i] = graph2->adjList[j];	
			i++;
		}
	}
	
	free(graph2->adjList);
	
	
	
	return graph1;
	
}

void printRelated(struct Graph* graph, char* str) {
	struct node* temp;
	struct node* temp1;
	struct node* temp2;
	struct node* first;
	struct node* second;
	struct node* third;
	int i, j;
	
	
	
	
	i = 0;
	while(i < graph->numVertices && strcmp(str, graph->adjList[i]->str) != 0){
		i++;
	}
	
	if(i == graph->numVertices) {
		printf("Not found \n");
		return;
	} 
	else {
	  	for (j = 0; j < graph->numVertices; j++) {
    		temp2 = graph->adjList[j];
   	
    	while (temp2) {
      		if(strcmp(temp2->str, graph->adjList[i]->str) == 0)
      			temp2->searchNum++;
      			
      		temp2 = temp2->next;
    	}
		 
    }
  }
	
	temp = graph->adjList[i]->next;
	first = temp;
	temp = temp->next;
	if(temp == NULL) {		// 1 tane baðlý düðüm olma durumu
		printf("Related Searches : \n");	
		printf("%s (%d)\n", first->str, first->searchNum);
		return;
	}
	second = temp;
	temp = temp->next;
	if(temp == NULL) {	// 2 tane baðlý düðüm olma durumu
		printf("Related Searches : \n");
		printf("%s (%d)\n", first->str, first->searchNum);
		printf("%s (%d)\n", second->str, second->searchNum);
		return;
	}
	third = temp;
	
	if(third->searchNum > first->searchNum) {
		temp1 = third;
		third = first;
		first = temp1;
	}
	
	if(third->searchNum > second->searchNum) {
		temp1 = third;
		third = second;
		second = temp1;
	}
	
	if(second->searchNum > first->searchNum) {
		temp1 = first;
		first = second;
		second = temp1;
	}										// first > second > third þekline getirdim
	
	

		
	while(temp->next != NULL) {
		temp = temp->next;
		if(temp->searchNum > first->searchNum) {
			third = second;
			second = first;
			first = temp;
		}
		else if (temp->searchNum > second->searchNum) {
			third = second;
			second = temp;
		}
		else if(temp->searchNum > third->searchNum) {
			third = temp;
		}
		
		
		
	}
	
	printf("Related Searches : \n");
	printf("%s (%d)\n", first->str, first->searchNum);
	printf("%s (%d)\n", second->str, second->searchNum);
	printf("%s (%d)\n", third->str, third->searchNum);
	
	
}
