#include <stdio.h>
#include <stdlib.h>

typedef struct nodes{
	int value;
	struct nodes* left;
	struct nodes* right;
} Node;

void addNode(Node* root, 
			  Node* newNode){
				  
	if (newNode == NULL || root == NULL)
		return;
	if (root->value == newNode->value)
		return;

	Node* nextNode = NULL;
	if (newNode->value < root->value){
		nextNode = root->left;
		if (nextNode == NULL){
			root->left = newNode;
			return;
		}
	}else{
		nextNode = root->right;
		if (nextNode == NULL){
			root->right = newNode;
			return;
		}
	}
	addNode(nextNode, newNode);
}

int search(Node* root,
			 int searchValue,
			 int count){
	
	if (root == NULL) return count;
	if (root->value == searchValue) 
		return count;
	if (searchValue < root->value)
		search(root->left, 
			   searchValue, 
			   count+1);
	else
		search(root->right, 
			   searchValue, 
			   count+1);
}

void preOrder(Node* root){
	if (root == NULL) return;
	printf("%d ", root->value);
	preOrder(root->left);
	preOrder(root->right);
}

int main(){
	int value_node, search_node;
	scanf("%d", &value_node);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->value=value_node;

	while(1){
		scanf("%d", &value_node);
		if (getchar() == '\n') break;
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->value = value_node;
		addNode(root, new_node);
		if (getchar() == '\n') break;
	}
	scanf("%d", &search_node);
	int result = search(root, search_node, 1);
	printf("%d", result);
}