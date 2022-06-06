#ifndef DA2_PROJETO_GRAPH_H
#define DA2_PROJETO_GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <climits>
#include <set>
#include "maxHeap.h"
#include <stack>

using namespace std;

class Graph {

    /**
     * Graph's edge. It will connects two different nodes, that is, two different locals. In other words, it represents a journey.
     */
    struct Edge {
        /**
         * Boolean flag that checks if an edge is available, that is, if it has capacity to carry more flow.
         */
        bool available;
        /**
         * Destiny's node.
         */
        int dest;
        /**
         * Edge's capacity. It is the maximum number of people a vehicle can carry, in this context.
         */
        int capacity;
        /**
         * Edge's flow. It is the maximum number of people a vehicle is actually carrying, in this context.
         */
        int flow;
        /**
         * Boolean flag that checks if a edge has been already reversed. It will be used in the residual graph.
         */
        bool is_reversed;

        /**
        * Duration of the trip until that local.
        */
        int duration;
    };

    /**
     * Graph's node. It will represent a certain local.
     */
    struct Node {
        /**
         * Group of edge's that the node is connected.
         */
        vector<Edge> adj;
        /**
         *
         */
        int mincap;
        /**
         * Node that precedes the current one.
         */
        int pred;

        /**
         * Boolean flag that checks if a node was already visited or not. Its value will be modified (or not) in the BFS algorithm.
         */
        bool visited;

        int es;

        int lf;

        int ft;

        int degree;
    };

    /**
     * Number of nodes (locals).
     */
    int n;
    /**
     * Graph's group of nodes.
     */
    vector<Node> nodes;

public:

    /**
     * Constructor of a graph. it will initializes the number of locals, and its group of nodes as well.
     * @param nodes Number of the nodes.
     */
    explicit Graph(int nodes): n(nodes), nodes(nodes+1) {};

    /**
     * This method will add an edge (or journey) to the graph, so that we can traverse it later while looking for a path.
     * Initially, this edge is available.
     * @param src Initial node.
     * @param dest Destination node of the edge.
     * @param capacity Capacity of the vehicle on that journey.
     * @param flow Number of people that is being carried in that moment.
     * @param is_reversed Checks is it was already reversed or not (true if so, false otherwise).
     * @param dur Duration associated to the journey.
     */
    void addEdge(int src, int dest, int capacity, int flow, bool is_reversed, int dur){
        if (src<1 || src>n || dest<1 || dest>n) return;
        nodes[src].adj.push_back({ true, dest, capacity, flow, is_reversed, dur});
    };

    /**
     * This method adds a reversed edge to the graph. Initially, this edge is not available; however, it can be while a path is being constructed.
     * @param src Initial node.
     * @param dest Destination node of the edge.
     * @param capacity Capacity of the vehicle on that journey.
     * @param flow Number of people that is being carried in that moment.
     * @param is_reversed Checks is it was already reversed or not (true if so, false otherwise).
     * @param duration Duration associated to the journey.
     */
    void addRevEdge(int src, int dest, int capacity, int flow, bool is_reversed, int duration){
        if (src<1 || src>n || dest<1 || dest>n) return;
        nodes[src].adj.push_back({ false, dest, capacity, flow, is_reversed, duration});
    };

    /**
     * This method will create the corresponding reversed edges, by invoking addRevEdge method for each existing edge that hasn't been reversed yet.
     */
    void addReverseEdges() {
        for(int node = 0; node <= n; node++) {
            for(auto edge: nodes[node].adj) {
                if(!edge.is_reversed)
                    addRevEdge(edge.dest, node, 0, 0, true, edge.duration);
            }
        }
    }


    /**
     * This method returns the Maximum flow allowed in a path
     * @param path path discovered by the BFS algorithm.
     * @return Maximum flow value.
     */
    int getMaxFlow(vector<int> path);

    /**
     * @return The group of existent locals (nodes).
     */
    vector<Node> getNodes() {return this->nodes;}

    /**
     * This method returns the graph's size.
     * @return Graph's size, that is, number of nodes.
     */
    int getSize() const {return this->n;}

    /**
     * This is the BFS algorithm. It traverses all the graph by its levels while there is available edges.
     * @param v First node to begin the search.
     * @return Returns true if the last node is visited, otherwise it returns false.
     */
    bool bfs(int v);

    /**
     * This method uses the BFS algorithm and stores the path found. Then it calculates its size.
     * @param a initial node of the path.
     * @param b final path node.
     * @return the path size, that is, number of locals that a path contains.
     */
    int bfs_path1_2(int a, int b);

    /**
     * This method displays the path that contains the maximum capacity on the console.
     * This value is conditioned to the value of the edge with the lowest capacity.
     * @param s Initial path node.
     * @param t Final path node.
     */
    void maximumCapacityPath(int s, int t);

    /**
     * This method is similar to the maximumCapacityPath, but instead of using the maximum capacity path,
     * it will use the intermediate ones. It will also displays the maximum transhipment needed.
     * @param s Initial path node.
     * @param t Final path node.
     */
    void maximumCapacityPath1_2(int s, int t);

    /**
     * This method will use the Edmonds-Karp algorithm, in order to displays the
     * maximum flow allowed by the graph. It will use the BFS algorithm in order to
     * find the paths available and it will augment all the edges in each iteration.
     * Consequently, it will make some edges unavailable, since they can no longer support more flow.
     * Finally, it displays on the console the value of the maximum flow.
     */
    void edmondsKarp();
    /**
     * This method is similar to edmondsKarp; however, in case the path found does not
     * support the input flow, it will search for a path that does so.
     * @param size Size of the group (its dimension).
     * @return The path's maximum flow value
     */
    int edmondsKarp2(int size);

    /**
     * This method will use the BFS algorithm in order to find a path that goes from node a to node b.
     * @param a Initial path node.
     * @param b Final path node.
     * @return Path found.
     */
    vector<int> bfs_path(int a, int b);

    /**
     * This method displays tha path found on the console.
     * @param path Path to be displayed.
     */
    void static printPath(vector<int>& path);

    /**
     * This method calculates the minimum time that a group will get back together in destiny.
     * This is associated to the Critical Path Problem.
     */
    int criticalPath();

    /**
     * This method calculates the maximum time that the elements wait, supposing that they start at the same time in the same place.
     * It also displays the locals of where those elements wait that time.
     * @param duration Maximum wait duration.
     */
    void maxTimeWait(int duration);
};

#endif //DA2_PROJETO_GRAPH_H
