using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snake : MonoBehaviour{
    public int applesEaten = 0;
    // public Vector3 dir = Vector3.zero;
    public int count = 0;
    public GameObject applePrefab;
    public GameObject snakeBodyPrefab;
    public GameObject currentApple;
    public List<GameObject> snakeObj = new List<GameObject>();
    public List<Node> snakeNodes = new List<Node>();
    public bool eatenAppleThisStep;
    Graph graph = new Graph(31);

    void Start(){
        Extend();
        currentApple = Instantiate(applePrefab, new Vector3(25, 0, 15), Quaternion.identity);
        SpawnApple();
    }

    void Update(){
        eatenAppleThisStep = false;
        RenderSnake();

        if(applesEaten > 1){
            UpdateGraph();
        }
        DrawConnections();

        if(applesEaten > 10){
            int score = graph.Evaluate(currentApple.transform.localPosition, snakeNodes);
            Debug.Log(score);
            Debug.Break();
        }

        // if(Input.GetKey(KeyCode.W))
        //     dir = transform.forward;
        // if(Input.GetKey(KeyCode.S))
        //     dir = -transform.forward;
        // if(Input.GetKey(KeyCode.D))
        //     dir = transform.right;
        // if(Input.GetKey(KeyCode.A)) 
        //     dir = -transform.right;

        List<Node> path = Astar.FindPath(snakeNodes[snakeNodes.Count - 1], PosToNode(currentApple.transform.localPosition));

        if(count % 5 == 0){
            // transform.localPosition = (transform.localPosition + dir);
            transform.localPosition = path[0].position;
            RepairGraph();

            // for(int i = 0; i < snakeObj.Count - 1; i++){ // subtract one from count because top of the list is always going to be head and the head can't hit the head
            //     if(snakeObj[i].transform.localPosition == transform.localPosition){
            //         Debug.Break();
            //         Debug.Log("hit self");
            //     }
            // }
            AppleCheck();
            UpdateBody();
            
            count = 0;
        }
        count++;
    }

    void SpawnApple(){
        float x = Random.Range(0, 30);
        float y = Random.Range(0, 30);
        
        for(int i = 0; i < snakeNodes.Count; i++){
            if(snakeNodes[i].position.x == x && snakeNodes[i].position.z == y){
                SpawnApple();
                return;
            }
        }
        currentApple.transform.localPosition = new Vector3(x, 0, y);
    }

    void AppleCheck(){
        if(transform.localPosition == currentApple.transform.localPosition){
            applesEaten++;
            eatenAppleThisStep = true;
            Extend();
            SpawnApple(); 
        }
    }

    void Extend(){
        Node newNode = PosToNode(transform.localPosition);
        snakeNodes.Add(newNode);
        newNode.isSnake = true;

        GameObject piece = Instantiate(snakeBodyPrefab, transform.localPosition, Quaternion.identity);
        snakeObj.Add(piece);
    }

    void UpdateBody(){
        // if the player hasn't eaten an apple this step then move butt to front
         if(eatenAppleThisStep == false){
            // GameObject butt = snakeObj[0];
            Node butt = snakeNodes[0];
            Node newHead = PosToNode(transform.localPosition);
            // butt.position = transform.localPosition;
            snakeNodes.Remove(butt);
            snakeNodes.Add(newHead);
            // snakeObj.Remove(butt);
            // snakeObj.Add(butt);
         }
    }

    Node PosToNode(Vector3 pos){
        for (int i = 0; i < graph.graph.Count; i++){
            if(graph.graph[i].position == pos){
                return graph.graph[i];
            }
        }
        Debug.Log("You called PosToNode but no Node has that position");
        return null;
    } 

    void UpdateGraph(){
        List<Node> NodesToDelete = new List<Node>();

        // deletes all the connects inside the snake on the graph preventing it from generating paths that cross itself
        foreach (Node snakeBody in snakeNodes){
            if(snakeBody != snakeNodes[snakeNodes.Count - 1]){
                foreach (Node neighbor in snakeBody.neighboursList){
                    foreach (Node bodyPiece in snakeNodes){
                        if(neighbor.position == bodyPiece.position){
                            // Debug.Log("snake neighbor :)");
                        }
                        else{
                            NodesToDelete.Add(neighbor);
                        }
                    }
                }
                foreach(Node delete in NodesToDelete){
                    snakeBody.neighboursList.Remove(delete);
                    delete.neighboursList.Remove(snakeBody);
                }
                // Debug.Log(snakeBody.neighboursList.Count);
            }
        }
    }

    void RepairGraph(){
        // updates all the connections to the tail of the snake
        Node tail = snakeNodes[0];
        int i = tail.num;
        int sideLength = 31;
        tail.neighboursList.Clear();

        tail.ResetBothNeighboursList(i, sideLength, graph.graph);
    }

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