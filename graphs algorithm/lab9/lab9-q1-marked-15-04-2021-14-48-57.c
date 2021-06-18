#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* This is a directed, WEIGHT and non-simple graph */
typedef struct node_s{
    int v;
	int weight; /* new item */
    struct node_s *next;
}Node;

typedef struct graph_t{
    int V; /* number of vertex */
    int E; /* number of edge */
    Node **adj; /* V linked list */
}AdjList;

typedef struct edge_t{
    int v;
    int w;
	int weight; /* new item */
} Edge;

/* copy your work from lab8-q1.c */

Node *list_insert(Node *listhead, int v, int weight){

Node *tmp = malloc(sizeof(Node));
tmp->v = v;
tmp->weight = weight;
tmp->next = listhead;
return tmp;

}

void al_insert_edge(AdjList *G, Edge e){
	// your code here...
    int v = e.v, w = e.w, weight = e.weight;
    G->adj[v] = list_insert(G->adj[v],  w, weight);
    G->E++;
}

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







/* need to update your work from unweighted graph to weighted graph */


int main(int argc, char *argv[]) {

	FILE * fin, * fout;
	AdjList * G;
	Edge tmpedge;
	int i, j;
	int n;
	int u, v, w;
	int *distance, *previous, *visited;
	int minvalue, minpos;
	Node * tmplist, *ptr;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &n);

	/* It is a good habit to initialize the variables before use */
	G = al_graph_init(n);
	distance = malloc(sizeof(int)*n);
	previous = malloc(sizeof(int)*n);
	visited = malloc(sizeof(int)*n);
	memset(distance, 0, sizeof(int)*n);
	memset(previous, 0, sizeof(int)*n);
	memset(visited, 0, sizeof(int)*n);

	/* Reading input */
	for (u = 0; u < n; u++) {
		v = 0;
		w = 0;
		while (fscanf(fin, "%d%d", &v, &w), v != -1 || w != -1) {

			tmpedge.v = u;
			tmpedge.w = v;
			tmpedge.weight = w;
            al_insert_edge(G, tmpedge);
		}
	}

	/* Dijkstra initialization */
	// Your code here ...
	for(i=0; i<n;i++){
        distance[i] = INT_MAX;
        previous[i] = -1;
	}
	distance[0] = 0;


	/* modified Dijkstra */
	// Your code here ...
	for(i=0;i<n;i++){

	minvalue = INT_MAX;
	minpos =-1;
	for(j=0;j<n;j++){
        if(distance[j]<minvalue && visited[j] == 0){
        minpos = j;
        minvalue = distance[j];
        }
	}
	if(minpos == -1){
	break;
	}

	visited[minpos] = 1;

	//output

	for(j=0;j<n-1;j++)
        fprintf(fout, "%d ", distance[j]);

	fprintf(fout, "%d\n", distance[n-1]);

// preform relaxation
	tmplist = al_neighbors(G, minpos);
	ptr = tmplist;
	while(ptr != NULL){
        if(distance[ptr->v] > distance[minpos] + ptr->weight){
        distance[ptr->v] = distance[minpos] + ptr->weight;
        previous[ptr->v] = minpos;
        }
    ptr = ptr->next;
	}
	}

	free(distance);
	free(previous);
	free(visited);
	G = al_free(G);
	fclose(fin);
	fclose(fout);

	return 0;
}

