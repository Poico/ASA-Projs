/*
Objectivos:
- 2 DFS para identificar os SCCs
- Construir o Grafo dos SCCs
- DFS no grafo SCCs para achar ordem topológica
- Árvore com maior profundidade na floresta DFS

flags de compilação:  g++ -std=c++11 -O3 -Wall file.cpp -lm
*/

#include <cstring>
#include <limits>
#include <stack>
#include <stdio.h>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

#define NIL 0
#define WHITE 'W'
#define GRAY 'G'
#define BLACK 'B'

void DFSvisitInputGraph(int vertice, stack<int> &st_secondDFS,
                        char *color);
void DFSvisitTransposedGraph(int vertice, int SCC_num, int *SCCs, char *color);
void printGraph(vector<vector<int>> graph, int vertices);

void resetColors(char *color);

// global vars. to make things easier for the project
int vertices, edges;
vector<vector<int>> graph_input;
vector<vector<int>> graph_transposed;
vector<vector<int>> graph_sccs;

int main(int argc, char const *argv[]) {
  // read first input
  scanf("%d %d", &vertices, &edges);

  // initialize input and trans graph
  graph_input.resize(vertices);
  graph_transposed.resize(vertices);

  // quem tem a possibilidade de infectar outros, ou seja, read edges
  for (int i = 0; i < edges; i++) {
    // an edge that goes form u to v (u->v)
    int u, v;
    scanf("%d %d", &u, &v);
    graph_input[u - 1].push_back(v - 1);
    graph_transposed[v - 1].push_back(u - 1); // >:D transposed graph
  }

  // vectors for DFSs
  char* color= new char[vertices];
  int* SCCs = new int[vertices];
  stack<int> st_secondDFS;

  // init vectores that need inits
  for (int i = 0; i < vertices; i++) {
    color[i] = WHITE;
  }

  // perform first DFS
  for (int u = 0; u < vertices; u++) {
    if (color[u] == WHITE) {
      DFSvisitInputGraph(u, st_secondDFS, color);
      // to insert the nodes for the next DFS correctly
    }
  }

  // second DFS to identify SCCs
  int SCC_num = 0;
  resetColors(color);
  while (!st_secondDFS.empty()) {
    int u = st_secondDFS.top();
    st_secondDFS.pop();
    if (color[u] == WHITE) {
      DFSvisitTransposedGraph(u, SCC_num, SCCs, color);
      ++SCC_num;
    }
  }

  // init SCCs graph
  graph_sccs.resize(SCC_num+1);
  // create edges for the graph
  for (int i = 0; i < vertices; i++) {
    for (int j = 0; j < (int)graph_input[i].size(); j++) {
      int neighbor = graph_input[i][j];
      if (SCCs[i] != SCCs[neighbor]) {
        graph_sccs[SCCs[i]].push_back(SCCs[neighbor]);
      }
    }
  }
  // calculate distances
  int* distances = new int[SCC_num](); // Initialize distances array with zeros
  int maxDistance = 0; // Initialize maxDistance

  for (int u = 0; u < SCC_num; u++) {
    int size = (int)graph_sccs[u].size();
    for (int v = 0; v < size; v++) {
      int adjacent = graph_sccs[u][v];
      if (distances[adjacent] < distances[u] + 1) {
        distances[adjacent] = distances[u] + 1;
        if (distances[adjacent] > maxDistance) {
          maxDistance = distances[adjacent]; // Update maxDistance
        }
      }
    }
  }

  printf("%d\n", maxDistance);

  return 0;
}

void DFSvisitInputGraph(int vertice, stack<int> &st_secondDFS,
                        char *color) {
  // we use a stack to replace recursive approach
  // pair of vertice u and vertice where we left off on the DFSvisit of u
  stack<int> st;
  st.push(vertice);
  
  while (!st.empty()) {
    // me when segfaulting this balls
    int u = st.top();

    int edges_size = (int)graph_input[u].size();
    // visit adjacents, if there's one yet unexplored, we go through it next
    if (color[u] == WHITE){
      // currently visiting
      color[u] = GRAY;
      for (int v = 0; v < edges_size; ++v) {
        if (color[graph_input[u][v]] == WHITE) {
          st.push(graph_input[u][v]); 
        }
      }
    } else {
      if (color[u] == GRAY){
        color[u] = BLACK;
        st_secondDFS.push(u);
      }
      st.pop(); // finished verifying current node, so we take it out
    }
  }
}

void DFSvisitTransposedGraph(int vertice, int SCC_num, int *SCCs, char *color) {
  // pair of vertice u and vertice index where we left off on the DFSvisit of u
  stack<int> st;
  st.push(vertice);

  while (!st.empty()) {
    int u = st.top();

    int edges_size = (int)graph_transposed[u].size();

    // visit adjacents, if there's one yet unexplored, we go through it next
    if (color[u] == WHITE){
      color[u] = GRAY;
      for (int v = 0; v < edges_size; ++v) {
        if (color[graph_transposed[u][v]] == WHITE) {
          st.push(graph_transposed[u][v]); 
        }
      }
    } else {
      if (color[u] == GRAY) {
        color[u] = BLACK;
        SCCs[u] = SCC_num;
      }
      st.pop(); // finished verifying current node, so we take it out
    }
  }
}

void resetColors(char *color) {
  for (int i = 0; i < vertices; i++) {
    color[i] = WHITE;
  }
}

void printGraph(vector<vector<int>> graph, int vertices) {
  for (int i = 0; i < vertices; i++) {
    int size = (int)graph[i].size();
    for (int j = 0; j < size; ++j)
      printf("%d connects to %d\n", i, graph[i][j]);
  }
}