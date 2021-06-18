#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node {
	double key;	/* key of a node */
	char value[100];/* value of a node */
} Node;

typedef struct heap{
	int maxsize;	/* maximum size of the heap */
	int count; 	/* number of nodes stored in the heap */
	Node *data;	/* storage of the heap */
}MaxHeap;

/* copy your correct implementation of MaxHeap from Q1 to below */
/* Note: key is changed to 'double' */

/* Init an empty heap with a given size */
MaxHeap* maxheap_init(int maxsize) {
	// Your code here ...

	MaxHeap *H = malloc(sizeof(MaxHeap));
	H->maxsize = maxsize;
	H->count = 0;
	H->data = malloc(sizeof(Node)*(maxsize+1));
	memset(H->data, 0, sizeof(Node)*(maxsize+1));
	return H;
}

/* Heaplify a max-heap based on the input array S with size S_size */
/* The root of heap is stored at H->node[1] */
/* Return the max-heap based on the input S */
MaxHeap *maxheap_heaplify(Node* S, int S_size) {
	// Your code here ...

	MaxHeap *H = maxheap_init(S_size);
	int i, index, swap, other;
	Node tmp;

	for(i=0;i<S_size; i++){

        H->data[i+1].key = S[i].key;
        sprintf(H->data[i+1].value, "%s\0", S[i].value);
	}
	H->count = S_size;

	for(i = (S_size>>1); i>0; i--){
        index = i;
        tmp.key = H->data[i].key;
        sprintf(tmp.value, "%s\0", H->data[i].value);

            for(index = i; 1; index = swap){
                swap = (index<<1); //left child
                other = (swap|1); //right child

                if(other <= S_size && H->data[other].key > H->data[swap].key) swap = other;
                if(swap > S_size) break;
                if(tmp.key > H->data[swap].key) break;

                H->data[index].key = H->data[swap].key;
                sprintf(H->data[index].value, "%s\0", H->data[swap].value);
        }
        H->data[index].key = tmp.key;
        sprintf(H->data[index].value, "%s\0", tmp.value);

	}




        return H;
}

/* Insert the (key,value) pair into the max-heap H */
/* If key exist in the heap, update the value */
/* If key does not exist in the heap and heap is not full, */
/* perform the insertion of a max-heap */
/* If key does not exist in the heap but heap is full, do nothing */
/* Return 1 if insertion is successful */
/* Return 2 if update of value is successful */
/* Return 0 if heap is full and insertion cannot be proceeded */
int maxheap_insert(MaxHeap *H, int key, char* value) {
	// Your code here ...

	int i, index, parent;

	for(i = 1; i<= H->count; i++){
        if(H->data[i].key == key){
            sprintf(H->data[i].value, "%s\0", value);
            return 2;
        }
	}
	//heap is full
	if(H->count == H->maxsize) return 0;

	H->count++;
	for(index = H->count; index >1 ; index=parent){
        parent = (index >> 1);

        if(H->data[parent].key > key) break;
        H->data[index].key = H->data[parent].key;
        sprintf(H->data[index].value, "%s\0", H->data[parent].value);

	}

	H->data[index].key = key;
	sprintf(H->data[index].value, "%s\0", value);
	return 1;
}

/* Delete root of the max-heap */
/* Update the heap accordingly */
/* Return the (key,value) of the deleted root */
/* Return NULL if the heap is empty */
Node *maxheap_delete(MaxHeap *H) {
	// Your code here ...
        int index, swap, other;
        Node tmp, *result;

        if(H->count ==0) return NULL;
        result = malloc(sizeof(Node));
        result->key = H->data[1].key;
        sprintf(result->value, "%s\0", H->data[1].value);

        tmp.key = H->data[H->count].key;
        sprintf(tmp.value, "%s\0", H->data[H->count].value);
        H->count --;




	for(index =1; 1; index = swap){
	swap = (index<<1);
	other = (swap |1);
	if(other <=H->count && H->data[other].key > H->data[swap].key)
	swap = other;
	if(swap>H->count) break;
	if(tmp.key > H->data[swap].key) break;


    H->data[index].key = H->data[swap].key;
    sprintf(H->data[index].value, "%s\0", H->data[swap].value);


	}
	H->data[index].key = tmp.key;
	sprintf(H->data[index].value, "%s\0", tmp.value);
	return result;

}


/* Free the max-heap */
/* Return NULL pointer */
MaxHeap *maxheap_free(MaxHeap *H) {
	// Your code here ...

	if(H == NULL) return NULL;
	free(H->data);
	free(H);

	return NULL;
}

/* copy your correct implementation of MaxHeap from Q1 to above */

int main(int argc, char *argv[]){

	FILE *fin, *fout;
	int n, i;
	MaxHeap *H;
	Node *S;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &n);
	S = malloc(sizeof(Node)*n);

	/* key is changed to floating point number */
	for (i = 0; i < n; i++) {
		fscanf(fin, "%s", S[i].value);
		S[i].key = atof(S[i].value);
	}


	H = maxheap_heaplify(S, n);



	/* output your heapified MaxHeap */
	for (i = 1; i < n; i++) {
		fprintf(fout, "%s ", H->data[i].value);
	}
	fprintf(fout, "%s\n", H->data[n].value);

        /* think about how to generate the remaining output */
	// Your code below ...
 //inserted parts
       while(H->count>1){

        maxheap_delete(H);
        for(i=1; i<H->count; i++){
        fprintf(fout, "%s ", H->data[i].value);
        }
        fprintf(fout, "%s\n", H->data[H->count].value);
        }
    //end of inserted parts



	free(S);
	maxheap_free(H);

	fclose(fin);
	fclose(fout);

	return 0;
}

