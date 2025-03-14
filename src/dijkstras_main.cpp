#include "dijkstras.h"

int main(){
    Graph test_graph;
    file_to_graph("./src/medium.txt", test_graph);
    // for (Edge e : test_graph[3]){cout << e.src << " -> " << e.dst << " : " << e.weight << endl;}
    int src = 3;
    vector<int> prev;
    vector<int> dijkstra_path = dijkstra_shortest_path(test_graph, src, prev);
    int destination = 1;
    vector<int> short_path = extract_shortest_path(dijkstra_path, prev, destination);
    print_path(short_path, short_path.size());
    cout << endl;
    return 0;
}
