#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int key;
    int freq;
    struct node * right;
    struct node * left;
};

struct node *buildTree(char *string);
void preOrder(struct node *Node);
struct node* insertTree(struct node* p,int keyVal);;
void turnLeft(struct node **Node);
void turnRight(struct node **Node);

int search(struct node **Node, int value);

int main(int argc, char *argv[])
{
    if(argc != 2)
        return -1;
    struct node* root =buildTree(argv[1]);
    printf("Pre order traversal of constructed tree: ");
    preOrder(root);

    while (1)
    {
        int value;
        printf("\nEnter a value to search:");
        scanf("%d", &value);
        search(&root, value);
        printf("Pre order traversal of constructed tree: ");
        preOrder(root);
    }
}

int search(struct node **Node, int value)
{
    if(*Node == NULL)
        return 0;
    if((*Node)->key == value)
    {
        (*Node)->freq++;
        return 1;
    }
    else if((*Node)->key > value)
    {
        if(search(&(*Node)->left, value))
        {
            if((*Node)->left->freq > (*Node)->freq)
            {
                turnRight(Node);
                return 1;
            }
            else
                return 0;
        }
    }
    else if((*Node)->key < value)
    {
        if(search(&(*Node)->right, value))
        {
            if((*Node)->right->freq > (*Node)->freq)
            {
                turnLeft(Node);
                return 1;
            }
            else
                return 0;
        }
    }
}

struct node* insertTree(struct node* p,int keyVal)
{
    if(p==NULL){
        p=malloc(sizeof(struct node));
        p->key=keyVal;
        p->freq=0;
        p->right=NULL;
        p->left=NULL;
        return p;

    }
    else if(keyVal<p->key){
        p->left=insertTree(p->left,keyVal);

    }
    else if(keyVal>p->key){
        p->right=insertTree(p->right,keyVal);

    }
    return p;
}
struct node *buildTree(char *fileName)
{
    FILE *fPtr=fopen(fileName,"r");
    char string[50];
    struct node *head= NULL;
    int keyVal;
    while(fgets(string,50,fPtr)!=NULL){
        keyVal = atoi(string);
        head = insertTree(head,keyVal);
    }
    fclose(fPtr);
    return head;
}
void preOrder(struct node *Node)
{
    if(Node == NULL)
        return;
    printf("(%d,%d) ", Node->key, Node->freq);
    preOrder(Node->left);
    preOrder(Node->right);
}

void turnLeft(struct node **Node)
{
    struct node *temp = *Node;
    struct node *temp2 = (*Node)->right->left;
    *Node = (*Node)->right;
    (*Node)->left = temp;
    (*Node)->left->right = temp2;
}

void turnRight(struct node **Node)
{
    struct node *temp = *Node;
    struct node *temp2 = (*Node)->left->right;
    *Node = (*Node)->left;
    (*Node)->right = temp;
    (*Node)->right->left = temp2;
}
