#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct graph_t{
    int V; /* number of vertex */
    int E; /* number of edge */
    int **adj; /* V x V adjacency matrix */
}AdjMatrix;

typedef struct edge_t{
    int v;
    int w;
    int weight;
} Edge;

/* Copy your work from lab8-q2.c to here */
int **matrix_init(int r, int c, int val){
int i, j;
int **t = malloc(r *sizeof(int *));
for(i=0; i<r; i++)
    t[i] = malloc(c *sizeof(int));
for(i=0; i<r; i++)
    for(j=0; j<c; j++)
        t[i][j] = val;
    return t;
}
AdjMatrix *am_graph_init(int V){
	// your code here...
    AdjMatrix *G = malloc(sizeof(AdjMatrix));
    G->V = V;
    G->E =0;
    G ->adj = matrix_init(V,V,0);

	return G;
}

/* Insert edge e to G */
/* Update the adjacency matrix according to the value of e */
void am_insert_edge(AdjMatrix *G, Edge e){
	// your code here...
    int v = e.v, w=e.w;
    if(G->adj[v][w] == 0)
        G->E++;
    G->adj[v][w] = e.weight;

}

/* Remove edge e from G */
/* Set the entry to 0 */
/* You also need to check e.weight */
void am_remove_edge(AdjMatrix *G, Edge e){
	// your code here...
    int v =e.v, w=e.w;
    if(G->adj[v][w] !=0 && G->adj[v][w] ==e.weight){
    G->E--;
    G->adj[v][w] = 0;
    //G->adj[w][v] = 0;
    }
}

/* Search edge e in G */
/* Return the weight of e in G */
/* Note: e.weight means nothing in this find function */
int am_find_edge(AdjMatrix *G, Edge e){
	// your code here...
int v = e.v, w=e.w, count =0;
    //Node *ptr = G->adj[v];

    return G->adj[v][w]; //it's enough
    //wait wut?! just like this ?! right, if you dont believe, try to submiit
    //ummm i trust u ofcoz xd

} //but i dont have Node defined? q2 is quite different from q1, you only need a matrix to store the edges, why you need nodes?
//if you want to identify if an edge is in a graph, just check if adj[v][w] != 0, sorry my mistake
//so i just copy codes from Q1, which is list no need done


/* Return the neighbors of vectex v in G */
/* The return-type is an integer array */
/* index = 0 means the number of neighbors of v */
/* Suppose n neighbors are found, index = 1..n corresponds to the n neighbors */
/* The neighbors are stored in the increasing numeric order */
/* Note: weight means nothing in this neighbors function */
int *am_neighbors(AdjMatrix *G, int v){
	// your code here...I will give you a pseudo code

    //2.create a new array and
    //let the first number of this array to be count.
    //3.for 1 to count, let array[i] = neighbors

    int count, *result, i, pos;
    count = 0;
    for(i=0;i<G->V;i++) if (G->adj[v][i]!=0) count++; //1.check the number of neighbors of v as count

    result = malloc(sizeof(int)*(count+1));
    //your turn
    result[0] = count;
    pos = 1;
    for(int i = 0;i<G->V;i++) // not right
    {
        if(G->adj[v][i]!=0){
            result[pos++] = i;
            //cannot use pos ++ inside ?! you can, but I want to say that this style is equivalent to the previous one i prefer the previoss xdd
            }
    }

	return result; // return an array ? correct, what's the array like? you need to create a new array.
}
// how about neibour @@
//read the instructions, tell me what should this function return?

/* Free the adjacency matrix */
/* Return NULL pointer */
AdjMatrix *am_free(AdjMatrix *G){
	// your code here...
	// your code here...
    int i;

	return NULL;
}






//end of copyyyyy
int main(int argc, char *argv[]){

	FILE *fin, *fout;
	int i, j, k, n;
	AdjMatrix *G;
	int contain_cycle;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	/* Reading input */
	fscanf(fin, "%d", &n);

	/* Initalizing adj matrix G */
	G = am_graph_init(n);
    int dist[i][j];
	/* Reading input */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fin, "%d", &G->adj[i][j]);

            //dist[i][j] = G->adj[i][j]; //added this ?
		}
	}

	/* Flody Warshall's algorithm */
	// Your code here ...

    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){ //3K party???? aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
            if(G->adj[i][k] == INT_MAX) continue;
            if(G->adj[k][j] == INT_MAX) continue;
            if(G->adj[i][k]+G->adj[k][j]<G->adj[i][j])
                G->adj[i][j] = G->adj[i][k] + G->adj[k][j] ;


            }
        }
    }
	/* Output distance matrix */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n-1; j++) {
			fprintf(fout, "%d ", G->adj[i][j]);
		}
		fprintf(fout, "%d\n", G->adj[i][n-1]);
	}

	/* Run Flody Warshll's algorithm once more to detect negative cycles */
	contain_cycle = 0;
	// Your code here ...
for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
            if(G->adj[i][k] == INT_MAX) continue;
            if(G->adj[k][j] == INT_MAX) continue;
            if(G->adj[i][k]+G->adj[k][j]<G->adj[i][j]){
                contain_cycle = 1;
                break;
            }
            }
        }
    }

//    go wc n bath if u c thisss

	/* Output */
	if (contain_cycle) {
		fprintf(fout, "The graph contains negative cycles.");
	} else {
		fprintf(fout, "The graph does not contain negative cycles.");
	}

	/* Free resources */
	G = am_free(G);
	fclose(fin);
	fclose(fout);

	return 0;
}

