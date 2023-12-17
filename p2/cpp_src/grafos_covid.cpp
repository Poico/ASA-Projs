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
#include <limits>
using namespace std;

#define NIL 0
enum Visited {
    WHITE,
    GRAY,
    BLACK
};

void DFSvisitInputGraph(int vertice, int *time, stack<int> *st_secondDFS, enum Visited *color, int *end_time, int *parent);
void addEdge();
void dfsIterative(int start);
void printGraph(vector<vector<int>> graph);
void printGraphMatrix(vector<vector<int>> graph);

// global vars. to make things easier for the project
int vertices, edges;
vector<vector<int>> graph_input;
vector<vector<int>> graph_transposed;

int main(int argc, char const *argv[]) {
  // read first input
  scanf("%d %d", &vertices, &edges);

  // initialize input and trans graph
  graph_input.resize(vertices + 1);
  graph_transposed.resize(vertices + 1);
  for (int i = 1; i <= vertices; i++) {
    // se vai ser matriz, então basta ser V^2
    graph_input[i].resize(vertices + 1);
    graph_transposed[i].resize(vertices + 1);
  }

  // quem tem a possibilidade de infectar outros, ou seja, read edges
  for (int i = 0; i < edges; i++) {
    addEdge();
  }

  // vectors for DFSs
  enum Visited color[vertices+1];
  int end_time[vertices+1];
  int parent[vertices+1]; 
  int SCC[vertices+1];
  stack<int> st_firstDFS;
  stack<int> st_secondDFS;

  // init vectores that need inits
  for (int i = 1; i <= vertices; i++) {
    color[i] = WHITE;
    parent[i] = NIL;
    end_time[i] = __INT_MAX__;
    // printf("for vertice %d: parent - %d, color - %d\n", i, parent[i], color[i]);
  }

  // // perform DFS from each
  // int time = 1;
  // for (int u = 1; u <= vertices; u++) {
  //   if (color[u] == WHITE){
  //     DFSvisitInputGraph(u, &time, &st_secondDFS, color, end_time, parent); // to insert the nodes for the next DFS correctly
  //   }
  // }
  
  
  
  
  return 0;
}

void DFSvisitInputGraph(int vertice, int *time, stack<int> *st_secondDFS, enum Visited *color, int *end_time, int *parent){
  ++time;
  // we use a stack to replace recursive approach
  stack<int> st;
  st.push(vertice);
  
  while (!st.empty()) {
    int u = st.top(); // u is the start node for the edges 
    st.pop(); // we are now handeling the current vertice
    color[u] = GRAY;
    // visit adjacentes, if there's one yet unexplored, we go through it next
    for (int v = 1; v <= vertices; v++) {
      if (graph_input[u][v] != 0 && color[v] == WHITE){
        parent[v] = u;
        st.push(v);
      }
    }
    
  }
  
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
  bool visited[vertices+1];
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

// debug coisos

// pretty print
void printGraph(vector<vector<int>> graph) {
  for (int u = 1; u <= vertices; u++) {
    for (int v = 1; v <= vertices; v++) {
      if (graph[u][v] != 0)
        printf("%d connects to %d\n", u, v);
    }
  }
}

void printGraphMatrix(vector<vector<int>> graph){
  printf("[");
  for (int u = 1; u <= vertices; u++) {
    for (int v = 1; v <= vertices; v++) {
        if (v == vertices)
          printf("%d", graph[u][v]);
        else
          printf("%d, ", graph[u][v]);
    }
    if (u != vertices)
      printf("\n");
  }
  printf("]\n"); 
}
