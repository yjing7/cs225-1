/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
    map<Vertex, Vertex> vmap;
    setUnexplored(graph);
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    while(!q.empty())
    {
        Vertex v = q.front();
        vector<Vertex> adj = graph.getAdjacent(v);
        q.pop();
        for (int i = 0; i < adj.size(); i++)
        {
            Vertex w = adj[i];
            if (graph.getVertexLabel(w).compare("UNEXPLORED") == 0)
            {
                vmap[w] = v;
                graph.setEdgeLabel(v, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                q.push(w);
            } else if (graph.getEdgeLabel(v, w).compare("UNEXPLORED") == 0)
                graph.setEdgeLabel(v, w, "CROSS");
       }
    }

    int count = 0;
    while (end != start)
    {
        graph.setEdgeLabel(end, vmap[end], "MINPATH");
        end = vmap[end];
        count++;
    }

    return count;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
    setUnexplored(graph);
    //grab a starting vertex
    Vertex start = graph.getStartingVertex();
    //cout<<graph.getVertexLabel(start)<<endl;
    //get all the adjacent vertices
    vector<Vertex> a = graph.getAdjacent(start);
    //use one of the weight as the inital min
    int min_weight = graph.getEdgeWeight(start, a[0]);
    //setup min_v and min_w to keep track of the min edge
    Vertex min_v;
    Vertex min_w;
    
    //BFS
    //declare queue for BFS
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    while(!q.empty())
    {
        Vertex v = q.front();
        vector<Vertex> adj = graph.getAdjacent(v);
        q.pop();
        for (int i = 0; i < adj.size(); i++)
        {
            Vertex w = adj[i];
            if (graph.getVertexLabel(w).compare("UNEXPLORED") == 0)
            {
                graph.setEdgeLabel(v, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                q.push(w);
            } else if (graph.getEdgeLabel(v, w).compare("UNEXPLORED") == 0)
                graph.setEdgeLabel(v, w, "CROSS");
            if(graph.getEdgeWeight(v, w) <= min_weight)
            {
                min_weight = graph.getEdgeWeight(v,w);
                min_v = v;
                min_w = w;
            }
        }
    }

    graph.setEdgeLabel(min_v, min_w, "MIN");

    return min_weight;
}

void GraphTools::setUnexplored(Graph &graph)
{
    Vertex start = graph.getStartingVertex();
    queue<Vertex> q;
    graph.setVertexLabel(start,"UNEXPLORED");
    q.push(start);
    while(!q.empty())
    {
        Vertex v = q.front();
        vector <Vertex> adj = graph.getAdjacent(v);
        q.pop();
        for (int i = 0; i < adj.size(); i++)
        {
            Vertex w = adj[i];
            if (graph.getVertexLabel(w).compare("UNEXPLORED") != 0)
            {
                graph.setEdgeLabel(v,w, "UNEXPLORED");
                graph.setVertexLabel(w, "UNEXPLORED");
                q.push(w);
            } else if (graph.getEdgeLabel(v,w).compare("UNEXPLORED")!= 0)
                graph.setEdgeLabel(v,w,"UNEXPLORED");
        }
    }
}

void GraphTools::BFS(Graph &graph, Vertex v)
{
    queue<Vertex> q;
    graph.setVertexLabel(v, "VISITED");
    q.push(v);
    while(!q.empty())
    {
        q.push(v);
        vector<Vertex> adj = graph.getAdjacent(v);
        for (int i = 0; i < adj.size(); i++)
        {
            Vertex w = adj[i];
            if (graph.getVertexLabel(w) == "UNEXPLORED")
            {
                graph.setEdgeLabel(v, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                q.push(w);
            } else if (graph.getEdgeLabel(v, w) == "UNEXPLORED")
                graph.setEdgeLabel(v, w, "CROSS");
        }
    }
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{

    vector <Edge> edge_list = graph.getEdges();
    vector <Edge>::iterator it;
    sort(edge_list.begin(), edge_list.end(), sort_edge);
    DisjointSets vertices;
    vector <Vertex> vertex_list = graph.getVertices();
    vertices.addelements(vertex_list.size());

    //traverse the list from start
    for (int i = 0; i < edge_list.size(); i++)
    {
        //inspect the current edge. if that edge connects two vertices from different sets, union their sets and mark the edge as part of the MST. otherwise do nothing
        //get vertices from this edge
        Vertex u = edge_list[i].source;
        Vertex v = edge_list[i].dest;

        //see if they are from different sets
        if (vertices.find(u) != vertices.find(v))
        {
            //different sets
            //1. Union 
            vertices.setunion(u,v);
            //2. mark the edge
            graph.setEdgeLabel(u,v,"MST");
        }
    }
}

bool GraphTools::sort_edge (Edge a, Edge b) {
    return (a.weight < b.weight);
}
