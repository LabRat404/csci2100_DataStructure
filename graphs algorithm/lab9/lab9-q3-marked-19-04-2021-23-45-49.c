#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* You can reuse some of the code in lab9-q1.c */

int main(int argc, char *argv[]) {

	FILE * fin, * fout;
	int i, j, k;
	int T[2];
	int minvalue, minpos;
	int start;
	int princess;
	int n, row, col;
	int u, v, w;
	int *distance, *visited;
	int answer;
	char maze[101][101];

	/* this may be useful to some of you */
	int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d%d", &row, &col);
	n = row*col; //n means what? the total size of maze right

	/* It is a good habit to initialize the variables before use */
	memset(maze, 0, sizeof(maze));
	answer = 0;

	distance = malloc(sizeof(int)*n); // distance will store the distance from the starting point to every position,get !
	visited = malloc(sizeof(int)*n);// visited stores if I hav eoki gooooooooooooooooooooooood.
	memset(distance,0,sizeof(int)*n);
	memset(visited,0,sizeof(int)*n);
	//here put map gen ???
	// no need gen, just red the input


	/* Reading input */
	for (i = 0; i < row; i++) {
		fscanf(fin, "%s", maze[i]);
		printf("%s\n", maze[i]);
	}


	w = 0; // w indicate the temp location.
	for (u=0;u<row;u++){
        for(v = 0; v<col; v++)
        {
            if(maze[u][v] == 'T')
            {
                T[w++] = u*col+v;
            }
            if(maze[u][v] == 'S')
                start = u*col + v;
            if(maze[u][v] == 'P')
                princess = u*col +v;
        }
	} // can you understand this part?
	//thonking
	//yes i understand this part, scaning the maze and mapping ? right

	/* Dijkstra initialization */
	// Your code here
	//int portal = 0;

	for(i=0; i<n;i++){
        distance[i] = INT_MAX;
	}
	distance[start] = 0;//distance[i] means the min distance between i and the start point, of course the distance between start and start is 0. and we need to find distance[princess], right? yes yup yup
	//btw, nooooooooooooooooooooooooooot the distance, but the minimum distance, ah yes////// let's move on.
// 456
// 789

//to into 123456789 ? thcen ornroexw tstart is basiclly at some part of array? yes, I want to represent the 2D maze with 1D array.awww nice

//well  i 'm not sure either... xdddd
	/* modified Dijkstra */
	// Your code here

for(i=0;i<n;i++){

	minvalue = INT_MAX;
	minpos =-1;

	for(j=0;j<n;j++){
        if(visited[j]==1) continue;
        if(minvalue > distance[j]){
            minvalue = distance[j];
            minpos = j;
        }
	}
	if(minpos==-1 || minpos == princess) break;
	visited[minpos] = 1;
	//time is up, I have no time to explain, try to understand my code, I will keep on wrting.

	u = minpos/col;
	v = minpos%col;

	for(j=0;j<4;j++)	// try four different directions.
	{
        if(u+dir[j][0]<0) continue;
        if(u+dir[j][0]>=row) continue;
        if(v+dir[j][1]<0) continue;
        if(v+dir[j][1]>=col) continue;
        if(maze[u+dir[j][0]][v+dir[j][1]] =='X') continue;
        w = (dir[j][0]+u)*col+(v+dir[j][1]);

        if(maze[u+dir[j][0]][v+dir[j][1]]=='.'){
            if(distance[w]>distance[minpos]+1){
                distance[w] = distance[minpos]+1;
            }
        }else if(maze[u+dir[j][0]][v+dir[j][1]]=='S'){
            if(distance[w]>distance[minpos]+1){
                distance[w] = distance[minpos]+1;
            }
        }else if(maze[u+dir[j][0]][v+dir[j][1]]=='P'){
            if(distance[w]>distance[minpos]+1){
                distance[w] = distance[minpos]+1;
            }
        }else if(maze[u+dir[j][0]][v+dir[j][1]]=='D'){
            if(distance[w]>distance[minpos]+2){
                distance[w] = distance[minpos]+2;
            }
        }else if(maze[u+dir[j][0]][v+dir[j][1]]=='T'){
            if(w==T[0]){
                if(distance[T[1]]>distance[minpos]+10){
                    distance[T[1]] = distance[minpos]+10;
                }
            }
            else if(w==T[1]){
                if(distance[T[0]]>distance[minpos]+10){
                    distance[T[0]] = distance[minpos]+10;
                }
            }
        }
	}

}


	/* output, free feel to edit the condition */
	if (minpos == princess) {
		fprintf(fout, "I save Princess in %d seconds!\n", distance[princess]);  //:D
	} else {
		fprintf(fout, "I cannot save Princess.\n"); // D:
	}

    free(distance);
    free(visited);
	fclose(fin);
	fclose(fout);

	return 0;
}

