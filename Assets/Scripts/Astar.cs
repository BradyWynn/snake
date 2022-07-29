using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Astar{
    // much of the code below is adapted from the sudo code
    // presented in this video https://www.youtube.com/watch?v=mZfyt03LDH4
    // GraphTwo graph = new GraphTwo(9);
    public static List<Node> FindPath(Node start, Node end){
        // List<List<Node>> pathList = new List<List<Node>>();
        List<Node> open = new List<Node>();
        List<Node> closed = new List<Node>();
        open.Add(start);

        while(open.Count > 0){
            Node current = open[0];
            for (int i = 0; i < open.Count; i++){
                if(open[i].fCost < current.fCost || open[i].fCost == current.fCost && open[i].hCost < current.hCost){
                    current = open[i];
                }
            }
            open.Remove(current);
            closed.Add(current);

            // check if at end
            if(current == end){
                List<Node> path = Backtrack(start, end);
                return path;
            }

            // if(current == end){
            //     Backtrack(start, end);
            //     // List<Node> path = Backtrack(start, end);
            //     // pathList.Add(path);
            //     // current = start;

            //     // if(pathList.Count >= 1){
            //     //     return pathList;
            //     // }
            // }

            foreach (Node neighbor in current.neighboursList){
                if (closed.Contains(neighbor)){
                    continue;
                }

                int newMove = current.gCost + GetDistanceOctile(current, neighbor);
                if(newMove < neighbor.gCost || !open.Contains(neighbor)){
                    neighbor.gCost = newMove;
                    neighbor.hCost = GetDistanceOctile(neighbor, end);
                    neighbor.parent = current;

                    if(!open.Contains(neighbor)){
                        open.Add(neighbor);
                    }
                }
            }
        }
        Debug.Log("FindPath exited without a valid path");
        Debug.Log(end.position);
        return null;
    }

    static List<Node> Backtrack(Node _start, Node _end){
        List<Node> path = new List<Node>();
        Node _current = _end;

        while(_current != _start){
            path.Add(_current);
            _current = _current.parent;
        }
        path.Reverse();
        // for (int i = 0; i < path.Count; i++){
        //     if(i < path.Count - 1){
        //         Debug.DrawLine(path[i].position, path[i + 1].position, Color.red, 1);
        //     }
        // }
        return path;
    }

    static int GetDistanceManhattan(Node A, Node B){
        int x = Mathf.Abs((int)B.position.x - (int)A.position.x);
        int y = Mathf.Abs((int)B.position.z - (int)A.position.z);
        return x + y;
    } 

    static int GetDistanceEuclidean(Node A, Node B){
        Vector3 posOne = A.position;
        Vector3 posTwo = B.position;
        return (int)Vector3.Distance(posOne, posTwo);
    }

    static int GetDistanceOctile(Node A, Node B){
        int x = Mathf.Abs((int)B.position.x - (int)A.position.x);
        int y = Mathf.Abs((int)B.position.z - (int)A.position.z);

        if(x > y){
            return (int)(14 * y) + 10 * (x - y);
        }
        return (int)(14 * y) + 10 * (y - x);
    }
    
}