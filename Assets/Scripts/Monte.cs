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
    //  List<Node> lastPath = new List<Node>();
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
            // lastPath = path; 
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

            Node temp = new Node();
            locGra.snakeNodes.Add(temp);
            
            GameObject piece = Instantiate(snakeBodyPrefab, transform.localPosition, Quaternion.identity);
            piece.name = locGra.snakeNodes.Count.ToString();
            snakeObj.Add(piece);

            foreach(Node snakeBody in locGra.snakeNodes){
                snakeBody.ResetBothNeighboursList(snakeBody.num, locGra.sideLength, locGra.graph); 
            }


            // for (int i = 0; i < locGra.snakeNodes.Count; i++){
            //     if(locGra.snakeNodes.Count > path.Count){
            //         if(i >= (locGra.snakeNodes.Count - 1) - (path.Count - 1)){
            //             locGra.snakeNodes[i] = path[i - (locGra.snakeNodes.Count - path.Count)];
            //         }
            //         else{
            //             try
            //             {
            //                 locGra.snakeNodes[i] = lastPath[i + (lastPath.Count - (locGra.snakeNodes.Count - path.Count))];
            //             }
            //             catch (System.Exception)
            //             {
            //                 Debug.Log(lastPath.Count + ": lastPath count");
            //                 Debug.Log(i + ": i ");
            //                 Debug.Log(locGra.snakeNodes.Count + ": snakeNodes count");
            //                 Debug.Log(path.Count + ": path count");
            //                 Debug.Break();
            //                 throw;
            //             }

            //         }
            //     }
            //     else{
            //         locGra.snakeNodes[i] = path[i + (path.Count - locGra.snakeNodes.Count)];
            //     }
            // }
            int snakeNodeSize = locGra.snakeNodes.Count;
            int pathSize = path.Count;

            if(snakeNodeSize > pathSize){
                for (int x = 0; x < snakeNodeSize - pathSize; x++){
                    locGra.snakeNodes[x] = locGra.snakeNodes[x + pathSize - 1];
                }
                for (int i = 0; i < pathSize; i++){
                    try{
                        locGra.snakeNodes[i + (snakeNodeSize - pathSize)] = path[i];
                    }
                    catch (System.Exception){
                        Debug.Log(i + ": i");
                        Debug.Log(pathSize + ": pathsize");
                        Debug.Log(snakeNodeSize + ": snakenodeSize");
                        Debug.Break();
                        throw;
                    }
                }
            }
            else{
                for (int i = 0; i < snakeNodeSize; i++){
                   locGra.snakeNodes[i] = path[i + (pathSize - snakeNodeSize)]; 
                }
            }

            // Debug.Log(back.Count);
            // Debug.Log(pathSize + ": pathsize");
            // Debug.Log(snakeNodeSize + ": snakenodeSize");
            
            RenderSnake();
            locGra.SpawnApple();
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