#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct node{
	int value[2];
	struct node *parent;
	int depth;
} node;

typedef struct Snake {
    int array[900][2];
} Snake;

typedef struct Paths {
	int lengths[4];
    int array[4][900][2];
} Paths;

int simulate(int *);
double euclidian(int[], int[]);
int search(int[2], int[2], Snake *, int, Paths *, int);
void get_neighbors(int[], Snake *, int[4][2], int, int);
void f();
bool contains(node, node[], int length);

int main(){
	// srand(time(NULL));
	// srand((unsigned) time(NULL));
	// clock_t t;
	// t = clock();
	// int *dataset = (int *)malloc(sizeof(int) * (900 * 450 * 2));
	// for(int i = 0; i < 900; i++){
	// 	int **a = (int **)malloc(sizeof(int *) * i);
	// 	for(int x = 0; x < i; x++){
	// 		int *b = (int *)malloc(sizeof(int) * 2);
	// 		a[x] = b;
	// 	}
	// 	dataset[i] = a;
	// }
	f();
	
	// for(int i = 0; i < 1; i++){
	// 	int length = simulate(dataset);
	// 	// printf("\n");
	// 	// printf("%d", length);
	// }
	// printf("\n");
	// for(int x = 0; x < length; x++){
	// 	for(int y = 0; y < x; y++){
	// 		printf("(");
	// 		for(int z = 0; z < 2; z++){
	// 			printf("%d", dataset[x][y][z]);
	// 			printf(", ");
	// 		}
	// 		printf("), ");
	// 	}
	// 	printf("\n");
	// }
	
	// t = clock() - t;
	// double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
	// printf("\n");
	// printf("%f", time_taken);

	return 0;
}

void f(){
	Snake snake;
	Paths paths;
	for(int r = 0; r < 900; r++){
		for(int c = 0; c < 2; c++){
			snake.array[r][c] = 0;
			paths.array[0][r][c] = 0;
		}
	}
	// snake.array[0][0] = 7;
	// snake.array[0][1] = 20;
	// snake.array[1][0] = 8;
	// snake.array[1][1] = 20;
	// snake.array[2][0] = 9;
	// snake.array[2][1] = 20;
	// snake.array[3][0] = 10;
	// snake.array[3][1] = 20;
	// snake.array[4][0] = 11;
	// snake.array[4][1] = 20;
	// snake.array[5][0] = 12;
	// snake.array[5][1] = 20;
	// snake.array[6][0] = 13;
	// snake.array[6][1] = 20;
	// snake.array[7][0] = 14;
	// snake.array[7][1] = 20;
	// snake.array[8][0] = 15;
	// snake.array[8][1] = 20;
	// snake.array[9][0] = 15;
	// snake.array[9][1] = 19;
	// snake.array[10][0] = 15;
	// snake.array[10][1] = 18;
	// snake.array[11][0] = 15;
	// snake.array[11][1] = 17;
	// snake.array[12][0] = 15;
	// snake.array[12][1] = 16;
	// snake.array[13][0] = 15;
	// snake.array[13][1] = 15;
	// snake.array[14][0] = 15;
	// snake.array[14][1] = 14;
	// snake.array[15][0] = 14;
	// snake.array[15][1] = 14;
	// snake.array[16][0] = 14;
	// snake.array[16][1] = 13;
	// snake.array[17][0] = 14;
	// snake.array[17][1] = 12;
	// snake.array[18][0] = 14;
	// snake.array[18][1] = 11;
	// snake.array[19][0] = 14;
	// snake.array[19][1] = 10;
	// snake.array[20][0] = 14;
	// snake.array[20][1] = 9;
	// snake.array[21][0] = 14;
	// snake.array[21][1] = 8;
	// snake.array[22][0] = 14;
	// snake.array[22][1] = 7;
	// snake.array[23][0] = 13;
	// snake.array[23][1] = 7;
	// snake.array[24][0] = 12;
	// snake.array[24][1] = 7;
	// snake.array[25][0] = 11;
	// snake.array[25][1] = 7;
	// snake.array[26][0] = 11;
	// snake.array[26][1] = 6;
	// snake.array[27][0] = 10;
	// snake.array[27][1] = 6;
	// snake.array[28][0] = 10;
	// snake.array[28][1] = 7;
	// snake.array[29][0] = 9;
	// snake.array[29][1] = 7;
	// snake.array[30][0] = 9;
	// snake.array[30][1] = 6;
	// snake.array[31][0] = 8;
	// snake.array[31][1] = 6;
	// snake.array[32][0] = 8;
	// snake.array[32][1] = 7;
	// snake.array[33][0] = 7;
	// snake.array[33][1] = 7;
	// snake.array[34][0] = 7;
	// snake.array[34][1] = 6;
	// snake.array[35][0] = 6;
	// snake.array[35][1] = 6;
	// snake.array[36][0] = 6;
	// snake.array[36][1] = 5;
	// snake.array[37][0] = 5;
	// snake.array[37][1] = 5;
	// snake.array[38][0] = 5;
	// snake.array[38][1] = 4;
	// snake.array[39][0] = 4;
	// snake.array[39][1] = 4;
	// snake.array[40][0] = 4;
	// snake.array[40][1] = 3;
	// snake.array[41][0] = 3;
	// snake.array[41][1] = 3;
	// snake.array[42][0] = 2;
	// snake.array[42][1] = 3;
	// snake.array[43][0] = 2;
	// snake.array[43][1] = 4;
	// snake.array[44][0] = 3;
	// snake.array[44][1] = 4;
	// snake.array[45][0] = 3;
	// snake.array[45][1] = 5;
	// snake.array[46][0] = 4;
	// snake.array[46][1] = 5;
	// snake.array[47][0] = 4;
	// snake.array[47][1] = 6;
	// snake.array[48][0] = 5;
	// snake.array[48][1] = 6;
	// snake.array[49][0] = 5;
	// snake.array[49][1] = 7;
	// snake.array[50][0] = 6;
	// snake.array[50][1] = 7;
	// snake.array[51][0] = 6;
	// snake.array[51][1] = 8;
	// snake.array[52][0] = 7;
	// snake.array[52][1] = 8;
	// snake.array[53][0] = 8;
	// snake.array[53][1] = 8;
	// snake.array[54][0] = 9;
	// snake.array[54][1] = 8;
	// snake.array[55][0] = 10;
	// snake.array[55][1] = 8;
	// snake.array[56][0] = 11;
	// snake.array[56][1] = 8;
	// snake.array[57][0] = 12;
	// snake.array[57][1] = 8;
	// snake.array[58][0] = 13;
	// snake.array[58][1] = 8;
	// snake.array[59][0] = 13;
	// snake.array[59][1] = 9;
	// snake.array[60][0] = 13;
	// snake.array[60][1] = 10;
	// snake.array[61][0] = 13;
	// snake.array[61][1] = 11;
	// snake.array[62][0] = 13;
	// snake.array[62][1] = 12;
	// snake.array[63][0] = 13;
	// snake.array[63][1] = 13;
	// snake.array[64][0] = 13;
	// snake.array[64][1] = 14;
	// snake.array[65][0] = 13;
	// snake.array[65][1] = 15;
	// snake.array[66][0] = 14;
	// snake.array[66][1] = 15;
	// snake.array[67][0] = 14;
	// snake.array[67][1] = 16;
	// snake.array[68][0] = 14;
	// snake.array[68][1] = 17;
	// snake.array[69][0] = 14;
	// snake.array[69][1] = 18;
	int apple[] = {2, 1};
	search(snake.array[0], apple, &snake, 0, &paths, 4);
}

int simulate(int *dataset){
	Snake snake;
	Paths paths;
	for(int r = 0; r < 900; r++){
		for(int c = 0; c < 2; c++){
			snake.array[r][c] = 0;
			paths.array[0][r][c] = 0;
		}
	}
	snake.array[0][0] = 0;
	snake.array[0][1] = 0;
	int apple[2] = {0, 0};
	int moves = 0;
	int length = 1;
	for(int epoch = 0; epoch < 900; epoch++){
		printf("[");
		for(int i = 0; i < length; i++){
			printf("(");
			printf("%d", snake.array[i][0]);
			printf(", ");
			printf("%d", snake.array[i][1]);
			printf("),");
		}
		printf("]\n");
		for(int i = 0; i < 900; i++){
			paths.array[0][i][0] = 0;
			paths.array[0][i][1] = 0;
		}
		while(true){ // generate apple position
			bool inSnake = false;
			apple[0] = rand() % 30;
			apple[1] = rand() % 30;
			for(int y = 0 ; y < epoch; y++){
				if(snake.array[y][0] == apple[0] && snake.array[y][1] == apple[1]){
					inSnake = true;
				}
			}
			if(!inSnake){
				break;
			}
		}
		// printf("apple: ");
		// printf("%d", apple[0]);
		// printf(" ");
		// printf("%d", apple[1]);
		// printf("\n");
		int result = search(snake.array[0], apple, &snake, epoch, &paths, 1);
		if(result == 0){
			// printf("[");
			// for(int i = 0; i < length; i++){
			// 	printf("(");
			// 	printf("%d", snake.array[i][0]);
			// 	printf(", ");
			// 	printf("%d", snake.array[i][1]);
			// 	printf("),");
			// }
			// printf("]\n");
			// printf("%d", epoch);
			// printf("\n");
			// printf("%d", length);
			printf("\n");
			printf("%d", apple[0]);
			printf(", ");
			printf("%d", apple[1]);
			return epoch;
			break;
		}
		for(int i = 0; i < length; i++){
			paths.array[0][i + paths.lengths[0]][0] = snake.array[i][0];
			paths.array[0][i + paths.lengths[0]][1] = snake.array[i][1];
		}
		length++;
		for(int i = 0; i < length; i++){
			snake.array[i][0] = paths.array[0][i][0];
			snake.array[i][1] = paths.array[0][i][1];
		}
		// epoch == rowIndex
		// for(int colIndex = 0; colIndex < epoch; colIndex++){ // copy snake into dataset
		// 	dataset[(((epoch) * (epoch + 1))/ 2 + colIndex) * 2] = snake.array[colIndex][0];
		// 	dataset[(((epoch) * (epoch + 1))/ 2 + colIndex) * 2 + 1] = snake.array[colIndex][1];
		// }
	}
	return 0;
}

int search(int start[2], int end[2], Snake *snake, int length, Paths *paths, int number){
	int pathsFound = 0;
	int neighbors[4][2];

	int closedSize = 1;
	node closed[900];

	int queueSize = 1;
	node *queue[100000];

	node root = {{start[0], start[1]}, NULL, 0};
	
	closed[0] = root;
	queue[0] = &(closed[0]);
	while (queueSize != 0 && queueSize < 100000){
		// sets all neighbor values to -1
		for (int r = 0; r < 4; r++){
			for (int c = 0; c < 2; c++){
				neighbors[r][c] = -1;
			}
		}
		// get lowest value node from queue
		// int lowestIndex = -1;
		// double lowestValue = 1000.0;
		// for(int i = 0; i < queueSize; i++){
		// 	double score = euclidian((*queue[i]).value, end);
		// 	if(lowestValue > score){
		// 		lowestIndex = i;
		// 		lowestValue = score;
		// 	}
		// }

		node *current = queue[0];

		// removing current from queue
		for (int i = 0; i < queueSize - 1; i++){ // shift everything one to the left
			queue[i] = queue[i + 1];
		}

		queueSize--;

		// checking if current is end
		if ((*current).value[0] == end[0] && (*current).value[1] == end[1]){
			// writing path and length
			int depth = (*current).depth;
			node *temp = &(*current);
			int count = 0;
			printf("[");
			for(int x = 0; x < depth; x++){
				paths->array[pathsFound][count][0] = (*temp).value[0];
				paths->array[pathsFound][count][1] = (*temp).value[1];
				memcpy(&temp, &((*temp).parent), sizeof(node *));
				printf("(");
				printf("%d", (*temp).value[0]);
				printf(", ");
				printf("%d", (*temp).value[1]);
				printf("), ");
				count++;
			}
			printf("]\n");


			paths->lengths[pathsFound] = depth;

			pathsFound++;

			if(pathsFound == 4){
				printf("%d", queueSize);
				printf("\n");
				return depth;
			}

			continue;
		}
		//debugging
		printf("("); 
		printf("%d", (*current).value[0]);
		printf(", ");
		printf("%d", (*current).value[1]);
		printf("),");
		printf("\n");
		get_neighbors((*current).value, snake, neighbors, length, (*current).depth);
		for (int i = 0; i < 4; i++){
			// checking if we want to add this node to the queue
			node neighbor = {{neighbors[i][0], neighbors[i][1]}, &(*current), (*current).depth + 1};

			if (neighbors[i][0] == -1){
				continue;
			}
			if(contains(neighbor, closed, closedSize)){
				continue;
			}
			
			queueSize++;
			closedSize++;
			closed[closedSize - 1] = neighbor;
			queue[queueSize - 1] = &closed[closedSize - 1];
		}
	}
	printf("%d", queueSize);
	return 0;
}

bool contains(node current, node array[], int length){
	for(int i = 0; i < length; i++){
		if(current.value[0] == array[i].value[0] && current.value[1] == array[i].value[1]){
			return true;
		}
	}
	return false;
}

void get_neighbors(int point[], Snake *snake, int neighbors[4][2], int length, int depth){

	if (point[0] + 1 < 30){
		neighbors[2][0] = point[0] + 1;
		neighbors[2][1] = point[1];
	}
	if (point[0] - 1 > -1){
		neighbors[0][0] = point[0] - 1;
		neighbors[0][1] = point[1];
	}
	if (point[1] + 1 < 30){
		neighbors[1][0] = point[0];
		neighbors[1][1] = point[1] + 1;
	}
	if (point[1] - 1 > -1){
		neighbors[3][0] = point[0];
		neighbors[3][1] = point[1] - 1;
	}

	// check if neighbor is snake
	for (int i = 0; i < (length - depth); i++){
		for (int r = 0; r < 4; r++){
			if(neighbors[r][0] == snake->array[i][0] && neighbors[r][1] == snake->array[i][1]){
				neighbors[r][0] = -1;
				neighbors[r][1] = -1;
			}
		}
	}
}

double euclidian(int a[2], int b[2]){
	int x = abs(a[0] - b[0]);
	int y = abs(a[1] - b[1]);
	return sqrt(x * x + y * y);
}