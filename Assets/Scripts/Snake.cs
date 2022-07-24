using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snake : MonoBehaviour{
    public int applesEaten = 0;
    // public Vector3 dir = Vector3.zero;
    public int count = 0;
    public GameObject applePrefab;
    public GameObject snakeBodyPrefab;
    public Node appleNode;
    public GameObject appleObj;
    public List<GameObject> snakeObj = new List<GameObject>();
    // public List<Node> snakeNodes = new List<Node>();
    public bool eatenAppleThisStep;
    // Graph graph = new Graph(31);

    void Start(){
        Extend();
        appleObj = Instantiate(applePrefab, new Vector3(25, 0, 15), Quaternion.identity);
        appleNode = PosToNode(new Vector3(25, 0, 15), graph.graph);
        SpawnApple();
    }

    void Update(){
        // eatenAppleThisStep = false;
        // RenderSnake();

        // if(applesEaten > 1){
        //     UpdateGraph();
        // }
        // DrawConnections();

        // for (int i = 0; i < 899; i++){
        //     if(applesEaten > -1){
        //         float score = graph.Evaluate(appleNode.position, snakeNodes);
        //         // Debug.Log(score);
        //     }
        // }

        Debug.Log("done");
        Debug.Break();

        // if(Input.GetKey(KeyCode.W))
        //     dir = transform.forward;
        // if(Input.GetKey(KeyCode.S))
        //     dir = -transform.forward;
        // if(Input.GetKey(KeyCode.D))
        //     dir = transform.right;
        // if(Input.GetKey(KeyCode.A)) 
        //     dir = -transform.right;

        // List<Node> path = Astar.FindPath(snakeNodes[snakeNodes.Count - 1], PosToNode(currentApple.transform.localPosition, graph.graph));

        // if(count % 5 == 0){
        //     // transform.localPosition = (transform.localPosition + dir);
        //     transform.localPosition = path[0].position;
        //     RepairGraph();

        //     // for(int i = 0; i < snakeObj.Count - 1; i++){ // subtract one from count because top of the list is always going to be head and the head can't hit the head
        //     //     if(snakeObj[i].transform.localPosition == transform.localPosition){
        //     //         Debug.Break();
        //     //         Debug.Log("hit self");
        //     //     }
        //     // }
        //     AppleCheck();
        //     UpdateBody();
            
        //     count = 0;
        // }
        // count++;
    }

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
                Debug.DrawLine(node.position, neighbor.position, Color.blue, .2f);
            }
        }
    }

    void RenderSnake(){
        for (int i = 0; i < snakeNodes.Count; i++){
            snakeObj[i].transform.position = snakeNodes[i].position;
        }
    }
}