// testing main program
#include <stdio.h>
#include "bst.h"

int main(void) {
	BStree bst;
	bst = bstree_ini(1000);
	bstree_insert(bst, key_construct("We", 1), 11);
	bstree_insert(bst, key_construct("would", 22), 2);
	bstree_insert(bst, key_construct("like", 3), 33);
	bstree_insert(bst, key_construct("students", 4), 44);
	bstree_insert(bst, key_construct("to", 5), 55);
	bstree_insert(bst, key_construct("experience", 6), 66);
	bstree_insert(bst, key_construct("arrays", 7), 77);
	bstree_insert(bst, key_construct(",", 8), 88);
	bstree_insert(bst, key_construct("strings", 99), 9);
	bstree_insert(bst, key_construct(",", 5), 50);
	bstree_insert(bst, key_construct("pointers", 1), 10);
	bstree_insert(bst, key_construct("and", 7), 10);
	bstree_insert(bst, key_construct("recursion", 4), 32);
	bstree_insert(bst, key_construct("to", 1), 10);
	bstree_insert(bst, key_construct("understand", 89), 10);
	bstree_insert(bst, key_construct("and", 123), 7);
	bstree_insert(bst, key_construct("use", 87), 10);
	bstree_insert(bst, key_construct("user", 9), 5);
	bstree_traversal(bst);
	bstree_free(bst);

	return 0;
}
