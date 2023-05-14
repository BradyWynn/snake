#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// int euclidian(int[], int[]);
int bfs(int[2], int[2], int[900][2], int);
void getNeighbors(int[], int[900][2], int[4][2], int);

typedef struct node
{
	int value[2];
	struct node *parent;
	int depth;
} node;

int snake[900][2];
int length = 1;

int main(){
	// clock_t tic = clock();

	snake[0][0] = 1;
	snake[0][1] = 1;

	int start[] = {0, 0};
	int end[] = {10, 2};
	int a = bfs(start, end, snake, length);

	printf("%d", a);

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

// def BFS(start, end, snake, n):
//     paths = []
//     tree = [Node(start, 0, [], euclidian(start, end))]
//     while len(tree) != 0:
//         min_val = 1000000
//         min_node = None
//         for i in tree:
//             if i.depth + i.h < min_val:
//                 min_val = i.depth + i.h
//                 min_node = i
//         current = min_node
//         if current.value == end:
//             paths.append(list(reversed(current.path)))
//         if len(paths) == n:
//             return paths
//         neighbors = get_neighbors(current.value, snake, current.depth)
//         for neighbor in neighbors:
//             if neighbor is not None:
//                 node = Node(neighbor, current.depth + 1, current.path, euclidian(neighbor, end))
//                 if node not in tree and neighbor not in current.path:
//                     tree.append(node)
//         tree.remove(current)
//     return paths

int bfs(int start[2], int end[2], int snake[900][2], int length){
	int treeSize = 1;
	int queueSize = 1;
	int neighbors[4][2];
	node *tree = (node *)malloc(sizeof(node) * 900); // dynamic array of all nodes
	node **queue = (node **)malloc(sizeof(node *)); // dynamic array of pointers to non-evaluated nodes
	node head = {{0, 0}, NULL, 0};
	tree[0] = head;
	queue[0] = &head;
	while (queueSize != 0){
		for (int r = 0; r < 4; r++){
			for (int c = 0; c < 2; c++){
				neighbors[r][c] = -1;
			}
		}
		// get lowest value node from queue
		node *current = queue[0];
		printf("%d", (*current).value[0]);
		printf(" ");
		printf("%d", (*current).value[1]);
		printf("\n");
		if ((*current).value[0] == end[0] && (*current).value[1] == end[1]){
			printf("path found");
			free(tree);
			free(queue);
			return 1;
		}
		getNeighbors((*current).value, snake, neighbors, length);
		for (int i = 0; i < 4; i++){
			if (neighbors[i][0] != -1){
				bool add = true;
				node neighbor = {{neighbors[i][0], neighbors[i][1]}, &(*current), (*current).depth + 1};
				for (int y = 0; y < treeSize; y++){ // checking the node isn't already in tree
					if (neighbor.value[0] == tree[y].value[0] && neighbor.value[0] == tree[y].value[0] && neighbor.depth == tree[y].depth){
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
					// p_parent = (*p_parent).parent;
					// printf("%p", p_parent);
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
			if ((*current).value[0] == (*queue)[i].value[0] && (*current).value[1] == (*queue)[i].value[1] && (*current).depth == (*queue)[i].depth){
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