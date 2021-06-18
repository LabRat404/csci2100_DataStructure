#include"lab8-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

Node *list_insert(Node *listhead, int v){
    Node *tmp = malloc(sizeof(Node));
    tmp->v =v;
    tmp->next = listhead;
    return tmp;
}
/* Return an adjacency list with V empty linked lists */
AdjList *al_graph_init(int V){
	// your code here...
    int i;
    AdjList *G = malloc(sizeof(AdjList));
    G->V = V;
    G->E = 0;
    G->adj = malloc(sizeof(Node)*V);
    for(i=0;i<V; i++){
        G->adj[i] = NULL;
    }
	return G;
}

/* Insert edge e to G */
/* Edge e is inserted at the front of the linked list */
void al_insert_edge(AdjList *G, Edge e){
	// your code here...
    int v = e.v, w = e.w;
    G->adj[v] = list_insert(G->adj[v],  w);
    G->E++;
}
Node *list_delete(Node *listhead, int v){
    Node *ptr = listhead, *prev;
    while(ptr!=NULL){
        if(ptr->v == v){
            if(listhead == ptr){
                listhead = listhead->next;
            }else{
                prev->next = ptr->next;
            }
        free(ptr);
        return listhead;
        }
    prev = ptr;
    ptr = ptr->next;
    }
return listhead;
}

int list_contain(Node *listhead, int v){
    Node *ptr = listhead;
    while(ptr != NULL){
        if(ptr->v == v){
        return 1;
        }
    ptr = ptr->next;
    }
    return 0;
}
/* Remove edge e from G */
/* If e does not in G, do nothing */
/* If there are multiple e in G, only remove the first e */
void al_remove_edge(AdjList *G, Edge e){
	// your code here...
    int v =e.v, w = e.w;
    if(list_contain(G->adj[v], w)==1){
    G->adj[v] = list_delete(G->adj[v], w);
    G->E--;
    }
}
/* Search edge e in G */
/* Return the number of occurence of e in G */
int al_find_edge(AdjList *G, Edge e){
	// your code here...
	int v = e.v, w=e.w, count =0;
    Node *ptr = G->adj[v];
    while(ptr!=NULL){
        if(ptr->v == w){
            count++;
        }
        ptr = ptr->next;
    }
	return count;
}

/* Return the neighbors of vectex v in G */
/* The return-type is linked list */
Node *al_neighbors(AdjList *G, int v){
	// your code here...

	return G->adj[v];
}

/* Free the adjacency list */
/* Return NULL pointer */
void free_list(Node *ptr){
    if(ptr == NULL) return;
    free_list(ptr->next);
    free(ptr);
}
AdjList *al_free(AdjList *G){
	// your code here...
    int i;
    for(i=0; i< G->V; i++)
        free_list(G->adj[i]);
        free(G->adj);
        free(G);

	return NULL;
}

