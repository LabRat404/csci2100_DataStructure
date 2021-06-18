#include"lab7-q1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


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


