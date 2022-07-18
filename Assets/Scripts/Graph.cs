using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Graph {
    public List<Node> graph = new List<Node>();
    public Graph(int sideLength){
        for (int i = 0; i < sideLength*sideLength; i++){
            Node node = new Node();
            graph.Add(node);
            node.num = i;
        }
        foreach (Node node in graph){
            node.ResetMyNeighboursList(node.num, sideLength, graph);

            int row = (node.num - (node.num % sideLength))/sideLength;
            int col = node.num % sideLength;

            graph[node.num].position = new Vector3(col, 0, row);
            // graph[i].neighboursList = neighboursList;
            graph[node.num].num = node.num;
        }      
    }

    public int Evaluate(Vector3 applePos, List<Node> snakeNodes){
        // int travesability; 
        // for (int i = 0; i < 10; i++){
        //     float x = Random.Range(0, 30);
        //     float y = Random.Range(0, 30);
            
        //     for(int w = 0; w < snakeNodes.Count; w++){
        //         if(snakeNodes[i].position.x != x && snakeNodes[i].position.z != y){
        //             Snake.UpdateGraph();
        //         }
        //     }
        // }
        return 0;
    }
}