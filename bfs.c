#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int euclidian(int[], int[]);
int bfs(int(*)[2], int(*)[2], int(*)[900][2], int);
void getNeighbors(int[], int(*)[900][2], int(*)[4][2], int);

typedef struct node{
  int value[2];
  struct node *parent;
  int depth;
}node;

int snake[900][2];
int length = 1;

int main(){
	// snake[0][0] = 1;
	snake[0][1] = 2;

	int start[] = {0, 0};
	int end[] = {1, 1};
	int neighbors[4][2];
	getNeighbors(start, &snake, &neighbors, length);
	for(int i = 0; i < 4; i++){
		printf("%d", neighbors[i][0]);
		printf(" ");
		printf("%d", neighbors[i][1]);
		printf("\n");
	}
	// int a = bfs(&start, &end, &snake, length);
	// printf("%d", a);
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

// int bfs(int (*start)[2], int (*end)[2], int (*snake)[900][2], int length){
//     int treeSize = 1;
//     int neighbors[4][2];
//     node *tree = malloc(sizeof(node));
//     node head = {{0, 0}, NULL, 5};
//     tree[0] = head;
//     while(treeSize != 0){
//         node current = tree[0];
//         printf("%d", current.depth);
//         printf("\n");
//         if(current.value[0] == *end[0]){
//             printf("path found");
//             free(tree);
//             return 1;
//         }
//         getNeighbors(current.value, snake, &neighbors, length); 
//         for(int i = 0; i < 4; i++){
//             if(neighbors[i] != NULL){
//                 bool add = true;
//                 node neighbor = {{neighbors[i][0], neighbors[i][1]}, &current, current.depth + 1};
//                 for(int i = 0; i < treeSize; i++){
//                     if(neighbor.value[0] == tree[i].value[0], neighbor.value[0] == tree[i].value[0], neighbor.depth == tree[i].depth){
//                         add = false;
//                         break;
//                     }
//                 }
//                 node temp = {{neighbor.value[0], neighbor.value[1]}, neighbor.parent, neighbor.depth};
//                 for(int i = 0; i < neighbor.depth; i++){
//                     memcpy(&temp, neighbor.parent, sizeof(node));
//                     if(neighbor.value[0] == temp.value[0], neighbor.value[0] == temp.value[0]){
//                         add = false;
//                         break;
//                     }
//                 }
//                 if(add){
//                     treeSize++;
//                     tree = realloc(tree, treeSize * sizeof(node));
//                     tree[treeSize] = neighbor;
//                 }
//             }
//         }
//         int index = 0;
//         for(int i = 0; i < treeSize; i++){
//             if(current.value[0] == tree[i].value[0], current.value[0] == tree[i].value[0], current.depth == tree[i].depth){
//                 index = i;
//                 break;
//             }
//         }
//         for(int i = index; i < treeSize - 1; i++){
//             tree[i] = tree[i + 1];
//         }
//         treeSize--;
//         tree = realloc(tree, treeSize * sizeof(node));

//     }
//     free(tree);
//     return 0;
// }

void getNeighbors(int point[], int (*p_snake)[900][2], int (*p_neighbors)[4][2], int length){
	int *p_top = (point[0] + 1);

	if(point[0] + 1 < 30){
		memcpy(p_neighbors[0][0], p_top, sizeof(int)); //pain
		memcpy(p_neighbors[0][1], &point[1], sizeof(int));
	}
	if(point[0] - 1 > -1){
		memcpy(p_neighbors[2][0], point[0] - 1, sizeof(int));
		memcpy(p_neighbors[2][1], &point[1], sizeof(int));
	}
	if(point[1] + 1 < 30){
		memcpy(p_neighbors[1][0], &point[0], sizeof(int));
		memcpy(p_neighbors[1][1], point[1] + 1, sizeof(int));
	}
	if(point[1] - 1 > -1){
		memcpy(p_neighbors[1][0], &point[0], sizeof(int));
		memcpy(p_neighbors[1][1], point[1] - 1, sizeof(int));
	}

	int a = 1;
	int *null = &a; 
	// check if neighbor is snake
	for(int i = 0; i < length; i++){
		if(point[0] == *p_snake[i][0]){
			if(point[1] + 1 == *p_snake[i][1]){
				memcpy(p_neighbors[1][0], null, sizeof(int));
				memcpy(p_neighbors[1][1], null, sizeof(int));
			}
			if(point[1] - 1 == *p_snake[i][1]){
				memcpy(p_neighbors[3][0], null, sizeof(int));
				memcpy(p_neighbors[3][1], null, sizeof(int));
			}
		}
		if(point[1] == *p_snake[i][1]){
			if(point[0] + 1 == *p_snake[i][0]){
				memcpy(p_neighbors[0][0], null, sizeof(int));
				memcpy(p_neighbors[0][1], null, sizeof(int));
			}
			if(point[0] - 1 == *p_snake[i][0]){
				memcpy(p_neighbors[2][0], null, sizeof(int));
				memcpy(p_neighbors[2][1], null, sizeof(int));
			}
		}
	}
		
}

int euclidian(int a[2], int b[2]){
	int x = abs(a[0] - b[0]);
	int y = abs(a[1] - b[1]);
	return sqrt(x * x + y * y);
}