using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node {
    public Vector3 position;
    public int num;
    public List<Node> neighboursList = new List<Node>();
    public int gCost;
    public int hCost; 
    public bool isSnake;
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
    public void ResetMyNeighboursList(int i, int sideLength, List<Node> graph){
        if(i + sideLength < sideLength * sideLength){
            neighboursList.Add(graph[i + sideLength]);
        }
        if(i - sideLength > 0){
            neighboursList.Add(graph[i - sideLength]);
        }
        if(i + 1 < sideLength * sideLength && i % sideLength != sideLength - 1){
            neighboursList.Add(graph[i + 1]);
        }
        if(i - 1 > 0 && i % sideLength != 0){
            neighboursList.Add(graph[i - 1]);
        }
    }

    public void ResetBothNeighboursList(int i, int sideLength, List<Node> graph){
        if(i + sideLength < sideLength * sideLength){
            // adjMat[i, i + sideLength] = true;
            neighboursList.Add(graph[i + sideLength]);
            graph[i + sideLength].neighboursList.Add(graph[i]);
        }
        if(i - sideLength > 0){
            // adjMat[i, i - sideLength] = true;
            neighboursList.Add(graph[i - sideLength]);
            graph[i - sideLength].neighboursList.Add(graph[i]);
        }
        if(i + 1 < sideLength * sideLength && i % sideLength != sideLength - 1){
            // adjMat[i, i + 1] = true;
            neighboursList.Add(graph[i + 1]);
            graph[i + 1].neighboursList.Add(graph[i]);
        }
        if(i - 1 > 0 && i % sideLength != 0){
            // adjMat[i, i - 1] = true;
            neighboursList.Add(graph[i - 1]);
            graph[i - 1].neighboursList.Add(graph[i]);
        }
    }
}