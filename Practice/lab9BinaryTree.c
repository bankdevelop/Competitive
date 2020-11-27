#include <stdio.h>
#include <stdlib.h>

typedef struct nodes{
	int value;
	struct nodes* left;
	struct nodes* right;
} Node;

void searchGo(Node* root, 
			  int searchValue,
			  Node** nodeFound){
				  
	if (*nodeFound != NULL) return;
	if (root == NULL) return;

	if (root->value == searchValue)
		*nodeFound = root;

	if (root->left != NULL)
		searchGo(root->left, searchValue, nodeFound);
	if (root->right != NULL)
		searchGo(root->right, searchValue, nodeFound);
}

Node* search(Node* root,
			 int searchValue){
				 
	Node* nodeFound = NULL;
	searchGo(root, searchValue, &nodeFound);
	if (nodeFound != NULL)
		return nodeFound;
	else
		return NULL;
}

void preOrder(Node* root){
	if (root == NULL) return;
	printf("%d ", root->value);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(Node* root){
	if (root == NULL) return;
	inOrder(root->left);
	printf("%d ", root->value);
	inOrder(root->right);
}

void postOrder(Node* root){
	if (root == NULL) return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->value);
}

int main(){
	int n;
	int root_node;
	scanf("%d", &n);
	scanf("%d", &root_node);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->value=root_node;

	for(int i=0; i<n; i++){
		int parent, child;
		char order;
		scanf("%d %d %c", &parent, &child, &order);

		Node* result = search(root, parent);
		if (result != NULL){
			Node* newChild = (Node*)malloc(sizeof(Node));
			newChild->value = child;
			if (order == 'R')
				result->right = newChild;
			else if (order == 'L')
				result->left = newChild;
		}
	}
	
	//pre order
	preOrder(root);
	printf("\n");
	//in order
	inOrder(root);
	printf("\n");
	//post order
	postOrder(root);
}