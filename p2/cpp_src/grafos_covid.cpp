/*
Objectivos:
- 2 DFS para identificar os SCCs
- Construir o Grafo dos SCCs
- DFS no grafo SCCs para achar ordem topológica
- Árvore com maior profundidade na floresta DFS

flags de compilação:  g++ -std=c++11 -O3 -Wall file.cpp -lm
*/

#include <limits>
#include <stack>
#include <stdio.h>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

#define NIL 0
enum Colors { WHITE, GRAY, BLACK };

void DFSvisitInputGraph(int vertice, int *time,
                        stack<pair<int, int>> *st_secondDFS, enum Colors *color,
                        int *end_time, int *parent);
void addEdge();
int dfsIterative(int start);
void printGraph(vector<vector<int>> graph);
void printGraphMatrix(vector<vector<int>> graph);
void resetColors(enum Colors *color);

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
  enum Colors color[vertices + 1];
  int end_time[vertices + 1];
  int parent[vertices + 1];
  int SCCs[vertices + 1];
  stack<pair<int, int>> st_secondDFS;

  // init vectores that need inits
  for (int i = 1; i <= vertices; i++) {
    color[i] = WHITE;
    parent[i] = NIL;
    end_time[i] = __INT_MAX__;
    // printf("for vertice %d: parent - %d, color - %d\n", i, parent[i],
    // color[i]);
  }

  // perform first DFS
  int time = 0;
  for (int u = 1; u <= vertices; u++) {
    if (color[u] == WHITE) {
      printf("DFS no vertice %d\n", u);
      DFSvisitInputGraph(u, &time, &st_secondDFS, color, end_time, parent);
      // to insert the nodes for the next DFS correctly
    }
  }

  // second DFS to identify SCCs
  int SCC_num = 1;
  resetColors(color);
  while (!st_secondDFS.empty()) {
    pair<int, int> p = st_secondDFS.top();
    int u = p.first;
    if (color[u] == WHITE)
      DFSvisitTransposedGraph(u, SCCs, color);
  }
  


  // for (int i = 1; i <= vertices; i++) {
  //   printf("for vertice %d: parent - %d, tempo de fim - %d\n", i, parent[i], end_time[i]);
  // }
  
  
  // printf("Longest path: %d\n", dfsIterative(1));

  return 0;
}

void DFSvisitInputGraph(int vertice, int *time,
                        stack<pair<int, int>> *st_secondDFS, enum Colors *color,
                        int *end_time, int *parent) {
  // we use a stack to replace recursive approach
  ++(*time);
  // pair of vertice u and vertice where we left off on the DFSvisit of u
  stack<pair<int, int>> st;
  pair<int, int> initial(vertice, 0);
  // initial.first = vertice; initial.second = 0;
  st.push(initial);
  color[vertice] = GRAY;

  while (!st.empty()) {
    // int u = st.top().first dá seg fault :'(
    pair<int, int> p = st.top();
    int u = p.first;

    // visit adjacents, if there's one yet unexplored, we go through it next
    while (st.top().second < vertices) {
      ++st.top().second;
      if (graph_input[u][st.top().second] != 0 &&
          color[st.top().second] == WHITE) {
        color[st.top().second] = GRAY;
        ++(*time);
        parent[st.top().second] = u;
        st.push(make_pair(st.top().second, 0));

        break; // after we add it to the stack, we break from here, to look at
               // the added node
      }
    }
    // after i visited everyone, we close this vertice
    if (st.top().second == vertices) {
      ++(*time);
      color[u] = BLACK;
      end_time[u] = *time;
      printf("fechei o vertice %d com tempo de fim %d e predecessor %d\n", u,
             end_time[u], parent[u]);
      st_secondDFS->push(make_pair(u, 0));
      st.pop(); // finished verifying current node, so we take it out
    }
  }
  printf("acabei de fazer a árvore de %d\n", vertice);
}

void DFSvisitTransposedGraph(int vertice, )

void addEdge() {
  // an edge that goes form u to v (u->v)
  int u, v;
  scanf("%d %d", &u, &v);
  graph_input[u][v] = 1;
  graph_transposed[v][u] = 1;
}

int longestPath = 0;

int dfsIterative(int start) {
  stack<pair<int, int>> st;
  st.push({start, 0});
  bool visited[vertices + 1];
  visited[start] = true;

  while (!st.empty()) {
    int current = st.top().first;
    int pathLength = st.top().second;
    st.pop();

    // Update the longest path if necessary
    longestPath = max(longestPath, pathLength);
    // Visit all the adjacent nodes of the current node
    for (int v = 1; v <= vertices; ++v) {
      for (int v = 1; v <= vertices; ++v) {
        if (graph_input[current][v] != 0 && !visited[v]) {
          st.push({v, pathLength + 1});
          visited[v] = true;
        }
      }
    }
  }
  return longestPath;
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

void printGraphMatrix(vector<vector<int>> graph) {
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

void resetColors(enum Colors *color){
  for (int i = 1; i <= vertices; i++) {
    color[i] = WHITE;
  }
}