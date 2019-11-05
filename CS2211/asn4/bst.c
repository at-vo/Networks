/**
 * Dat Vo 250983323
 **/
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/**
 * Declare Constants 
 **/
const int ROOT = 1;


/**
 * bstree_ini
 * Input: 'size': size of an array
 * Output: a pointer of type BStree
 */
BStree bstree_ini(int size) {
	BStree tree;
	tree = (BStree) malloc(sizeof(BStree_struct)); // dynamically allocate memory of type BStree_struct
	Node *nodeArr;
	nodeArr= (Node*) malloc((size +1)*sizeof(Node));// allocate memory for a Node array of size+1 for member tree_nodes
	unsigned char *charArr;
	charArr=(unsigned char *)malloc((size + 1)*sizeof(unsigned char)); // allocate memory for an unsigned char array of size+1 for member is_free
	int i;
	for (i = 0;i<size+1;i++){charArr[i] = 1;} // set all entries of is_free to 1
	tree->tree_nodes = nodeArr;
	tree->is_free = charArr;
	tree->size = size; // set member size to 'size'

	return tree;
}

/**
 * bstree_insert Function
 * Input: 'bst': a binary search tree
 * 		  'key': a key pointer
 * 		  'data': an integer
 * Effect: index of 'key' to be inserted is found
 **/
int getIndex(BStree bst, Key * key, int index){
	if (index > bst->size){return -1;}
	if (bst->is_free[index] == 1){return index;}
	else{
		Key *compare = bst->tree_nodes[index].key;
		if (key_comp(*key,*compare) == -1){return getIndex(bst,key,(2*index));}
		else if (key_comp(*key,*compare) == 1){return getIndex(bst,key,(2*index)+1);}
		else if (key_comp(*key,*compare) == 0){return 0;}
	}
}

/**
 * bstree_insert Function
 * Input: 'bst': a binary search tree
 * 		  'key': a key pointer
 * 		  'data': an integer
 * Effect: 'data' with 'key' is inserted into 'bst' 
 **/
void bstree_insert(BStree bst, Key *key, int data) {
	int index = ROOT; // array index
	index = getIndex(bst,key,index);

	if (index == -1){printf("out of bounds!\n");}
	else {
		if (index == 0){
			printf("already in tree!\n",index);

		// if 'key' is already in 'bst', do nothing
		}
		else{
			printf("inserted! index:%d \n",index);
			bst->is_free[index] = 0;
			bst->tree_nodes[index].key = key;
			bst->tree_nodes[index].data = data;
		}
		
	}
}

/**
 * printTree Helper Function
 * Input: 'bst': a binary search tree
 * 		  'index': current index of array
 * Effect: print all the nodes in bst using inorder traversal
 **/
void printTree(BStree bst, int index){
	if (index < bst->size){
		if (bst->is_free[index*2] == 0){printTree(bst,2*index);}
		print_node(bst->tree_nodes[index]);
		if (bst->is_free[(index*2)+1] == 0){printTree(bst,(2*index)+1);}
	}
}

/**
 * bstree_traversal Function
 * Input: 'bst': a binary search tree
 * Effect: print all the nodes in bst using inorder traversal
 **/
void bstree_traversal(BStree bst) {
	printTree(bst,ROOT);
}

/**
 * bstree_free Function
 * Input: 'bst': a binary search tree
 * Effect: all memory used by bst is freed 
 **/
void bstree_free(BStree bst) {
	int i;
	for (i=0;i<bst->size;i++){
		if (bst->is_free[i]==0){
			free(bst->tree_nodes[i].key->name);
			free(bst->tree_nodes[i].key); 
		}
	}
	//delNodes(bst,ROOT);
	free(bst->tree_nodes);
	free(bst->is_free);
	free(bst);
}