#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using std::vector;
using std::queue;
using std::min;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity};
        Edge backward_edge = {to, from, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].capacity += flow;
        edges[id ^ 1].capacity -= flow;
    }
};

int bfs(int from,FlowGraph& graph){
    vector<int> dads(graph.size(),-1);
    vector<int> capacities(graph.size(),1000000000);
    queue<int> q;
    q.push(0);
    dads[0] = -2;
    int n = graph.size();
    while(q.size() && dads[n-1] == -1){
        int dad = q.front();
        q.pop();
        vector<size_t> adj = graph.get_ids(dad);
        for(auto va:adj){
            int to = graph.get_edge(va).to;
            if(dads[to] == -1 && graph.get_edge(va).capacity != 0){
                dads[to] = va;
                capacities[to] = min(capacities[dad],graph.get_edge(va).capacity);
                q.push(to);
            }
        }
    }
    if(dads[n-1] == -1)return 0;
    int ans = capacities[n-1];
    from = n-1;
    while(dads[from] != -2){
        graph.add_flow(dads[from],-ans);
        from = graph.get_edge(dads[from]).from;
    }
    return ans;
}


FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    while(1){
        int add = bfs(0,graph);
        if(add == 0) break;
        flow += add;
    }
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
