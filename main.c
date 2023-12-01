#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int key;
	int freq;
	struct node * right;
	struct node * left;
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



struct node* buildSequence(char *fileName){
	FILE *fPtr=fopen(fileName,"r");
	char string[50];
	struct node *head= NULL;
	int keyVal;
	int freqVal;
	
	
	while(fgets(string,50,fPtr)!=NULL){
		keyVal = atoi(strtok(string,","));
		freqVal=atoi(strtok(NULL,","));
		insertSequence(&head,keyVal,freqVal);
	}
	fclose(fPtr);
	return head;
}
void insertSequence(struct node **headRef,int keyVal,int freqVal){
	struct node * newNodePtr = malloc(sizeof(struct node));
	newNodePtr->key = keyVal;
	newNodePtr->freq = freqVal;
	
	struct node* previousPtr =NULL;
	struct node *currentPtr = *headRef;
	while(currentPtr!=NULL&&freqVal<currentPtr->freq){
		previousPtr=currentPtr;
		currentPtr=currentPtr->right;
	}
	if(previousPtr==NULL){
		newNodePtr->right= *headRef;
		*headRef = newNodePtr;
		
	}else{
		newNodePtr->right=currentPtr;
		previousPtr->right = newNodePtr;
	}
	
	
}
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
	return p;
}
struct node* buildTree(char *fileName){
	struct node* currentPtr = buildSequence(fileName);
	struct node* p = NULL;
	while(currentPtr!=NULL){
		p=insertTree(p,currentPtr->key,currentPtr->freq);
		currentPtr = currentPtr->right;
		
	}
	return p;
}
void preOrder(struct node *Node)
{
    if(Node == NULL)
        return;
    printf("%d ", Node->key);
    preOrder(Node->left);
    preOrder(Node->right);
}