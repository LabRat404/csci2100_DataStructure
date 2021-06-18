
#include"lab6-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Init an empty BST */
BST* bst_init(){
	// Your code here ...
	return NULL;
}

/* Create a new node with specified values */
/* Set the children to NULL */
BST* bst_create_node(int key, int value){
	// Your code here ...

	BST *T = malloc(sizeof(BST));
	T->key = key;
	T->value = value;
	T->lchild = T->rchild = NULL;
	return T;
}

/* Search for key in the tree */
/* Return the node with the key */
/* Return NULL if the key does not exist in the tree */
BST *bst_find(BST *T, int key){
	// Your code here ...

    if(T==NULL) return NULL;
    if(T->key == key) return T;

    if(key<T->key) return bst_find(T->lchild, key);
	return bst_find(T->rchild, key);
}

/* Insert the (key,value) pair into the tree */
/* If key exist in the tree, update the value */
/* If key does not exist in the tree, create the new node and add to the tree */
/* Return the root of the tree */
BST* bst_insert(BST *T, int key, int value){
	// Your code here ...
    BST *tmp;
    if(T == NULL){

        tmp = bst_create_node(key, value);
        return tmp;
    }
    if(T->key == key){

        T->value = value;
        return T;
    }

    if(key < T->key){

        T->lchild = bst_insert(T->lchild, key, value);
        return T;
    }

    T->rchild = bst_insert(T->rchild, key, value);
	return T;
}

/* Delete the node with specified key */
/* If key does not exist in the tree, do nothing */
/* If key is leaf, delete it directly */
/* If key has one child, adjust a pointer to bypass this node and delete it */
/* If key has two children, replace the (key,value) of this node with the largest (key,value) of the left subtree, and propagate the deletion */
/* Return the root of the tree */
BST *bst_delete(BST *T, int key){
	// Your code here ...
    BST *tmp;
    //terminating condition
    if(T==NULL) return NULL;
    //recursive part

    if(key<T->key){
        T->lchild = bst_delete(T->lchild, key);
        return T;
    }else if(key >T->key){
        T->rchild = bst_delete(T->rchild, key);
        return T;
    }
    //key == T->key
    //case I: 2 children
    if(T->lchild && T->rchild){
        tmp = bst_find_max(T->lchild);
        T->key = tmp->key;
        T->value = tmp->value;
        T->lchild = bst_delete(T->lchild, tmp->key);
        return T;
        }
    if(T->lchild){
        tmp = T->lchild;
            free(T);
            return tmp;
    }

    if(T->rchild){
        tmp = T->rchild;
        free(T);
        return tmp;
    }

    free(T);
	return NULL;

}

/* Find the node storing maximum key among all nodes in the tree */
BST *bst_find_max(BST *T){
	// Your code here ...

	if(T == NULL) return NULL;
	if(T->rchild == NULL) return T;
	return bst_find_max(T->rchild);
}

/* Free the tree */
/* Return NULL pointer */
BST *bst_free(BST *T){
	// Your code here ...
    if(T == NULL) return NULL;
    if(T->lchild !=NULL) T->lchild = bst_free(T->lchild);
        if(T->rchild != NULL) T->rchild = bst_free(T->rchild);
        free(T);
	return NULL;
}

