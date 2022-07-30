using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Graph {
    public List<Node> graph = new List<Node>();
    public int sideLength;
    public List<Node> snakeNodes = new List<Node>();
    public Node apple = new Node();
    public Graph(int _sideLength){
        sideLength = _sideLength;
        for (int i = 0; i < sideLength*sideLength; i++){
            Node node = new Node();
            graph.Add(node);
            node.num = i;
        }
        foreach (Node node in graph){
            node.ResetMyNeighboursList(node.num, sideLength, graph);

            int row = (node.num - (node.num % sideLength))/sideLength;
            int col = node.num % sideLength;

            graph[node.num].position = new Vector3(col, 0, row);
            graph[node.num].num = node.num;
        }      
    }

    // public float Evaluate(Vector3 applePos, List<Node> snakeNodes){
    //     float travesability = 0; 
    //     float samples = 200;
    //     List<Vector3> apples = new List<Vector3>();


    //     // generate valid apple posiitons
    //     while(apples.Count < samples){
    //         float x = Random.Range(0, 30);
    //         float y = Random.Range(0, 30);
            
    //         for(int w = 0; w < snakeNodes.Count; w++){ // this can sped up significantly by just looking up isSnake variable on node instead of looping
    //             if(snakeNodes[w].position.x != x && snakeNodes[w].position.z != y){
    //                 apples.Add(new Vector3(x, 0, y));
    //             }
    //         }
    //     }

    //     foreach (Vector3 apple in apples){
    //         List<Node> returnList = Astar.FindPath(snakeNodes[snakeNodes.Count - 1], Snake.PosToNode(apple, graph));
    //         travesability = travesability + returnList.Count;
    //     }

    //     return travesability/samples;
    // }

    public void RepairGraph(){
        // updates all the connections to the tail of the snake
        Node tail = snakeNodes[0];
        int i = tail.num;
        int sideLength = 31;
        tail.neighboursList.Clear();

        tail.ResetBothNeighboursList(i, sideLength, graph);
        // foreach(Node snakeBody in snakeNodes){
        //    snakeBody.ResetBothNeighboursList(snakeBody.num, sideLength, graph); 
        // }
    }

    public void UpdateGraph(){
        List<Node> NodesToDelete = new List<Node>();

        // deletes all the connects inside the snake on the graph preventing it from generating paths that cross itself
        // foreach (Node snakeBody in snakeNodes){
        //     if(snakeBody != snakeNodes[snakeNodes.Count - 1]){
        //         foreach (Node neighbor in snakeBody.neighboursList){
        //             foreach (Node bodyPiece in snakeNodes){
        //                 if(neighbor.position == bodyPiece.position){
        //                 }
        //                 else{
        //                     NodesToDelete.Add(neighbor);
        //                 }
        //             }
        //         }
        //         foreach(Node delete in NodesToDelete){
        //             snakeBody.neighboursList.Remove(delete);
        //             delete.neighboursList.Remove(snakeBody);
        //         }
        //     }
        // }
        Node head = snakeNodes[snakeNodes.Count - 1];
        foreach(Node neighbor in head.neighboursList){
            NodesToDelete.Add(neighbor);
        }
        foreach(Node delete in NodesToDelete){
            head.neighboursList.Remove(delete);
            delete.neighboursList.Remove(head);
        }
    }

    public Node PosToNode(Vector3 pos){
        // for (int i = 0; i < graph.Count; i++){
        //     if(graph[i].position == pos){
        //         return graph[i];
        //     }
        // }
        int x = (int)pos.x;
        int y = (int)pos.z;
        return graph[(y * sideLength) + x];
    } 

    public void SpawnApple(){
        float x = Random.Range(0, 30);
        float y = Random.Range(0, 30);
        
        for(int i = 0; i < snakeNodes.Count; i++){
            if(snakeNodes[i].position.x == x && snakeNodes[i].position.z == y){
                SpawnApple();
                return;
            }
        }
        apple = PosToNode(new Vector3(x, 0, y));
        // apple.position = new Vector3(x, 0, y);
    }
    public List<Node> AppleCheck(Node currentPos, int count){
        if(currentPos == apple){
            // count = 0;
            // applesEaten++;
            // eatenAppleThisStep = true;
            Extend(currentPos);
            SpawnApple(); 
            Debug.Log("ran");

            List<Node> path = Astar.FindPath(snakeNodes[snakeNodes.Count - 1], apple);
            return path;
        }
        else{
            UpdateBody(currentPos);
        }
        return null;
    }

    public void Extend(Node currentPos){
        snakeNodes.Add(currentPos);
        currentPos.isSnake = true;

        // GameObject piece = Instantiate(snakeBodyPrefab, transform.localPosition, Quaternion.identity);
        // snakeObj.Add(piece);
    }

    public void UpdateBody(Node currentPos){
        // if the player hasn't eaten an apple this step then move butt to front
        Node butt = snakeNodes[0];
        snakeNodes.Remove(butt);
        snakeNodes.Add(currentPos);
    }
}