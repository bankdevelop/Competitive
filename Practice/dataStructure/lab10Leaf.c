#include <stdio.h>
#include <stdlib.h>

typedef struct nodes{
	int value;
	struct nodes* left;
	struct nodes* right;
} Node;

void addNode(Node* root, 
			  Node* newNode){
				  
	if (newNode == NULL) return;
	if (root == NULL) return;
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

void sumLeaf(Node* root,
			 int* sum){
	
	if (root == NULL) return;
	if (root->left == NULL && 
		root->right == NULL) 
		(*sum)+=root->value;
	sumLeaf(root->left, sum);
	sumLeaf(root->right, sum);
}

int main(){
	int n, value_node, sum=0;
	scanf("%d", &n);
	
	if (n > 0){
		scanf("%d", &value_node);
		Node* root = (Node*)malloc(sizeof(Node));
		root->value=value_node;

		for(int i=1; i<n; i++){
			scanf("%d", &value_node);
			Node* new_node = (Node*)malloc(sizeof(Node));
			new_node->value = value_node;
			addNode(root, new_node);
		}
		sumLeaf(root, &sum);
	}
	
	printf("%d", sum);
}