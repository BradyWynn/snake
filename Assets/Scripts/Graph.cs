using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Graph {
    public List<Node> graph = new List<Node>();
    public Graph(int sideLength){
        for (int i = 0; i < sideLength*sideLength; i++){
            Node node = new Node();
            graph.Add(node);
        }
        for (int i = 0; i < graph.Count; i++){
            List<Node> neighboursList = new List<Node>();

            if(i + sideLength < sideLength * sideLength){
                neighboursList.Add(graph[i + sideLength] );
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

            int row = (i - (i % sideLength))/sideLength;
            int col = i % sideLength;

            graph[i].position = new Vector3(col, 0, row);
            graph[i].neighboursList = neighboursList;
            graph[i].num = i;
        }      
    }
}