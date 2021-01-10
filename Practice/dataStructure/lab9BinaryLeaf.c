#include <stdio.h>
#include <stdlib.h>

typedef struct nodes{
	int value;
	struct nodes* left;
	struct nodes* right;
} Node;

void searchGo(Node* root, 
			  char searchValue,
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
			 char searchValue){
				 
	Node* nodeFound = NULL;
	searchGo(root, searchValue, &nodeFound);
	if (nodeFound != NULL)
		return nodeFound;
	else
		return NULL;
}

void countLeafGo(Node* root, int* count){
	if (root == NULL) return;
	if (root->left == NULL && root->right == NULL){
		(*count)++;
		return;
	}
	countLeafGo(root->left, count);
	countLeafGo(root->right, count);
}

int countLeaf(Node* root){
	int count = 0;
	countLeafGo(root, &count);
	return count;
}

int main(){
	int n;
  char root_node;
	scanf("%c", &root_node);
	scanf("%d", &n);
	
	Node* root = (Node*)malloc(sizeof(Node));
	root->value=root_node;

	for(int i=0; i<n; i++){
		char parent, child, order;
		scanf("\n%c %c %c", &parent, &child, &order);

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
	
	int amountLeafLeft = countLeaf(root->left);
	int amountLeafRight = countLeaf(root->right);

	printf("%d ", amountLeafLeft);
	printf("%d ", amountLeafRight);
}