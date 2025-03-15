#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int graph_size = G.size();
    vector<int> distance(graph_size, INF);
    vector<bool> visits(graph_size, 0);
    previous.assign(graph_size, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priQue;
    distance[source] = 0;
    priQue.push({0, source});
    while (!priQue.empty()){
        auto [curDis, cur] = priQue.top();
        priQue.pop();

        if (!visits[cur]){
            visits[cur] = 1;

            for (const Edge & e : G[cur]){
                // cout << e.src << " -> " << e.dst << " : " << e.weight << endl;
                int adjacent_vertex = e.dst;
                int wgt = e.weight;
                if (!visits[adjacent_vertex] && distance[cur] + wgt < distance[adjacent_vertex]){
                    distance[adjacent_vertex] = distance[cur] + wgt;
                    previous[adjacent_vertex] = cur;
                    priQue.push({distance[adjacent_vertex], adjacent_vertex});
                }
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int> & distance, const vector<int> & previous, int destination){
    if (destination < 0 || distance[destination] == INF || destination >= distance.size()) return {};
    vector<int> return_path;
    for (int src = destination; src != -1 ;src = previous[src]){
        return_path.push_back(src);
    }
    vector<int> new_path;
    for (int back_index = return_path.size() - 1; back_index >= 0; back_index--){
        new_path.push_back(return_path[back_index]);
    }
    return new_path;
}

void print_path(const vector<int> & v, int total){
    for(int i = 0; i < v.size(); ++i){cout << v[i] << " ";}
    cout << endl << "Total cost is " << total << endl;
}
