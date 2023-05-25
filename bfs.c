#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int gameSim(int *);
double euclidian(int[], int[]);
int bfs(int[2], int[2], int[900][2], int, int[900][2]);
void getNeighbors(int[], int[900][2], int[4][2], int, int);

typedef struct node
{
	int value[2];
	struct node *parent;
	int depth;
} node;


int main(){
	// clock_t t;
	// t = clock();
	// int ***dataset = (int ***)malloc(sizeof(int **) * 900);
	// for(int i = 0; i < 900; i++){
	// 	int **a = (int **)malloc(sizeof(int *) * i);
	// 	for(int x = 0; x < i; x++){
	// 		int *b = (int *)malloc(sizeof(int) * 2);
	// 		a[x] = b;
	// 	}
	// 	dataset[i] = a;
	// }

	// int length = gameSim(dataset);
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

// def game_sim():
//     snake = [(14, 14)]
//     dataset = []
//     moves = 0
//     while True:
//         dataset.append(snake.copy())
//         while True:
//             apple = (int(np.random.rand(1) * board_size), int(np.random.rand(1) * board_size))
//             if apple not in snake:
//                 break
//         pathington = BFS(snake[0], apple, snake, 1)
//         if len(pathington) == 0:
//             return dataset, moves, len(snake)
//         path = pathington[0]
//         moves += len(path)
//         path = path + snake
//         snake.append((0, 0))
//         for i, piece in enumerate(snake):
//             snake[i] = path[i]

int gameSim(int *dataset){
	srand((unsigned) time(NULL));
	int snake[900][2];
	int path[900][2];
	snake[0][0] = 0;
	snake[0][1] = 0;
	int apple[2];
	int moves = 0;
	int length = 1;
	for(int epoch = 0; epoch < 200; epoch++){
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
			path[i][0] = 0;
			path[i][1] = 0;
		}
		while(true){ // generate apple position
			bool inSnake = false;
			apple[0] = rand() % 30;
			apple[1] = rand() % 30;
			for(int y = 0 ; y < epoch; y++){
				if(snake[y][0] == apple[0] && snake[y][1] == apple[1]){
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
		int result = bfs(snake[0], apple, snake, epoch, path);
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
			path[i + result][0] = snake[i][0];
			path[i + result][1] = snake[i][1];
		}
		length++;
		for(int i = 0; i < length; i++){
			snake[i][0] = path[i][0];
			snake[i][1] = path[i][1];
		}
		// epoch == rowIndex
		for(int colIndex = 0; colIndex < epoch; colIndex++){ // copy snake into dataset
			dataset[(((epoch) * (epoch + 1))/ 2 + colIndex) * 2] = snake[colIndex][0];
			dataset[(((epoch) * (epoch + 1))/ 2 + colIndex) * 2 + 1] = snake[colIndex][1];
		}
	}
	return 0;
}

int bfs(int start[2], int end[2], int snake[900][2], int length, int path[900][2]){
	int treeSize = 1;
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
			if(lowestValue > euclidian((*queue[i]).value, end)){
				lowestIndex = i;
				lowestValue = euclidian((*queue[i]).value, end);
			}
		}
		node *current = queue[lowestIndex];
		// printf("(");
		// printf("%d", (*current).value[0]);
		// printf(", ");
		// printf("%d", (*current).value[1]);
		// printf("),");
		if ((*current).value[0] == end[0] && (*current).value[1] == end[1]){
			int depth = (*current).depth;
			int count = 0;
			for(int x = 0; x < depth; x++){
				path[count][0] = (*current).value[0];
				path[count][1] = (*current).value[1];
				memcpy(&current, &((*current).parent), sizeof(node *));
				count++;
			}
			// printf("path found");
			free(tree);
			free(queue);
			return depth;
		}
		getNeighbors((*current).value, snake, neighbors, length, (*current).depth);
		for (int i = 0; i < 4; i++){
			if (neighbors[i][0] != -1){
				bool add = true;
				node neighbor = {{neighbors[i][0], neighbors[i][1]}, &(*current), (*current).depth + 1};
				for (int y = 0; y < treeSize; y++){ // checking the node isn't already in tree
					if (neighbor.value[0] == tree[y].value[0] && neighbor.value[1] == tree[y].value[1] && neighbor.depth == tree[y].depth){
						add = false;
						break;
					}
				}
				node *p_parent = &neighbor;
				for(int x = 0; x < neighbor.depth; x++){ // traversing up tree to check node hasn't been in path so far
					memcpy(&p_parent, &((*p_parent).parent), sizeof(node *));
				    if(neighbor.value[0] == (*p_parent).value[0] && neighbor.value[1] == (*p_parent).value[1]){
				        add = false;
				        break;
				    }
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

void getNeighbors(int point[], int snake[900][2], int neighbors[4][2], int length, int depth){

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
			if(neighbors[r][0] == snake[i][0] && neighbors[r][1] == snake[i][1]){
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