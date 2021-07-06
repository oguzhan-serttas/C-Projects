#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// I used Left-Child, Right-Sibling Representation of Tree
// This program is the representation of the structure of the directory in the operation system

struct Node {
	char name[40];
	struct Node* firstChild;
	struct Node* sibling;
	struct Node* parent;							
};


struct Node* init();	
struct Node* findChild(struct Node*, char*);	
void addChild(struct Node*, char*);
void removeChild(struct Node*, char*);
void display(struct Node*);
void printChildNum(struct Node*);




int main() {
	char line[50];
	char* command;		
	int flag = 0;
	
	struct Node* root = init();
	struct Node* currentNode = root;
	struct Node* temp;



while (flag == 0) {
	
	printf("> ");
	
	scanf(" %[^\n]%*c", line);		
	
	command = strtok(line, " ");		
	
	
	
	if (strcmp(command, "mkdir") == 0) {
	
		strcpy(command, strtok(NULL, " "));
		
		addChild (currentNode, command);
			
	}
	
	
	else if (strcmp(command, "chdir") == 0) {
	
		strcpy(command, strtok(NULL, " "));
		
		if(strcmp(command, "..") == 0) {
			if(currentNode->parent == NULL) {
				printf("> Your location is root directory. You can not change directory\n");
			}
			else {
				currentNode = currentNode->parent;
			}
		}
		
		else {
			temp = findChild(currentNode, command);
			if (temp == NULL) 
				printf("> can't change directory. The directory does not exist\n");
			else
				currentNode = temp;
			
		}		
	}
	
	
	
	else if(strcmp(command, "rmdir") == 0) {
	
		strcpy(command, strtok(NULL, " "));			
		removeChild(currentNode, command);
		
	}
	
	
	
	
	else if(strcmp(command, "dir") == 0) {
		
		display(currentNode);
		
	}
	
	
	
	else if(strcmp(command, "count") == 0) {
		printChildNum(currentNode);
	}

	
	else if(strcmp(command, "exit") == 0) {
		flag = 1;
		printf("> Exit");
	}
	
}

	
}



struct Node* init() {
	
	struct Node* root = (struct Node *)malloc(sizeof(struct Node));
			
	if (root == NULL) {
		printf("Allocation error");
		exit(1);
	}
	
	strcpy(root->name, "root");	
	root->firstChild = NULL;
	root->sibling = NULL;
	root->parent = NULL;
	
	return root;
	
}




struct Node* findChild(struct Node* currentNode, char* name) {		
	
	struct Node* temp;
	
	temp = currentNode->firstChild;
	
	if(temp == NULL) {
		return NULL;
	}
	
	while(temp != NULL && strcmp(temp->name, name) != 0) {
		temp = temp->sibling;
	}
	
	if(temp == NULL) {
		return NULL;
	}
	
	return temp;
				
}


void addChild(struct Node* currentNode, char* name) {
	
	struct Node* temp;
	struct Node* newNode;
	
	if (findChild(currentNode, name) != NULL)	{
		printf("> This file name already taken\n");
		return;
	}


			
	newNode = (struct Node *)malloc(sizeof(struct Node));
	
	if (newNode == NULL) {
		printf("> Allocation error");
		exit(1);
	}
	
	strcpy(newNode->name, name);
	newNode->firstChild = NULL;
	newNode->sibling = NULL;
	newNode->parent = currentNode;
	
	if(currentNode->firstChild == NULL) 
		currentNode->firstChild = newNode;
	else {
		temp = currentNode->firstChild;
		while(temp->sibling != NULL) {
			temp = temp->sibling;
		}
		
		temp->sibling = newNode;
	}
}

void removeChild(struct Node* currentNode, char* name) {
	
	struct Node* temp;
	struct Node* prev;
	
	temp = currentNode->firstChild;
	
	if(temp == NULL) {
		printf("> The directory does not exist\n");
		return;
	}
	
	else if (strcmp(temp->name, name) == 0){
			
		if(temp->firstChild != NULL) {
			printf("> Cannot delete folder. The directory is not empty\n");
			return;
		}
		
		currentNode->firstChild = temp->sibling;
		free(temp);
		return;
	}	
	
	while(temp != NULL && strcmp(temp->name, name) != 0) {
		prev = temp;
		temp = temp->sibling;
	}
	
	if(temp == NULL) {
		printf("> The directory does not exist\n");
		return;
	}
	else {
		if(temp->firstChild != NULL) {
			printf("> Cannot delete folder. The directory is not empty\n");
			return;
		}
		else {
		prev->sibling = temp->sibling;
		free(temp);
	}
	}

}

void display(struct Node* currentNode) {
	
	
	struct Node* temp;

	
	temp = currentNode->firstChild;
	
	printf("> ");
	if(temp == NULL) {
		printf("\n");
		return;
	}
	
	while(temp != NULL) {
		printf("%s\n  ",temp->name);
		temp = temp->sibling;
	}
	
	printf("\n");
}


void printChildNum(struct Node* currentNode) {
	
	struct Node* temp;
	int count = 0;
		
	temp = currentNode->firstChild;
	
	printf("> ");
	if(temp == NULL) {
		printf("0\n");
		return;
	}
	
	
	while(temp != NULL) {
		count++;
		temp = temp->sibling;
	}
	
	printf("%d\n",count);
	
}

