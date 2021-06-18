#include"lab7-q2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


/* Init a disjoint set with a given size */
/* All node should point to itself */
DS* ds_init(int size){
	// Your code here ...
	int i;
	DS*S = malloc(sizeof(DS));
	S->size = size;
	S->parent = malloc(sizeof(int)*size);
	for(i =0; i<size; i++)
        S->parent[i] = i;
    S->tree_size = 1;

        return S;
}

/* Find the root of node x */
/* Path compression is needed */
/* Return the root of node x */
int ds_find_set(DS *S, int x){
	// Your code here ...
    if(x==S->parent[x]) return x;
        return S->parent[x] = ds_find_set(S, S->parent[x]);
}

/* Check if x and y belong to the same set */
/* Return 1 if they are belong to the same set */
/* Return 0 if they are not belong to the same set */
int ds_same_set(DS* S, int x, int y){
	// Your code here ...
int rootx, rooty;
rootx = ds_find_set(S, x);
rooty = ds_find_set(S, y);
return rootx == rooty;
	return 0;
}

/* Union the set containing x and the set containing y */
/* Put the set containing y as the subtree of the set of containing x */
/* You need to update tree_size */
void ds_union(DS *S, int x, int y){
	// Your code here ...

        int root;
        if(ds_same_set(S, x, y)) return;
        root = ds_find_set(S, y);
        S->parent[root] = x;



}

/* Union the set containing x and the set containing y */
/* Put the smaller set as the subtree of the larger set */
/* If both sets have the same set, put set containing x as the subtree of set containing y */
/* Remember to update tree_size */
void ds_union_by_size(DS *S, int x, int y){
	// Your code here ...
    int rootx, rooty;
    if(ds_same_set(S, x, y)) return;
    rootx = ds_find_set(S, x);
    rooty = ds_find_set(S, y);
    if(S->tree_size[rootx]<S->tree_size[rooty]){
        S->parent[rootx] = rooty;
        S->tree_size[rooty] += S->tree_size[rootx];
    }else{
        S->parent[rooty] = rootx;
        S->tree_size[rootx] += S->tree_size[rooty];
    }

}

/* Free the disjoint set */
/* Return NULL pointer */
DS *ds_free(DS *S){
	// Your code here ...

	return NULL;
}



