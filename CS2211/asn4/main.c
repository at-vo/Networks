#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"

int main() {
	char input[1000];

	BStree bst;
	bst = bstree_ini(1000);

	do {
		fgets(input, sizeof(input), stdin);
		char * name = strtok(input, " ");
		int id = atoi(strtok(NULL, " "));
		int data = atoi(strtok(NULL, " "));
		bstree_insert(bst, key_construct( name, id), data);
	} while (input[0] != '\n');

	bstree_traversal(bst);
	bstree_free(bst);
}