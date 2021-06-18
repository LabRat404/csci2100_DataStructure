#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


int main(int argc, char *argv[]) {

	FILE * fin, * fout;
	int i, j;
	int n;
	int r1, c1, r2, c2, x, y;
	int distance[10][10], visited[10][10]; //distance is 2d array, why you use distance[start]?
	char start[4], end[4];
	int minvalue, minpos;
	/* This may be useful in handling 8 direction of knight move */
	int dir[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	memset(start, 0, sizeof(start));
	memset(end, 0, sizeof(end));

	/* Reading input */
	fscanf(fin, "%s%s", start, end);

	/* It is a good habit to initialize the variables before use */
	memset(distance, 0, sizeof(distance));
	memset(visited, 0, sizeof(visited));

	/* This may be useful */
	r1 = start[1] - '1';
	c1 = start[0] - 'a';
	r2 = end[1] - '1';
	c2 = end[0] - 'a';
	n = 8; // you may set n = 64, you can change to n1 = 8, n2 = 8

	/* Dijkstra initialization */
	/* You may referece to lab9-q1 and lab9-q3 */
	// Your code here ...

    //init
	for(i=0; i<n;i++){
        for(j=0; j < n;j++){
            distance[i][j] = INT_MAX;
        }
	}
	distance[r1][c1] = 0;// ohh, you just copied the code?yesss umm i tried to edit abit as u can see? but then i remeber that last time one is 1 d and this time is 2d, as u just said

//to into 123456789 ? thcen ornroexw tstart is basiclly at some part of array? yes, I want to represent the 2D maze with 1D array.awww nice

//well  i 'm not sure either... xdddd
	/* modified Dijkstra */
	// Your code here

//i'm a little busy now, I try to make it work, you try to understand it oki boss  maybe u wana copy the old codes again? since i edit alot? maybe it will confuse u alot nope, dont need
for(i=0;i<64;i++){

	minvalue = INT_MAX;
	minpos =-1;

	for(j=0;j<64;j++){
        if(visited[j/8][j%8]==1) continue;
        if(minvalue > distance[j/8][j%8]){
            minvalue = distance[j/8][j%8];
            minpos = j;
        }
	}
	if(minpos==-1 || (minpos/8 == r2 && minpos%8 == c2)) break;
	visited[minpos/8][minpos%8] = 1;
	//time is up, I have no time to explain, try to understand my code, I will keep on wrting.


	for(j=0;j<8;j++)	// try four different directions.
	{
        x = minpos/8 + dir[j][0];
        y = minpos%8 + dir[j][1];
        if(x<0) continue;
        if(x>=n) continue;
        if(y<0) continue;
        if(y>=n) continue;

        if(distance[x][y] > distance[minpos/8][minpos%8]+1){
            distance[x][y] = distance[minpos/8][minpos%8]+1;
        }
    }
}


	fprintf(fout, "To get from %s to %s takes %d knight move(s).\n", start, end, distance[r2][c2]);

	fclose(fin);
	fclose(fout);

	return 0;
}

