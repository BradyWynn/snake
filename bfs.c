#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int euclidian(int[], int[]);
int bfs(int[2], int[2], int[900][2], int, int[900][2]);
void getNeighbors(int[], int[900][2], int[4][2], int);

typedef struct node
{
	int value[2];
	struct node *parent;
	int depth;
} node;

int snake[900][2];
int path[900][2];
int length = 1;

int main(){
	// clock_t tic = clock();

	snake[0][0] = 1;
	snake[0][1] = 1;

	int start[] = {0, 0};
	int end[] = {29, 29};
	int a = bfs(start, end, snake, length, path);
	for(int i = 0; i < a; i++){
		printf("%d", path[i][0]);
		printf(" ");
		printf("%d", path[i][1]);
		printf("\n");
	}

	// printf("%d", a);

	// clock_t toc = clock();
    // printf("Elapsed: %f seconds\n", (toc - tic) / CLOCKS_PER_SEC);

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

// void gameSim(){

// }

int bfs(int start[2], int end[2], int snake[900][2], int length, int path[900][2]){
	int treeSize = 1;
	int queueSize = 1;
	int neighbors[4][2];
	node *tree = (node *)malloc(sizeof(node) * 900); // dynamic array of all nodes
	node **queue = (node **)malloc(sizeof(node *)); // dynamic array of pointers to non-evaluated nodes
	node head = {{0, 0}, NULL, 0};
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
		int lowestValue = 1000;
		for(int i = 0; i < queueSize; i++){
			if(lowestValue > euclidian((*queue[i]).value, end)){
				lowestIndex = i;
				lowestValue = euclidian((*queue[i]).value, end);
			}
		}
		node *current = queue[lowestIndex];
		// printf("%d", (*current).value[0]);
		// printf(" ");
		// printf("%d", (*current).value[1]);
		// printf("\n");
		if ((*current).value[0] == end[0] && (*current).value[1] == end[1]){
			int depth = (*current).depth;
			int count = 0;
			for(int x = 0; x < depth; x++){
				memcpy(&current, &((*current).parent), sizeof(node *));
				path[count][0] = (*current).value[0];
				path[count][1] = (*current).value[1];
				count++;
			}
			printf("path found");
			free(tree);
			free(queue);
			return depth;
		}
		getNeighbors((*current).value, snake, neighbors, length);
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
					// printf("%d", neighbor.value[0]);
					// printf(" ");
					// printf("%d", neighbor.value[1]);
					// printf(" ");
					// printf("%d", (*p_parent).value[0]);
					// printf(" ");
					// printf("%d", (*p_parent).value[1]);

					// printf("%p", (*p_parent).parent);
					// printf(" ");
					// printf("%p", p_parent);

					// printf("\n");
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

void getNeighbors(int point[], int snake[900][2], int neighbors[4][2], int length){

	if (point[0] + 1 < 30){
		neighbors[0][0] = point[0] + 1;
		neighbors[0][1] = point[1];
	}
	if (point[0] - 1 > -1){
		neighbors[2][0], point[0] - 1;
		neighbors[2][1], point[1];
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
	for (int i = 0; i < length; i++){
		if (point[0] == snake[i][0]){
			if (point[1] + 1 == snake[i][1]){
				neighbors[1][0] = -1;
				neighbors[1][1] = -1;
			}
			if (point[1] - 1 == snake[i][1]){
				neighbors[3][0] = -1;
				neighbors[3][1] = -1;
			}
		}
		if (point[1] == snake[i][1]){
			if (point[0] + 1 == snake[i][0]){
				neighbors[0][0] = -1;
				neighbors[0][1] = -1;
			}
			if (point[0] - 1 == snake[i][0]){
				neighbors[2][0] = -1;
				neighbors[2][1] = -1;
			}
		}
	}
}

int euclidian(int a[2], int b[2]){
	int x = abs(a[0] - b[0]);
	int y = abs(a[1] - b[1]);
	return sqrt(x * x + y * y);
}