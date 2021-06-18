#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


typedef struct edge_t{
    int v;
    int w;
	int weight;
} Edge;

typedef struct graph_t{
    int V; /* number of vertex */
    int E; /* number of edge */
	int Emax; /* max number of edge */
    Edge *edgelist; /* array of edge */
	int *vertexvalue; /* array of value of vertex */
}EdgeList;


/* Copy your solution from lab8-q3.c to here */
EdgeList *el_graph_init(int V, int Emax){
	// your code here...
    int i;
    EdgeList *G = malloc(sizeof(EdgeList));
    G->V =V;
    G->E =0;
    G->Emax = Emax;
    G->edgelist = malloc(sizeof(Edge)*Emax);
    memset(G->edgelist,0,sizeof(Edge)*Emax);
    G->vertexvalue = malloc(sizeof(int)*V);
    memset(G->edgelist,0,sizeof(int)*V);
    return G;
}//remember to initialize every possible parameter, malloc memory space and assign it to pointer

/* Insert edge e to G */
/* If e already exsit in G, update the weight */
/* If e not in G, edge e is inserted to the last entry of the edgelist */
/* When you insert new edge ex to edgelist, make sure ex.v < ex.w */
void el_insert_edge(EdgeList *G, Edge e){
	// your code here...
    int v = e.v, w = e.w, i;
    if(v>w){
        v = e.w;
        w = e.v;
    }
    /*Edge *ptr = G->edgelist;
    for(i = 0; i< G->E; i++){
        if(ptr->v ==v||ptr->w==w)
        return;
        if(ptr->v==w ||ptr->w==v)
        return;
        ptr = ptr->next;
    }*/
    //edgelist is just an int array, do not need to use a pointer to scan it.
    for(i=0;i<G->E;i++){
        if(G->edgelist[i].v==v && G->edgelist[i].w==w){
            G->edgelist[i].weight = e.weight;
            return;
        }
    }
    //you say ummm
    if(G->E == G->Emax) return;
    G->edgelist[G->E].v = v;
    G->edgelist[G->E].w = w;
    G->edgelist[G->E].weight = e.weight;
    G->E++;
    /*ptr = create_node(e);
    ptr->next = G->edgelist;
    G->edgelist = ptr;
    G->E++;
    */
}

/* Remove edge e from G */
/* You need to check all three entries of e */
/* If e does not in G, do nothing */
/* If e exist in G, replace current slot by the last edge in the edgelist */
void el_remove_edge(EdgeList *G, Edge e){
	// your code here...
    int v=e.v, w=e.w, i;
    if(v>w){
        v = e.w;
        w = e.v;
    }
    //it's almost the same.
    for(i=0;i<G->E;i++){
        if(G->edgelist[i].v==v && G->edgelist[i].w==w && G->edgelist[i].weight==e.weight){
            G->E--;
            G->edgelist[i].v = G->edgelist[G->E].v;
            G->edgelist[i].w = G->edgelist[G->E].w;
            G->edgelist[i].weight = G->edgelist[G->E].weight;
            return;
        }//can you understand? if == then remove the edge? right, and copy the last one to this position.
        //ummmm is the one below dose the same thing ? you mean el_find_edge? nope, there're some problems in the logic
        //D: idk what i have typed back then yours on seems so simple and clean so goood
    }
    /*Edge *ptr = G->edgelist, *prev;
    for(i=0;i<G->E;i++){
        if(ptr->v==v||ptr->w==w) //this should not be '||', it must be && and you missed the equa
        break;
        if(ptr->v==w||ptr->w==v)
        break;
        prev = ptr;
        ptr = ptr->next;
    }
    if(ptr == NULL)
    return;
    G->E--;
    if(ptr == G->edgelist)
        G->edgelist = G->edgelist->next;
        else prev->next = ptr->next;
        free(ptr);
    */
}

//this

/* Search edge e in G */
/* Return the weight of e in G */
/* Note: e.weight is don't care in this function */
int el_find_edge(EdgeList *G, Edge e){
	// your code here...
int v = e.v, w=e.w, i=0;
    //Node *ptr = G->adj[v];
    if(v>w){
        v = e.w;
        w = e.v;
    }
    for(i=0;G->E;i++){
        if(G->edgelist[i].v==v && G->edgelist[i].w==w)
        return G->edgelist[i].weight;
    }
    return 0;
}

/* Set the value of vectex v */
void el_set_vertex_value(EdgeList *G, int v, int value){
	G->vertexvalue[v] = value;
}

/* Return the value of vectex v */
int el_get_vertex_value(EdgeList *G, int v){
	// your code here...


	return G->vertexvalue[v];
}

/* Free the edge list */
/* Return NULL pointer */
EdgeList *el_free(EdgeList *G){
	// your code here...

    if(G==NULL) return NULL;
    free(G->edgelist);
    free(G->vertexvalue);
    free(G);
	return NULL;
}
//done thankss try try sin

//end of copyyyy













/* write a sorting algorihtm, any sorting algorithm can do */
void el_sort_edge(EdgeList *G){
	// Your code here ...
	//selection sort
	int i, j ,minweight, pos;
    int v, w, weight;

	for(i =0; i<G->E; i++){
	pos =i;
	minweight = G->edgelist[i].weight;
        for(j=i+1;j<G->E; j++){
            if(G->edgelist[j].weight < minweight){
            pos = j;
            minweight = G->edgelist[j].weight;

            }else if(G->edgelist[j].weight == minweight && G->edgelist[j].v < G->edgelist[pos].v){
            pos = j;
            minweight = G->edgelist[j].weight;
            }else if(G->edgelist[j].weight == minweight && G->edgelist[j].v == G->edgelist[pos].v && G->edgelist[j].w == G->edgelist[pos].w){
                pos = j;
                minweight = G->edgelist[j].weight;

            }
        }
        v= G->edgelist[pos].v;
        w= G->edgelist[pos].w;
        weight = G->edgelist[pos].weight;

        G->edgelist[pos].v = G->edgelist[i].v;
        G->edgelist[pos].w = G->edgelist[i].w;
        G->edgelist[pos].weight = G->edgelist[i].weight;

        G->edgelist[i].v = v;
        G->edgelist[i].w = w;
        G->edgelist[i].weight = weight;
	}
}

typedef struct ds {
	int size;		/* size of disjoint set */
	int *parent;	/* parent of each element */
	int *tree_size; /* size of a tree in the disjoint set */
} DS;

/* Copy your lab7-q2.c to here */
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

//end of copy





int main(int argc, char *argv[]){

	FILE *fin, *fout;
	int i, j, u, v, w, n, e, cnt;
	int total_mst;
	EdgeList *G;
	DS *S;
	Edge tmpedge;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d%d", &n, &e);

	/* Initialize the graph */
	G = el_graph_init(n, e);

	/* Read edge, and add the edge to the edgelist G */
	for (i = 0; i < e; i++) {
		fscanf(fin, "%d%d%d", &u, &v, &w);
		tmpedge.v = u;
		tmpedge.w = v;
		tmpedge.weight = w;
		el_insert_edge(G, tmpedge);
	}

	/* sort the edge list */
	el_sort_edge(G);

	/* initialize the disjoint set S */
	S = ds_init(n);


	/* Kruskal's algorithm */
	total_mst = 0;
	cnt = 0;
	// Your code here ...

	for(i=0; i<e && cnt!= n-1; i++){
        if(ds_same_set(S, G->edgelist[i].v, G->edgelist[i].w)){
        fprintf(fout, "%d %d %d dropped\n", G->edgelist[i].v, G->edgelist[i].w, G->edgelist[i].weight);
        continue;

        }

	fprintf(fout, "%d %d %d selected\n", G->edgelist[i].v, G->edgelist[i].w, G->edgelist[i].weight);
	ds_union(S, G->edgelist[i].v, G->edgelist[i].w);
	total_mst += G->edgelist[i].weight;
	cnt++;
	}


	/* output */
	fprintf(fout, "The weight of the minimum spanning tree is %d.\n", total_mst);

	/* free resources */
	G = el_free(G);
	S = ds_free(S);
	fclose(fin);
	fclose(fout);

	return 0;
}

