#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int euclidian(int a[], int b[]);
int bfs(int start[], int end[], int (*snake)[900][2], int length);
void getNeighbors(int point[], int (*snake)[900][2], int (*neighbors)[4][2], int length);

typedef struct node{
  int value[2];
  struct node *parent;
  int depth;
}node;

int main(){
    int snake[900][2];
    int length = 1;
    snake[0][0] = 1;
    snake[0][1] = 2;

    int start[] = {0, 0};
    int end[] = {1, 1};
    int a = bfs(start, end, &snake, length);
    printf("%d", a);
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

int bfs(int start[], int end[], int (*snake)[900][2], int length){
    int tree_size = 1;
    int neighbors[4][2];
    node *tree = malloc(sizeof(node));
    node head = {{0, 0}, NULL, 5};
    tree[0] = head;
    while(tree_size != 0){
        node current = tree[0];
        printf("%d", current.depth);
        printf("\n");
        if(current.value[0] == end[0]){
            printf("path found");
            free(tree);
            return 1;
        }
        getNeighbors(current.value, snake, &neighbors, length); 
        for(int i = 0; i < 4; i++){
            if(neighbors[i] != NULL){
                bool add = true;
                node neighbor = {{neighbors[i][0], neighbors[i][1]}, &current, current.depth + 1};
                for(int i = 0; i < tree_size; i++){
                    if(neighbor.value[0] == tree[i].value[0], neighbor.value[0] == tree[i].value[0], neighbor.depth == tree[i].depth){
                        add = false;
                        break;
                    }
                }
                node temp = {{neighbor.value[0], neighbor.value[1]}, neighbor.parent, neighbor.depth};
                for(int i = 0; i < neighbor.depth; i++){
                    memcpy(&temp, neighbor.parent, sizeof(node));
                    if(neighbor.value[0] == temp.value[0], neighbor.value[0] == temp.value[0]){
                        add = false;
                        break;
                    }
                }
                if(add){
                    tree_size++;
                    tree = realloc(tree, tree_size * sizeof(node));
                    tree[tree_size] = neighbor;
                }
            }
        }
        int index = 0;
        for(int i = 0; i < tree_size; i++){
            if(current.value[0] == tree[i].value[0], current.value[0] == tree[i].value[0], current.depth == tree[i].depth){
                index = i;
                break;
            }
        }
        for(int i = index; i < tree_size - 1; i++){
            tree[i] = tree[i + 1];
        }
        tree_size--;
        tree = realloc(tree, tree_size * sizeof(node));

    }
    free(tree);
    return 0;
}

void getNeighbors(int point[], int (*snake)[900][2], int (*neighbors)[4][2], int length){
    if(point[0] + 1 < 30){
        memcpy(neighbors[0][0], &point[0] + 1, sizeof(int)); //pain
        memcpy(neighbors[0][1], &point[1], sizeof(int));
    }
    if(point[0] - 1 > -1){
        memcpy(neighbors[2][0], &point[0] - 1, sizeof(int));
        memcpy(neighbors[2][1], &point[1], sizeof(int));
    }
    if(point[1] + 1 < 30){
        memcpy(neighbors[1][0], &point[0], sizeof(int));
        memcpy(neighbors[1][1], &point[1] + 1, sizeof(int));
    }
    if(point[1] - 1 > -1){
        memcpy(neighbors[1][0], &point[0], sizeof(int));
        memcpy(neighbors[1][1], &point[1] - 1, sizeof(int));
    }

    // check if neighbor is snake
    for(int i = 0; i < length; i++){
        if(point[0] == *snake[i][0]){
            if(point[1] + 1 == *snake[i][1]){
                memcpy(neighbors[1], NULL, sizeof(int));
            }
            if(point[1] - 1 == *snake[i][1]){
                memcpy(neighbors[3], NULL, sizeof(int));
            }
        }
        if(point[1] == *snake[i][1]){
            if(point[0] + 1 == *snake[i][0]){
                memcpy(neighbors[0], NULL, sizeof(int));
            }
            if(point[0] - 1 == *snake[i][0]){
                memcpy(neighbors[2], NULL, sizeof(int));
            }
        }
    }
        
}

int euclidian(int a[2], int b[2]){
    int x = abs(a[0] - b[0]);
    int y = abs(a[1] - b[1]);
    return sqrt(x * x + y * y);
}