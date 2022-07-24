using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monte : MonoBehaviour{
    Graph graph = new Graph(31);
    Node apple = new Node();
    List<List<Node>> possiblePaths = new List<List<Node>>();
    private void Start() {
        
    }
    public void Solve(){
        possiblePaths = Astar.FindPath(snakeNodes[snakeNodes.Count - 1], PosToNode(currentApple.transform.localPosition, graph.graph));
    }
}