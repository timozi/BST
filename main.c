#include <stdio.h>
#include <stdlib.h>


struct node{
	int key;
	int freq;
	struct node * right;
	struct node * left;
};



struct node* buildSequence();
void insertSequence(struct node **headRef,int keyVal,int freqVal);
struct node* insertTree(struct node* p,int keyVal,int freqVal);
struct node* buildTree();

int main(int argc, char *argv[]) {
    
  	struct node* head = buildSequence();
  	printf("%d",head->key);
//  	struct node* root =buildTree();
//  	printf("%d",root->key);
  	
  	
  	
  	
  
  
  
  
    return 0;
}



struct node* buildSequence(){
	FILE *fPtr=fopen("input.txt","r");
	char string[50];
	struct node *head= NULL;
	int keyVal;
	int freqVal;
	
	
	while(fgets(string,50,fPtr)!=NULL){
		keyVal = atoi(strtok(string,","));
		freqVal=atoi(strtok(NULL,","));
		insertSequence(&head,keyVal,freqVal);
		printf("%d",keyVal);
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
struct node* buildTree(){
	struct node* currentPtr = buildSequence();
	struct node* p = NULL;
	while(currentPtr!=NULL){
		p=insertTree(p,currentPtr->key,currentPtr->freq);
		currentPtr = currentPtr->right;
		
	}
	return p;
}