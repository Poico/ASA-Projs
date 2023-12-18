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
#include <cstring>
using namespace std;

#define NIL 0
#define WHITE 'W'
#define GRAY 'G'
#define BLACK 'B'

void DFSvisitInputGraph(int vertice, stack<pair<int, int>> *st_secondDFS,
                        char *color);
void DFSvisitTransposedGraph(int vertice, int SCC_num, int *SCCs,
                             char *color);
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
  graph_input.resize(vertices + 1);
  graph_transposed.resize(vertices + 1);

  // quem tem a possibilidade de infectar outros, ou seja, read edges
  for (int i = 0; i < edges; i++) {
    // an edge that goes form u to v (u->v)
    int u, v;
    scanf("%d %d", &u, &v);
    graph_input[u].push_back(v);
    graph_transposed[v].push_back(u); // >:D transposed graph
  }

  // vectors for DFSs
  char color[vertices + 1];
  int SCCs[vertices + 1];
  stack<pair<int, int>> st_secondDFS;

  // init vectores that need inits
  for (int i = 1; i <= vertices; i++) {
    color[i] = WHITE;
  }

  // perform first DFS
  for (int u = 1; u <= vertices; u++) {
    if (color[u] == WHITE) {
      DFSvisitInputGraph(u, &st_secondDFS, color);
      // to insert the nodes for the next DFS correctly
    }
  }

  // second DFS to identify SCCs
  int SCC_num = 1;
  resetColors(color);
  while (!st_secondDFS.empty()) {
    pair<int, int> p = st_secondDFS.top();
    int u = p.first;
    st_secondDFS.pop();
    if (color[u] == WHITE) {
      DFSvisitTransposedGraph(u, SCC_num, SCCs, color);
      ++SCC_num;
    }
  }
  
  // init SCCs graph
  graph_sccs.resize(SCC_num);
  // create edges for the graph 
  for (int i = 1; i <= vertices; i++) {
    for (int j = 0; j < (int)graph_input[i].size(); j++) {
      int neighbor = graph_input[i][j];
      if (SCCs[i] != SCCs[neighbor]) {
        graph_sccs[SCCs[i]].push_back(SCCs[neighbor]);
      }
    }
  }
  // calculate distances
  int distances[SCC_num];
  memset(distances, 0, sizeof(distances));
  int maxDistance = 0; // Initialize maxDistance

  for (int u = 1; u < SCC_num; u++) {
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

void DFSvisitInputGraph(int vertice, stack<pair<int, int>> *st_secondDFS,
                        char *color) {
  // we use a stack to replace recursive approach
  // pair of vertice u and vertice where we left off on the DFSvisit of u
  stack<pair<int, int>> st;
  pair<int, int> initial(vertice, -1);
  st.push(initial);
  color[vertice] = GRAY;

  while (!st.empty()) {
    // int u = st.top().first dá seg fault :'(
    // me when segfaulting this balls
    pair<int, int> p = st.top();
    int u = p.first;

    int edges_size = (int)graph_input[u].size();
    
    // visit adjacents, if there's one yet unexplored, we go through it next
    while (st.top().second < edges_size - 1) {
      ++st.top().second;
      if (color[graph_input[u][st.top().second]] == WHITE) {
        color[graph_input[u][st.top().second]] = GRAY;
        st.push(make_pair(graph_input[u][st.top().second], -1));

        break; // after we add it to the stack, we break from here, to look at
               // the added node
      }
    }
    // after i visited everyone, we close this vertice
    if (st.top().second == edges_size-1) {
      color[u] = BLACK;
      st_secondDFS->push(make_pair(u, -1));
      st.pop(); // finished verifying current node, so we take it out
    }
  }
}

void DFSvisitTransposedGraph(int vertice, int SCC_num, int *SCCs,
                             char *color) {
  // pair of vertice u and vertice index where we left off on the DFSvisit of u
  stack<pair<int, int>> st;
  pair<int, int> initial(vertice, -1);
  st.push(initial);
  color[vertice] = GRAY;

  while (!st.empty()) {
    pair<int, int> p = st.top();
    int u = p.first;

    int edges_size = (int)graph_transposed[u].size();

    // visit adjacents, if there's one yet unexplored, we go through it next
    while (st.top().second < edges_size - 1) {
      ++st.top().second;
      if (color[graph_transposed[u][st.top().second]] == WHITE) {
        color[st.top().second] = GRAY;
        st.push(make_pair(graph_transposed[u][st.top().second], -1));

        break; // after we add it to the stack, we break from here, to look at
               // the added node
      }
    }
    // after i visited everyone, we close this vertice
    if (st.top().second == edges_size - 1) {
      color[u] = BLACK;
      SCCs[u] = SCC_num;
      st.pop(); // finished verifying current node, so we take it out
    }
  }
}

void resetColors(char *color) {
  for (int i = 1; i <= vertices; i++) {
    color[i] = WHITE;
  }
}

void printGraph(vector<vector<int>> graph, int vertices){
  for (int i = 1; i <= vertices; i++) {
    int size = (int)graph[i].size();
    for (int j = 0; j < size; ++j)
      printf("%d connects to %d\n", i, graph[i][j]);
  }
  
}