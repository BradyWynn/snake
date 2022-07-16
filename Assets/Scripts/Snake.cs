using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snake : MonoBehaviour{
    public int graphSize;
    public float speed;
    public int applesEaten = 0;
    public Vector3 dir = Vector3.zero;
    public int count = 0;
    public GameObject applePrefab;
    public GameObject snakeBodyPrefab;
    public GameObject currentApple;
    public List<GameObject> snakeObj = new List<GameObject>();
    public bool eatenAppleThisStep;
    Graph graph = new Graph(31);
    Astar algo = new Astar();

    void Start(){
        Extend();
        currentApple = Instantiate(applePrefab, new Vector3(25, 0, 15), Quaternion.identity);
        SpawnApple();
    }

    void Update(){
        eatenAppleThisStep = false;

        if(applesEaten > 0){
            UpdateGraph();
        }
        // DrawConnections();

        // for (int i = 0; i < snakeObj.Count; i++){
        //     Node bodyNode = PosToNode(snakeObj[i].transform.localPosition);
        //     for (int w = 0; w < bodyNode.neighboursList.Count; w++){
        //         for (int x = 0; x < snakeObj.Count; x++){
        //             if(bodyNode.neighboursList[w].position == snakeObj[x].transform.localPosition){
        //                 continue;
        //             }
        //             else{ 
        //                 bodyNode.neighboursList.Remove(bodyNode.neighboursList[w]);
        //                 // bodyNode.neighboursList[w].neighboursList.Remove(bodyNode);
        //             }
        //         }
        //     }
        // }

        // if(Input.GetKey(KeyCode.W))
        //     dir = transform.forward;
        // if(Input.GetKey(KeyCode.S))
        //     dir = -transform.forward;
        // if(Input.GetKey(KeyCode.D))
        //     dir = transform.right;
        // if(Input.GetKey(KeyCode.A)) 
        //     dir = -transform.right;

        List<Node> path = algo.FindPath(PosToNode(transform.localPosition), PosToNode(currentApple.transform.localPosition));

        if(count % 5 == 0){
            // transform.localPosition = (transform.localPosition + dir);
            transform.localPosition = path[0].position;
            RepairGraph();

            for(int i = 0; i < snakeObj.Count - 1; i++){ // subtract one from count because top of the list is always going to be head and the head can't hit the head
                if(snakeObj[i].transform.localPosition == transform.localPosition){
                    Debug.Break();
                    Debug.Log("hit self");
                }
            }
            AppleCheck();
            UpdateBody();
            
            count = 0;
        }
        count++;
    }

    void SpawnApple(){
        float x = Random.Range(0, 30);
        float y = Random.Range(0, 30);
        
        for(int i = 0; i < snakeObj.Count; i++){
            if(snakeObj[i].transform.localPosition.x == x && snakeObj[i].transform.localPosition.z == y){
                SpawnApple();
                return;
            }
        }
        currentApple.transform.localPosition = new Vector3(x, 0, y);
    }

    void AmongUsAppleSpawn(){
        if(applesEaten == 0){
            currentApple.transform.localPosition = new Vector3(22, 0, 20);
        }
        if(applesEaten == 1){
            currentApple.transform.localPosition = new Vector3(13, 0, 20);
        }
        if(applesEaten == 2){
            currentApple.transform.localPosition = new Vector3(13, 0, 15);
        }
        if(applesEaten == 3){
            currentApple.transform.localPosition = new Vector3(24, 0, 15);
        }
        if(applesEaten == 4){
            currentApple.transform.localPosition = new Vector3(24, 0, 5);
        }
        if(applesEaten == 5){
            currentApple.transform.localPosition = new Vector3(22, 0, 4);
        }
        if(applesEaten == 6){
            currentApple.transform.localPosition = new Vector3(20, 0, 4);
        }
        if(applesEaten == 7){
            currentApple.transform.localPosition = new Vector3(17, 0, 10);
        }
        if(applesEaten == 8){
            currentApple.transform.localPosition = new Vector3(17, 0, 5);
        }
        if(applesEaten == 9){
            currentApple.transform.localPosition = new Vector3(12, 0, 4);
        }
        if(applesEaten == 10){
            currentApple.transform.localPosition = new Vector3(12, 0, 11);
        }
        if(applesEaten == 11){
            currentApple.transform.localPosition = new Vector3(8, 0, 13);
        }
        if(applesEaten == 12){
            currentApple.transform.localPosition = new Vector3(9, 0, 20);
        }
        if(applesEaten == 13){
            currentApple.transform.localPosition = new Vector3(11, 0, 22);
        }
        if(applesEaten == 14){
            currentApple.transform.localPosition = new Vector3(14, 0, 25);
        }
        if(applesEaten == 15){
            currentApple.transform.localPosition = new Vector3(22, 0, 25);
        }
        if(applesEaten == 16){
            currentApple.transform.localPosition = new Vector3(24, 0, 23);
        }
        if(applesEaten == 17){
            currentApple.transform.localPosition = new Vector3(25, 0, 21);
        }
        if(applesEaten == 18){
            currentApple.transform.localPosition = new Vector3(26, 0, 18);
        }
        if(applesEaten == 19){
            currentApple.transform.localPosition = new Vector3(25, 0, 16);
        }

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
        GameObject snakebody = Instantiate(snakeBodyPrefab, transform.localPosition, Quaternion.identity);
        snakeObj.Add(snakebody);
    }

    void UpdateBody(){
        // if the player hasn't eaten an apple this step then move butt to front
         if(eatenAppleThisStep == false){
            GameObject butt = snakeObj[0];
            butt.transform.localPosition = transform.localPosition;
            snakeObj.Remove(butt);
            snakeObj.Add(butt);
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

        // for (int i = 1; i < snakeObj.Count; i++){
        //     Node bodyNode = PosToNode(snakeObj[i].transform.localPosition);
        //     for (int w = 0; w < bodyNode.neighboursList.Count; w++){
        //         for (int x = 0; x < snakeObj.Count; x++){
        //             if(bodyNode.neighboursList[w].position == snakeObj[x].transform.localPosition){ // if the neighbor node is a snake body then continue
        //                 continue;
        //             }
        //             else if( x != 0){
        //                 NodesToDelete.Add(bodyNode.neighboursList[w]);
        //                 // bodyNode.neighboursList.Remove(bodyNode.neighboursList[w]);
        //                 // bodyNode.neighboursList[w].neighboursList.Remove(bodyNode);
        //             }
        //         }
        //     }
        // }

        foreach (GameObject snakeBody in snakeObj){
            if(snakeBody != snakeObj[snakeObj.Count - 1]){
                Node bodyNode = PosToNode(snakeBody.transform.localPosition);
                foreach (Node neighbor in bodyNode.neighboursList){
                    foreach (GameObject bodyPiece in snakeObj){
                        if(neighbor.position == bodyPiece.transform.localPosition){
                            // Debug.Log("snake neighbor :)");
                        }
                        else{
                            NodesToDelete.Add(neighbor);
                        }
                    }
                }
                foreach(Node delete in NodesToDelete){
                    bodyNode.neighboursList.Remove(delete);
                    delete.neighboursList.Remove(bodyNode);
                }
                // Debug.Log(bodyNode.neighboursList.Count);
            }
        }
    }

    void RepairGraph(){
        Node tail = PosToNode(snakeObj[0].transform.localPosition);
        int i = tail.num;
        int sideLength = 31;
        tail.neighboursList.Clear();

        if(i + sideLength < sideLength * sideLength){
            // adjMat[i, i + sideLength] = true;
            tail.neighboursList.Add(graph.graph[i + sideLength]);
            graph.graph[i + sideLength].neighboursList.Add(tail);
        }
        if(i - sideLength > 0){
            // adjMat[i, i - sideLength] = true;
            tail.neighboursList.Add(graph.graph[i - sideLength]);
            graph.graph[i - sideLength].neighboursList.Add(tail);
        }
        if(i + 1 < sideLength * sideLength && i % sideLength != sideLength - 1){
            // adjMat[i, i + 1] = true;
            tail.neighboursList.Add(graph.graph[i + 1]);
            graph.graph[i + 1].neighboursList.Add(tail);
        }
        if(i - 1 > 0 && i % sideLength != 0){
            // adjMat[i, i - 1] = true;
            tail.neighboursList.Add(graph.graph[i - 1]);
            graph.graph[i - 1].neighboursList.Add(tail);
        }
    }

    void DrawConnections(){
        foreach (Node node in graph.graph){
            foreach (Node neighbor in node.neighboursList){
                Debug.DrawLine(node.position, neighbor.position, Color.blue, .2f);
            }
        }
    }
}