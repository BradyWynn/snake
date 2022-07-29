using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monte : MonoBehaviour{
    Graph graph = new Graph(31);
    // public List<List<Node>> possiblePaths = new List<List<Node>>();
    public Graph locGra;
    public List<GameObject> snakeObj = new List<GameObject>();
     public int count = 0;
     public GameObject snakeBodyPrefab;
     List<Node> path = new List<Node>();
     List<Node> lastPath = new List<Node>();
    private void Start() {
        locGra = graph;
        graph.SpawnApple();
        Node currentLoc = graph.PosToNode(transform.localPosition);
        graph.Extend(currentLoc);
        GameObject piece = Instantiate(snakeBodyPrefab, transform.localPosition, Quaternion.identity);
        snakeObj.Add(piece);
        // Solve();
        // Debug.Log(possiblePaths.Count);
        // foreach(List<Node> path in possiblePaths){
        //     string output = "";
        //     foreach(Node node in path){
        //         output = output + node.position;
        //     }
        //     Debug.Log(output);
        // }
        // Solve(graph);
    }
    public void Update(){
        
        if(count % 100 == 0){
            // this function should take in a board state with an apple and play the game randomly until it ends and returns a score 
            // while(locGra.snakeNodes.Count < 4){ // while there are valid moves available 
                List<Node> NodesToDelete = new List<Node>();

                // deletes all the connects inside the snake on the graph preventing it from generating paths that cross itself
                foreach (Node snakeBody in locGra.snakeNodes){
                    if(snakeBody != locGra.snakeNodes[locGra.snakeNodes.Count - 1]){
                        foreach (Node neighbor in snakeBody.neighboursList){
                            foreach (Node bodyPiece in locGra.snakeNodes){
                                if(neighbor.position == bodyPiece.position){
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
                    }
                }
                DrawConnections(); 

                path = Astar.FindPath(locGra.snakeNodes[locGra.snakeNodes.Count - 1], locGra.apple);
                if(path == null){
                    Debug.Break();
                }
                // string output = "";
                // foreach(Node node in path){
                //     output = output + node.position;
                // }
                // Debug.Log(output);
                // return 2;

                // for (int i = locGra.snakeNodes.Count - 1; i > 0; i--){
                //     Debug.Log(i);
                //     locGra.snakeNodes[i] = path[path.Count - (locGra.snakeNodes.Count - i)];
                // }

                // locGra.Extend(path[0]);
                Node temp = new Node();
                locGra.snakeNodes.Add(temp);
                
                GameObject piece = Instantiate(snakeBodyPrefab, transform.localPosition, Quaternion.identity);
                snakeObj.Add(piece);

                foreach(Node snakeBody in locGra.snakeNodes){
                    snakeBody.ResetBothNeighboursList(snakeBody.num, locGra.sideLength, locGra.graph); 
                }

                // for (int i = 0; i < path.Count; i++){ // loop through every single element in path 
                //     if(i < locGra.snakeNodes.Count){ // only proceed if its less than the number of nodes
                //         locGra.snakeNodes[locGra.snakeNodes.Count -  i - 1] = path[path.Count - i - 1];
                //     }
                // }
                // for (int i = 0; i < locGra.snakeNodes.Count; i++){
                //     if(locGra.snakeNodes.Count - i < path.Count){
                //         locGra.snakeNodes[i] = lastPath[i];
                //     }
                // }

                for (int i = locGra.snakeNodes.Count - 1; i >= 0; i--){
                    if(i > locGra.snakeNodes.Count - 1  - path.Count - 1){
                       locGra.snakeNodes[i] = path[path.Count - 1 - (locGra.snakeNodes.Count - 1 - i)]; 
                    }
                    else{
                        locGra.snakeNodes[i] = lastPath[lastPath.Count - 1 - (locGra.snakeNodes.Count - 1 - i)];
                    }
                }

                locGra.SpawnApple();
                
                Debug.Log(path.Count);
                Debug.Log(lastPath.Count);
                RenderSnake();
                lastPath = path; 
        }
        count++;
    }

    void OnDrawGizmos(){
        // Draw a semitransparent blue cube at the transforms position
        foreach(Node snakeBody in locGra.snakeNodes){
            if(snakeBody == locGra.snakeNodes[locGra.snakeNodes.Count - 1]){
                Gizmos.DrawCube(snakeBody.position, new Vector3(1.1f, 1.1f, 1.1f));
            }
        }
    }
    void DrawConnections(){
        foreach (Node node in locGra.graph){
            foreach (Node neighbor in node.neighboursList){
                Debug.DrawLine(node.position, neighbor.position, Color.blue, 1);
            }
        }
    }
    void RenderSnake(){
        for (int i = 0; i < locGra.snakeNodes.Count; i++){
            snakeObj[i].transform.position = locGra.snakeNodes[i].position;
        }
    }
}