#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

//Allocate memory of type BStree node*, set the value to NULL, and return a pointer to the
//allocated memory.
BStree bstree_ini(void)
{
    BStree tree;
    tree = (BStree)malloc(sizeof(BStree_node *));
    *tree = NULL;
    return tree;
}

BStree_node *new_node(Key key, Data data)
{
    BStree_node *node, left, right;
    node = (BStree_node *)malloc(sizeof(BStree_node));
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BStree_node *findNode(BStree bst, Key findKey)
{
    BStree_node *find = *bst;

    while (find != NULL)
    {
        Key currkey;
        currkey = find->key;
        int comp = key_comp(findKey, currkey);
        if (comp == 1 && find->right != NULL)
        {
            find = find->right;
        }
        else if (comp == -1 && find->left != NULL)
        {
            find = find->left;
        }
        else
        {
            break;
        }
    }

    return find;
}

//Insert data with key into bst. If key is in bst, then do nothing.
// You may want to use a helper function for insertion to create a pointer to a tree node from
// key and data.
void bstree_insert(BStree bst, Key key, Data data)
{
    if (*bst == NULL)
    {
        BStree_node *root = new_node(key, data);
        *bst = root;
    }
    else
    {
        Data check = bstree_search(bst, key);
        if (check != NULL)
        {
            //printf("already in tree!\n");
        }
        else
        {
            BStree_node *newNode = new_node(key, data);
            BStree_node *insertFrom = findNode(bst, key);
            int comp = key_comp(newNode->key, insertFrom->key);
            if (comp == 1)
            {
                insertFrom->right = newNode;
            }
            else
            {
                insertFrom->left = newNode;
            }
        }
    }
}

//If key is in bst, return key’s associated data. If key is not in bst, return NULL.
Data bstree_search(BStree bst, Key key)
{

    BStree_node *find = *bst;

    while (find != NULL)
    {
        int comp = key_comp(key, find->key);
        if (comp == 1)
        {
            find = find->right;
        }
        else if (comp == -1)
        {
            find = find->left;
        }
        else if (comp == 0)
        {
            break;
        }
    }
    if (find == NULL)
    {
        return NULL;
    }

    return find->data;
}

/**
 * inorder helper function 
 */
BStree_node *inorder(BStree_node *curr)
{
    if (curr == NULL)
    {
        return curr;
    }
    inorder(curr->left);
    key_print(curr->key);
    data_print(curr->data);
    inorder(curr->right);
}

//In order traversal of bst and print each node’s key and data.
void bstree_traversal(BStree bst)
{
    if (*bst != NULL)
    {
        inorder(*bst);
    }
}

BStree_node *btree_free(BStree_node *curr)
{
    if (curr == NULL)
    {
        return curr;
    }
    btree_free(curr->left);
    btree_free(curr->right);
    key_free(curr->key);
    data_free(curr->data);
    free(curr);
}

//Free all the dynamically allocated memory of bst.
void bstree_free(BStree bst)
{
    btree_free(*bst);
    free(bst);
}