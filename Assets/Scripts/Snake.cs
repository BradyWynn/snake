using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snake : MonoBehaviour{
    public int applesEaten = 0;
    // public Vector3 dir = Vector3.zero;
    public int count = 0;
    // public GameObject applePrefab;
    // public GameObject snakeBodyPrefab;
    // public GameObject appleObj;
    // public List<GameObject> snakeObj = new List<GameObject>();
    // public List<Node> snakeNodes = new List<Node>();
    // public bool eatenAppleThisStep;
    Graph graph = new Graph(31);
    List<Node> path = new List<Node>();
    int slowerdowner = 0;

    void Start(){
        Node startingPos = graph.PosToNode(transform.position);
        graph.Extend(startingPos);
        // appleObj = Instantiate(applePrefab, new Vector3(25, 0, 15), Quaternion.identity);
        // appleNode = PosToNode(new Vector3(25, 0, 15), graph.graph);
        graph.SpawnApple();
        path = Astar.FindPath(graph.snakeNodes[graph.snakeNodes.Count - 1], graph.apple);
    }

    void Update(){
        if(slowerdowner % 50 == 0){
            // RenderSnake();

            if(graph.snakeNodes.Count > 1){
                graph.UpdateGraph();
            }


            List<Node> returned = graph.AppleCheck(path[count], count);
            graph.RepairGraph();
            if(returned != null){
                path = returned;
                count = 0;
            }
            DrawConnections();

            count++;
        }
        slowerdowner++;
    }
    // void OnDrawGizmos(){
    //     // Draw a semitransparent blue cube at the transforms position
    //     foreach(Node snakeBody in graph.snakeNodes){
    //         Gizmos.DrawCube(snakeBody.position, new Vector3(1, 1, 1));
    //     }
    // }

    // void SpawnApple(){
    //     float x = Random.Range(0, 30);
    //     float y = Random.Range(0, 30);
        
    //     for(int i = 0; i < snakeNodes.Count; i++){
    //         if(snakeNodes[i].position.x == x && snakeNodes[i].position.z == y){
    //             SpawnApple();
    //             return;
    //         }
    //     }
    //     appleNode = PosToNode(new Vector3(x, 0, y), graph.graph);
    //     appleNode.position = new Vector3(x, 0, y);
    // }

    // void AppleCheck(){
    //     if(transform.localPosition == appleNode.position){
    //         applesEaten++;
    //         eatenAppleThisStep = true;
    //         Extend();
    //         SpawnApple(); 
    //     }
    // }

    // void Extend(){
    //     Node newNode = PosToNode(transform.localPosition, graph.graph);
    //     snakeNodes.Add(newNode);
    //     newNode.isSnake = true;

    //     GameObject piece = Instantiate(snakeBodyPrefab, transform.localPosition, Quaternion.identity);
    //     snakeObj.Add(piece);
    // }

    // void UpdateBody(){
    //     // if the player hasn't eaten an apple this step then move butt to front
    //      if(eatenAppleThisStep == false){
    //         Node butt = snakeNodes[0];
    //         Node newHead = PosToNode(transform.localPosition, graph.graph);
    //         snakeNodes.Remove(butt);
    //         snakeNodes.Add(newHead);
    //      }
    // }

    // void UpdateGraph(){
    //     List<Node> NodesToDelete = new List<Node>();

    //     // deletes all the connects inside the snake on the graph preventing it from generating paths that cross itself
    //     foreach (Node snakeBody in snakeNodes){
    //         if(snakeBody != snakeNodes[snakeNodes.Count - 1]){
    //             foreach (Node neighbor in snakeBody.neighboursList){
    //                 foreach (Node bodyPiece in snakeNodes){
    //                     if(neighbor.position == bodyPiece.position){
    //                     }
    //                     else{
    //                         NodesToDelete.Add(neighbor);
    //                     }
    //                 }
    //             }
    //             foreach(Node delete in NodesToDelete){
    //                 snakeBody.neighboursList.Remove(delete);
    //                 delete.neighboursList.Remove(snakeBody);
    //             }
    //         }
    //     }
    // }

    void DrawConnections(){
        foreach (Node node in graph.graph){
            foreach (Node neighbor in node.neighboursList){
                Debug.DrawLine(node.position, neighbor.position, Color.blue, .1f);
            }
        }
    }

    // void RenderSnake(){
    //     for (int i = 0; i < graph.snakeNodes.Count; i++){
    //         snakeObj[i].transform.position = graph.snakeNodes[i].position;
    //     }
    // }
}