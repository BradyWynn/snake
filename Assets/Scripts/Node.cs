using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node {
    public Vector3 position;
    public int num;
    public List<Node> neighboursList = new List<Node>();
    public int gCost;
    public int hCost; 
    public Node parent;
    // public Node(Vector3 _position, List<Node> _neighboursList){
    //     position = _position;
    //     neighboursList = _neighboursList;
    // }
    public int fCost {
        get {
            return gCost + hCost;
        }
    }
    public void ResetNeighboursList(int i, int sideLength, Node tail, List<Node> graph){
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
}