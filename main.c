#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Ozan Yýldýrým 150122024
//Barýþ Korkmaz 150122016

// This program constructs a binary search tree from a given input file
// Firstly, create a sorted linked list with respect to frequency values, then create the binary search tree from that linked list
// Finally return the pre order traversal of thee tree



// Node structure
struct node{
	int key;
	int freq;
	
	struct node * right; // Right child
	
	struct node * left; //Left Child
};



struct node* buildSequence(char *fileName);
void insertSequence(struct node **headRef,int keyVal,int freqVal);
struct node* insertTree(struct node* p,int keyVal,int freqVal);
struct node* buildTree(char *fileName);
void preOrder(struct node *Node);
int main(int argc, char *argv[]) {
    if(argc != 2)
        return -1;
  	struct node* root =buildTree(argv[1]);
  	printf("Pre order traversal of constructed tree: ");
    preOrder(root);
  	
  	
  	
  
  
  
  
    return 0;
}


// Get the frequency and key values from the file
struct node* buildSequence(char *fileName){
	FILE *fPtr=fopen(fileName,"r");
	char string[50];
	struct node *head= NULL;
	int keyVal;
	int freqVal;
	
	
	while(fgets(string,50,fPtr)!=NULL){
		keyVal = atoi(strtok(string,","));
		freqVal=atoi(strtok(NULL,","));
		insertSequence(&head,keyVal,freqVal);// add and create the new node
	}
	fclose(fPtr);
	return head;
}

// insert the new node to linked list
void insertSequence(struct node **headRef,int keyVal,int freqVal){
	struct node * newNodePtr = malloc(sizeof(struct node));
	newNodePtr->key = keyVal;
	newNodePtr->freq = freqVal;
	
	struct node* previousPtr =NULL;
	struct node *currentPtr = *headRef;
	while(currentPtr!=NULL&&freqVal<currentPtr->freq){ //sort the frequency values and walk to
		previousPtr=currentPtr;
		currentPtr=currentPtr->right;
	}
	// if linked list is initially empty
	if(previousPtr==NULL){
		newNodePtr->right= *headRef;
		*headRef = newNodePtr;
		
	}else{// if not empty
		newNodePtr->right=currentPtr;
		previousPtr->right = newNodePtr;
	}
	
	
}

// insert the new node to binary search tree
struct node* insertTree(struct node* p,int keyVal,int freqVal){
	if(p==NULL){
		p=malloc(sizeof(struct node));
		p->key=keyVal;
		p->freq=freqVal;
		p->right=NULL;
		p->left=NULL;
		return p;
		
		
		
	}
	else if(keyVal<p->key){
		p->left=insertTree(p->left,keyVal,freqVal);
		
	}
	else if(keyVal>p->key){
		p->right=insertTree(p->right,keyVal,freqVal);
		
	}
	return p;// return the newly added node
}


struct node* buildTree(char *fileName){
	struct node* currentPtr = buildSequence(fileName);// create the linked list
	struct node* p = NULL;
	while(currentPtr!=NULL){// while not end of the linked list
		p=insertTree(p,currentPtr->key,currentPtr->freq);
		currentPtr = currentPtr->right;
		
	}
	return p;// return the root of the tree
}
void preOrder(struct node *Node)// pre order travelsal of the binary search tree
{
    if(Node == NULL)//if empty
        return;
    printf("%d ", Node->key);
    preOrder(Node->left);
    preOrder(Node->right);
}
