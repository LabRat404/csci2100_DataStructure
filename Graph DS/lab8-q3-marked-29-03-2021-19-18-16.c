#include"lab8-q3.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* Return an empty edge list with at most V vectice and Emax edges */
/* All entries in G->edgelist and G->vertexvalue are init as 0 */




EdgeList *el_graph_init(int V, int Emax){
	// your code here...
    int i;
    EdgeList *G = malloc(sizeof(EdgeList));
    G->V =V;
    G->E =0;
    G->edgelist = NULL;
    return G;
}

/* Insert edge e to G */
/* If e already exsit in G, update the weight */
/* If e not in G, edge e is inserted to the last entry of the edgelist */
/* When you insert new edge ex to edgelist, make sure ex.v < ex.w */
void el_insert_edge(EdgeList *G, Edge e){
	// your code here...
    int v = e.v, w = e.w, i;
    Edge *ptr = G->edgelist;
    for(i = 0; i< G->E; i++){
        if(ptr->v ==v||ptr->w==w)
        return;
        if(ptr->v==w ||ptr->w==v)
        return;
        ptr = ptr->next;
    }
    ptr = create_node(e);
    ptr->next = G->edgelist;
    G->edgelist = ptr;
    G->E++;

}

/* Remove edge e from G */
/* You need to check all three entries of e */
/* If e does not in G, do nothing */
/* If e exist in G, replace current slot by the last edge in the edgelist */
void el_remove_edge(EdgeList *G, Edge e){
	// your code here...
    int v=e.v, w=e.w, i;
    Edge *ptr = G->edgelist, *prev;
    for(i=0;i<G->E;i++){
        if(ptr->v==v||ptr->w==w)
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
}

/* Search edge e in G */
/* Return the weight of e in G */
/* Note: e.weight is don't care in this function */
int el_find_edge(EdgeList *G, Edge e){
	// your code here...
int v = e.v, w=e.w, count =0;
    //Node *ptr = G->adj[v];

    return G->adj[v][w]; //it's enough

}

/* Set the value of vectex v */
void el_set_vertex_value(EdgeList *G, int v, int value){
	G->vertexvalue[v] = value;
}

/* Return the value of vectex v */
int el_get_vertex_value(EdgeList *G, int v){
	// your code here...


	return 0;
}

/* Free the edge list */
/* Return NULL pointer */
EdgeList *el_free(EdgeList *G){
	// your code here...


	return NULL;
}

