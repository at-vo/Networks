/**
 * Dat Vo 250983323
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

/**
 * key_construct Function
 * Input: 'in_name': a string ends with '\0'
 *   	  'in_id': an integer
 * Output: a pointer of type pointer to Key, pointing to an allocated memory containing a Key 
 **/
Key *key_construct(char *in_name, int in_id) {
	Key* key;
	key = (Key*) malloc(sizeof(Key)); // dynamically allocate memory to hold a Key
	key->name = strdup(in_name); // dynamically allocate memory for the Key's name
	key->id = in_id; // set Key's id to be in_id
	
	return key;
}

/**
 * key_comp Function
 * Input: 'key1' and 'key2' are two Keys
 * Output: -1 if key1<key2, 0 if key1=key2, 1 if key1>key2 
 **/
int key_comp(Key key1, Key key2) {
	int comp = strcmp(key1.name, key2.name);
	if (comp < 0){return -1;}  //if return value < 0, then key1 < key2
	else if (comp == 0) { // if key1.name = key2.name, then compare key1.id with key2.id
		if (key1.id < key2.id){return -1;} 
		else if (key1.id == key2.id){return 0;} // if return value = 0, then key1 = key2,
		return 1;
	}
	else if (comp > 0){return 1;} // if return value > 0, then key1 > key2,
}

/**
 * print_key Function
 * Input: 'key': a pointer to Key
 * Effect: ( key->name key->id ) is printed 
 **/
void print_key(Key *key) {	
	printf("(%15s %10d) ",key->name,key->id);
}

/**
 * print_node Function
 * Input: 'node': a node
 * Effect: node.key is printed and then the node.data is printed 
 **/
void print_node(Node node) {
	print_key(node.key);
	printf("%10d\n",node.data);
}

