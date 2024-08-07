#include <iostream>
#include <queue>
using namespace std;

const int MAX_V = 100;
class Graph {
 private:
 int num_v;
 int adj[MAX_V][MAX_V];
 public:
 Graph(int vertices) {
 num_v = vertices;
 for(int i = 0; i < num_v; i++) {
 for(int j = 0; j < num_v; j++) {
 adj[i][j] = 0;
 
}
 
}
 
}
 void add_edge(int u, int v) {
 if (u >= 0 && u < num_v && v >= 0 && v < num_v) {
 adj[u][v] = 1;
 adj[v][u] = 1; // Since the graph is undirected
 } else {
 cout << "Invalid vertices!" << endl;
 
}
 
}
 void remove_edge(int u, int v) {
 if (u >= 0 && u < num_v && v >= 0 && v < num_v) {
 adj[u][v] = 0;
 adj[v][u] = 0; // Since the graph is undirected
 } else {
 cout << "Invalid vertices!" << endl;
 
}
 
}
 void bfs(int start) {
 bool vis[MAX_V] = {false};
 queue<int> q;
 vis[start] = true;
 q.push(start);
 while(!q.empty()) {
 int u = q.front();
 q.pop();
 cout << u << " ";
 for(int v = 0; v < num_v; v++) {
 if(adj[u][v] == 1 && !vis[v]) {
 vis[v] = true;
 q.push(v);
 }
 }
 }
 cout << endl;
 }
 void dfs_traversal(int start) {
 bool vis[MAX_V] = {false};
 dfs(start, vis);
 cout << endl;
 }
 void dfs(int v, bool vis[]) {
 vis[v] = true;
 cout << v << " ";
 for(int i = 0; i < num_v; i++) {
 if(adj[v][i] == 1 && !vis[i]) {
 dfs(i, vis);
 }
 }
 }
 void display_matrix() {
 for(int i = 0; i < num_v; i++) {
 for(int j = 0; j < num_v; j++) {
 cout << adj[i][j] << " ";
 }
 cout << endl;
 }
 }
};
int main() {
 int num_v, choice, start, u, v;
 cout << "Enter the number of vertices in the graph (max 100): ";
 cin >> num_v;
 Graph g(num_v);
 do {
 cout << "Menu:" << endl;
 cout << "1. Add edge" << endl;
 cout << "2. Remove edge" << endl;
 cout << "3. Breadth First Search (BFS)" << endl;
 cout << "4. Depth First Search (DFS)" << endl;
 cout << "5. Display adjacency matrix" << endl;
 cout << "6. Exit" << endl;
 cout << "Enter your choice: ";
 cin >> choice;
 switch(choice) {
 case 1:
 cout << "Enter the two vertices to add an edge between (0-" << num_v-1 << "): ";
 cin >> u >> v;
 g.add_edge(u, v);
 break;
 case 2:
 cout << "Enter the two vertices to remove the edge between (0-" << num_v-1 << "): ";
 cin >> u >> v;
 g.remove_edge(u, v);
 break;
 case 3:
 cout << "Enter the starting vertex for BFS (0-" << num_v-1 << "): ";
 cin >> start;
 cout << "BFS Traversal: ";
 g.bfs(start);
 break;
 case 4:
 cout << "Enter the starting vertex for DFS (0-" << num_v-1 << "): ";
 cin >> start;
 cout << "DFS Traversal: ";
 g.dfs_traversal(start);
 break;
 case 5:
 g.display_matrix();
 break;
 case 6:
 cout << "Exiting..." << endl;
 break;
 default:
 cout << "Invalid choice" << endl;
 break;
 }
 } while(choice != 6);
 return 0;
}
