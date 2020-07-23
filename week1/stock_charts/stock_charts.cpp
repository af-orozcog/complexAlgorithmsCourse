#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
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


class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  int MinCharts(const vector<vector<int>>& stock_data) {
    // Replace this incorrect greedy algorithm with an
    // algorithm that correctly finds the minimum number
    // of charts on which we can put all the stock data
    // without intersections of graphs on one chart.
    int vertex_count = (int)stock_data.size()*2+2;
    FlowGraph graph(vertex_count);
    for(int i = 1; i <= (int)stock_data.size();++i)
        graph.add_edge(0,i,1);
    for(int i = 1; i <= (int)stock_data.size();++i)
        graph.add_edge(i+(int)stock_data.size(),(int)stock_data.size()*2+1,1);
    for(int i = 0; i < (int)stock_data.size();++i){
        for(int j = 0; j < (int)stock_data.size();++j){
            if(compare(stock_data[i],stock_data[j]))
                graph.add_edge(i+1,j+1+(int)stock_data.size(),1);
        }
    }
    int important = max_flow(graph,0,vertex_count-1);
    return (int)stock_data.size()-important;
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] >= stock2[i])
        return false;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
