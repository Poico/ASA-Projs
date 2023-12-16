/*
Objectivos:
- 2 DFS para identificar os SCCs
- Construir o Grafo dos SCCs
- DFS no grafo SCCs para achar ordem topológica
- Árvore com maior profundidade na floresta DFS

flags de compilação:  g++ -std=c++11 -O3 -Wall file.cpp -lm
*/

#include <stack>
#include <stdio.h>
#include <vector>
using namespace std;
void addEdge();
void dfsIterative(int start);
void printGraph();
void printGraphMatrix(vector<vector<int>> graph);
int vertices, edges;
vector<vector<int>> graph_input;
vector<vector<int>> graph_transposed;
vector<bool> visited;

int main(int argc, char const *argv[]) {
  // read first input
  scanf("%d %d", &vertices, &edges);

  // initialize input and trans graph
  graph_input.resize(vertices + 1);
  graph_transposed.resize(vertices + 1);
  for (int i = 1; i <= vertices; i++) {
    graph_input[i].resize(edges + 1);
    graph_transposed[i].resize(edges + 1);
  }

  // quem tem a possibilidade de infectar outros, ou seja, read edges
  for (int i = 0; i < edges; i++) {
    addEdge();
  }

  // perform DFS from each unvisited vertex
  // visited.resize(vertices + 1, false);
  // for (int v = 1; v <= vertices; v++) {
  //   if (!visited[v]) {
  //     dfsIterative(v);
  //   }
  // }
  
  printGraphMatrix(graph_input);
  printGraphMatrix(graph_transposed);

  return 0;
}

// pretty print
void printGraph() {
  for (int v = 1; v <= vertices; v++) {
    for (int e = 1; e <= edges; e++) {
      if (graph_input[v][e] != 0)
        printf("%d connects to %d\n", v, e);
    }
  }
}

void printGraphMatrix(vector<vector<int>> graph){
  printf("[");
  for (int v = 1; v <= vertices; v++) {
    for (int e = 1; e <= edges; e++) {
        if (e == edges)
          printf("%d", graph[v][e]);
        else
          printf("%d, ", graph[v][e]);
    }
    if (v != vertices)
      printf("\n");
  }
  printf("]\n"); 
}

void addEdge() {
  // an edge that goes form u to v (u->v)
  int u, v;
  scanf("%d %d", &u, &v);
  graph_input[u][v] = 1;
  graph_transposed[v][u] = 1;
}

void dfsIterative(int start) {
  stack<int> st;
  st.push(start);
  visited[start] = true;

  while (!st.empty()) {
    int current = st.top();
    st.pop();

    // Process the current node
    printf("%d ", current);

    // Visit all the adjacent nodes of the current node
    for (int v = 1; v <= vertices; v++) {
      if (graph_input[current][v] != 0 && !visited[v]) {
        st.push(v);
        visited[v] = true;
      }
    }
  }
}
