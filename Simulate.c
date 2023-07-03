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

int main(){
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
	// int a[] = {0, 6};
	// int b[] = {0, 1};
	// int c = euclidian(a, b);
	// printf("%d", c);
	f();
	
	// for(int i = 0; i < 10; i++){
	// 	int length = simulate(dataset);
	// 	printf("\n");
	// 	printf("%d", length);
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
	int apple[] = {29, 8};
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
		// printf("[");
		// for(int i = 0; i < length; i++){
		// 	printf("(");
		// 	printf("%d", snake[i][0]);
		// 	printf(", ");
		// 	printf("%d", snake[i][1]);
		// 	printf("),");
		// }
		// printf("]\n");
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
			// printf("%d", epoch);
			return epoch;
			break;
		}
		// printf("[");
		// for(int i = 0; i < result; i++){
		// 	printf("(");
		// 	printf("%d", path[i][0]);
		// 	printf(", ");
		// 	printf("%d", path[i][1]);
		// 	printf("),");
		// }
		// printf("]\n");
		for(int i = 0; i < length; i++){
			paths.array[0][i + result][0] = snake.array[i][0];
			paths.array[0][i + result][1] = snake.array[i][1];
		}
		length++;
		for(int i = 0; i < length; i++){
			snake.array[i][0] = paths.array[0][i][0];
			snake.array[i][1] = paths.array[0][i][1];
		}
		// epoch == rowIndex
		for(int colIndex = 0; colIndex < epoch; colIndex++){ // copy snake into dataset
			dataset[(((epoch) * (epoch + 1))/ 2 + colIndex) * 2] = snake.array[colIndex][0];
			dataset[(((epoch) * (epoch + 1))/ 2 + colIndex) * 2 + 1] = snake.array[colIndex][1];
		}
	}
	return 0;
}

int search(int start[2], int end[2], Snake *snake, int length, Paths *paths, int number){
	int treeSize = 1;
	int pathsFound = 0;
	int queueSize = 1;
	int neighbors[4][2];
	node *tree = (node *)malloc(sizeof(node) * 100000); // dynamic array of all nodes
	node **queue = (node **)malloc(sizeof(node *)); // dynamic array of pointers to non-evaluated nodes
	node head = {{start[0], start[1]}, NULL, 0};
	tree[0] = head;
	queue[0] = &tree[0];
	while (queueSize != 0){
		for (int r = 0; r < 4; r++){
			for (int c = 0; c < 2; c++){
				neighbors[r][c] = -1;
			}
		}
		// get lowest value node from queue
		int lowestIndex = -1;
		double lowestValue = 1000.0;
		for(int i = 0; i < queueSize; i++){
			double score = euclidian((*queue[i]).value, end);
			if(lowestValue > score){
				lowestIndex = i;
				lowestValue = score;
			}
		}
		node *current = queue[lowestIndex];
		if ((*current).value[0] == end[0] && (*current).value[1] == end[1]){
			// writing path and length
			node *temp = &(*current);
			int depth = (*current).depth;
			int count = 0;
			for(int x = 0; x < depth; x++){
				paths->array[pathsFound][count][0] = (*temp).value[0];
				paths->array[pathsFound][count][1] = (*temp).value[1];
				memcpy(&temp, &((*temp).parent), sizeof(node *));
				count++;
			}
			
			paths->lengths[pathsFound] = depth;

			// this is just removing the final node ???
			int index = -1;
			for (int i = 0; i < queueSize; i++){ // get index of current in queue
				if (current == queue[i]){
					index = i;
					break;
				}
			}

			for (int i = index; i < queueSize - 1; i++){ // shift everything one to the left
				queue[i] = queue[i + 1];
			}

			pathsFound++;

			if(pathsFound == 4){
				free(tree);
				free(queue);
				return depth;
			}

			queueSize--;
			queue = (node **)realloc(queue, queueSize * sizeof(node *));
			continue;
		}
		printf("("); 
		printf("%d", (*current).value[0]);
		printf(", ");
		printf("%d", (*current).value[1]);
		printf("),");
		printf("\n");
		get_neighbors((*current).value, snake, neighbors, length, (*current).depth);
		for (int i = 0; i < 4; i++){
			if (neighbors[i][0] != -1){
				bool add = true;
				node neighbor = {{neighbors[i][0], neighbors[i][1]}, &(*current), (*current).depth + 1};
				node *p_parent = &(*current);
				for(int x = 0; x < neighbor.depth; x++){ // traversing up tree to check node hasn't been in path so far
				    if(neighbor.value[0] == (*p_parent).value[0] && neighbor.value[1] == (*p_parent).value[1]){
				        add = false;
				        break;
				    }
					memcpy(&p_parent, &((*p_parent).parent), sizeof(node *));
				}
				if (add){
					treeSize++;
					queueSize++;
					queue = (node **)realloc(queue, queueSize * sizeof(node *));
					tree[treeSize - 1] = neighbor;
					queue[queueSize - 1] = &tree[treeSize - 1];
				}
			}
		}
		int index = -1;
		for (int i = 0; i < queueSize; i++){ // get index of current in queue
			if (current == queue[i]){
				index = i;
				break;
			}
		}
		for (int i = index; i < queueSize - 1; i++){ // shift everything one to the left
			queue[i] = queue[i + 1];
		}
		queueSize--;
		queue = (node **)realloc(queue, queueSize * sizeof(node *));
	}
	free(tree);
	free(queue);
	return 0;
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