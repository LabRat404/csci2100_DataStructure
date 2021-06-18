#include"lab5-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Initialize the tree with a root */
/* Return a new tree with initialized root as (key, value) */
Tree_CS * tree_init(int key, int value){
	// Your code here ...
	Tree_CS *T = malloc(sizeof(Tree_CS));
	T->key = key;
	T->value = value;
	T->first_child = NULL;
	T->next_sibling = NULL;
	return T;
}

/* Insert (key, value) to the tree T */
/* If key already exist in T, then update the value */
/* If key does not exist in T, */
/* then add (key, value) to the last child of node with parent_key */
void tree_insert(Tree_CS *T, int parent_key, int key, int value){
	// Your code here ...
	Tree_CS *tmp;

	if(tree_contain(T, key) == 1){
	tmp = tree_find(T, key);
	tmp->value = value;
	return;
	}

	if(tree_contain(T, parent_key) == 0){
	return;
	}

	tmp = tree_find(T, parent_key);
	if(tmp->first_child == NULL){
        tmp->first_child = malloc(sizeof(Tree_CS));
        tmp = tmp->first_child;
        tmp->key = key;
        tmp->value  = value;
        tmp->first_child = NULL;
        tmp->next_sibling = NULL;
        return;
	}
	tmp=tmp->first_child;
	while(tmp->next_sibling != NULL){
        tmp = tmp->next_sibling;
	}
	tmp->next_sibling = malloc(sizeof(Tree_CS));
	tmp = tmp->next_sibling;
	tmp->key = key;
	tmp->value = value;
	tmp->first_child = NULL;
	tmp->next_sibling = NULL;
}
Tree_CS* tree_get_previous_node(Tree_CS* T, Tree_CS* tmp){
    Tree_CS *result;

    if(T==NULL) return NULL;

    if(T->first_child == tmp) return T;
    if(T->next_sibling == tmp) return T;

    result = tree_get_previous_node(T->next_sibling, tmp);
    if(result != NULL) return result;

    return tree_get_previous_node(T->first_child, tmp);
}

/* Delete node with key from the tree T */
/* If key in T and is a leaf, then delete the node */
/* Note: if it is the first child, then the second child becomes the first child */
/* Note: it if is in the middle of the sibling, then the list structure of siblings need to be maintained */
/* If key in T and is not a leaf, then do nothing */
/* If key does not in T, then do nothing */
void tree_delete(Tree_CS *T, int key){
	// Your code here ...
	Tree_CS*tmp, *prev;
	if(T->key == key){
        if(T->first_child == NULL){
            free(T);
        }
        return;
	}
	//the node cannot be deleted
	tmp = tree_find(T, key);
	if(tmp==NULL) return;
	if(tmp->first_child != NULL) return;

	//delete the node as first child, or next sibling
	prev = tree_get_previous_node(T, tmp);
	if(prev->first_child == tmp){
        prev->first_child = tmp->next_sibling;
        free(tmp);
	}else if(prev->next_sibling == tmp){
        prev->next_sibling = tmp->next_sibling;
        free(tmp);
	}
}

/* Check if key exist in the tree T or not */
/* If key in T, return 1 */
/* If key not in T, return 0 */
int tree_contain(Tree_CS *T, int key){
	// Your code here ...

	if(tree_find(T, key)!= NULL) return 1;
	return 0;
}

/* Find the value based on the key in the tree T */
/* If key in T, return the node of key */
/* If key does not exist in T, return NULL */
Tree_CS* tree_find(Tree_CS *T, int key){
	// Your code here ...
	Tree_CS *result;
	if(T == NULL) return NULL;
	if(T->key == key) return T;

        result = tree_find(T->next_sibling, key);
        if(result != NULL) return result;

	return tree_find(T->first_child, key);
}

/* Free the tree T, if T is not NULL */
void tree_free(Tree_CS *T){
	// Your code here ...
	if(T==NULL) return;
	if(T->next_sibling!= NULL) tree_free(T->next_sibling);
	if(T->first_child != NULL) tree_free(T->first_child);
	free(T);
}

/* The print function print the tree in an output string using preorder traversal */
/* The number in the bracket is key, number after bracket is value */
/* If the tree looks like */
/* (0)17 */
/* |       \ */
/* (1)12   (2)18  */
/* |        |     \ */
/* (4)0    (3)2   (8)5 */
/* Then, the output string is "(0)17 (1)12 (4)0 (2)18 (3)2 (8)5 " */
/* You can assume the number of nodes is not more than 100 */
void tree_print_recursive(Tree_CS *T, char *output){
    if(T==NULL) return;
    sprintf(output, "%s(%d)%d \0", output, T->key, T->value);
    tree_print_recursive(T->first_child, output);
    tree_print_recursive(T->next_sibling, output);
}
	// Your code here ...
char *tree_print(Tree_CS *T){
	char* output = malloc(sizeof(char)*2500);
	memset(output, 0, sizeof(char)*2500);
	tree_print_recursive(T, output);

	return output;
}

