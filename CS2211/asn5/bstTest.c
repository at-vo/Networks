#include <stdio.h>
#include <string.h>
#include "bstree.h"

int main()
{
    BStree bst;
    bst = bstree_ini();
    Data data1, data2, data3, data4, data5, data6, data7, data8;
    Key key1, key2, key3, key4, key5, key6, key7, key8;
    data1 = data_gen(10);
    key1 = key_gen("Fraser", "Brown");
    bstree_insert(bst, key1, data1);
    //bstree_traversal(bst);


    data2 = data_gen(9);
    key2 = key_gen("Jacob", "Kneeman");
    bstree_insert(bst, key2, data2);
    //bstree_traversal(bst);


    data3 = data_gen(8);
    key3 = key_gen("T", "Bills");
    bstree_insert(bst, key3, data3);
    // bstree_traversal(bst);


    data4 = data_gen(7);
    key4 = key_gen("Dijon", "Moutard");
    bstree_insert(bst, key4, data4);


    data5 = data_gen(6);
    key5 = key_gen("Dat Guy", "Kevin");
    bstree_insert(bst, key5, data5);
    // bstree_traversal(bst);

    data6 = data_gen(5);
    key6 = key_gen("something", "funny");
    bstree_insert(bst, key6, data6);
    // bstree_traversal(bst);


    data7 = data_gen(10);
    key7 = key_gen("hello", "world");
    bstree_insert(bst, key7, data7);
    // bstree_traversal(bst);

    data8 = data_gen(10);
    key8 = key_gen("hello", "world");
    bstree_insert(bst, key8, data8);
    // bstree_traversal(bst);

    data_print(bstree_search(bst, key_gen("Dijon", "Moutard")));
    
    bstree_traversal(bst);

    return 0;
}