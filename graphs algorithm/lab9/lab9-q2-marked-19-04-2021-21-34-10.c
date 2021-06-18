#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct ds {
	int size;		/* size of disjoint set */
	int *parent;	/* parent of each element */
	int *tree_size; /* size of a tree in the disjoint set */
} DS;

/* copy your work from lab7-q2.c to here */

DS* ds_init(int size){
	// Your code here ...
	int i;
	DS*S = malloc(sizeof(DS));
	S->size = size;
	S->parent = malloc(sizeof(int)*size);
    S->tree_size = malloc(sizeof(int)*size); // you forgot to malloc a memory space for tree_.s.i..ze......okay....
	for(i =0; i<size; i++)
    {    S->parent[i] = i;
        S->tree_size[i] = 1;
    }
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
        if(ds_same_set(S, x, y)) return; //in ds_union, you have checked if x,y is in the same set, so you
        //only need to use ds_union.
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


// end of copyy




int main(int argc, char *argv[]) {

	FILE * fin, * fout;
	DS * S;
	int n, e;
	int i, u, v;
	int answer;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d%d", &n, &e);
	S = ds_init(n); //added
	for (i = 0; i < e; i++) {
		fscanf(fin, "%d%d", &u, &v);
		ds_union(S,u,v);
    }
		// Your code here ...
//1 = same set

	answer = 0;
	// Your code here ...

	for(i=0;i<n;i++){
        if(S->parent[i] == i)//parent[i] == i means i is the root of this set, the number of roots is the number of sets, done.
            answer++;
	}

	fprintf(fout, "%d\n", answer);

	S = ds_free(S); //added
	fclose(fin);
	fclose(fout);

	return 0;
}



