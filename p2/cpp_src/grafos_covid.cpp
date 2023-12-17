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

void DFSvisitInputGraph(int vertice, stack<pair<int, int>> *st_secondDFS,
                        char *color);
void DFSvisitTransposedGraph(int vertice, int SCC_num, int *SCCs,
                             char *color);
int DFSvisitSCCsGraph(vector<vector<bool>> graph_sccs, int vertice,
                      char *color, int SCC_num);
void resetColors(char *color);

// global vars. to make things easier for the project
int vertices, edges;
vector<vector<bool>> graph_input;
vector<vector<bool>> graph_transposed;

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
    // an edge that goes form u to v (u->v)
    int u, v;
    scanf("%d %d", &u, &v);
    graph_input[u][v] = 1;
    graph_transposed[v][u] = 1;
  }

  // vectors for DFSs
  char color[vertices + 1];
  int SCCs[vertices + 1];
  stack<pair<int, int>> st_secondDFS;

  // init vectores that need inits
  for (int i = 1; i <= vertices; i++) {
    color[i] = 'W';
  }

  // perform first DFS
  for (int u = 1; u <= vertices; u++) {
    if (color[u] == 'W') {
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
    if (color[u] == 'W') {
      DFSvisitTransposedGraph(u, SCC_num, SCCs, color);
      ++SCC_num;
    }
  }

  // init SCCs graph
  vector<vector<bool>> graph_sccs;
  graph_sccs.resize(SCC_num + 1);
  for (int i = 1; i <= SCC_num; i++) {
    graph_sccs[i].resize(SCC_num);
  }
  // create edges for the graph
  for (int i = 1; i <= vertices; i++) {
    for (int j = 1; j <= vertices; j++) {
      if (graph_input[i][j] != 0 && graph_sccs[SCCs[i]][SCCs[j]] == 0 &&
          SCCs[i] != SCCs[j])
        graph_sccs[SCCs[i]][SCCs[j]] = 1;
    }
  }

  // final DFS
  resetColors(color);
  int longest = 0;
  int latest = 0;
  for (int u = 1; u <= SCC_num; u++) {
    if (color[u] == 'W') {
      latest = DFSvisitSCCsGraph(graph_sccs, u, color, SCC_num);
      longest = max<int>(longest, latest);
    }
  }

  printf("%d\n", longest);


  return 0;
}

void DFSvisitInputGraph(int vertice, stack<pair<int, int>> *st_secondDFS,
                        char *color) {
  // we use a stack to replace recursive approach
  // pair of vertice u and vertice where we left off on the DFSvisit of u
  stack<pair<int, int>> st;
  pair<int, int> initial(vertice, 0);
  st.push(initial);
  color[vertice] = 'G';

  while (!st.empty()) {
    // int u = st.top().first dá seg fault :'(
    pair<int, int> p = st.top();
    int u = p.first;

    // visit adjacents, if there's one yet unexplored, we go through it next
    while (st.top().second < vertices) {
      ++st.top().second;
      if (graph_input[u][st.top().second] != 0 &&
          color[st.top().second] == 'W') {
        color[st.top().second] = 'G';
        st.push(make_pair(st.top().second, 0));

        break; // after we add it to the stack, we break from here, to look at
               // the added node
      }
    }
    // after i visited everyone, we close this vertice
    if (st.top().second == vertices) {
      color[u] = 'B';
      st_secondDFS->push(make_pair(u, 0));
      st.pop(); // finished verifying current node, so we take it out
    }
  }
}

void DFSvisitTransposedGraph(int vertice, int SCC_num, int *SCCs,
                             char *color) {
  // pair of vertice u and vertice where we left off on the DFSvisit of u
  stack<pair<int, int>> st;
  pair<int, int> initial(vertice, 0);
  st.push(initial);
  color[vertice] = 'G';

  while (!st.empty()) {
    pair<int, int> p = st.top();
    int u = p.first;

    // visit adjacents, if there's one yet unexplored, we go through it next
    while (st.top().second < vertices) {
      ++st.top().second;
      if (graph_transposed[u][st.top().second] != 0 &&
          color[st.top().second] == 'W') {
        color[st.top().second] = 'G';
        st.push(make_pair(st.top().second, 0));

        break; // after we add it to the stack, we break from here, to look at
               // the added node
      }
    }
    // after i visited everyone, we close this vertice
    if (st.top().second == vertices) {
      color[u] = 'B';
      SCCs[u] = SCC_num;
      st.pop(); // finished verifying current node, so we take it out
    }
  }
}



int DFSvisitSCCsGraph(vector<vector<bool>> graph_sccs, int vertice,
                      char *color, int SCC_num) {
  int mais_maior = 0;
  int current_depth = 0;

  // tirar ferramentas da caixa
  stack<pair<int, int>> st;
  pair<int, int> initial(vertice, 0);
  st.push(initial);
  color[vertice] = 'G';

  while (!st.empty()) {
    // get vertice
    pair<int, int> p = st.top();
    int u = p.first;

    // visit adjacents, if there's one yet unexplored, we go through it next
    while (st.top().second < SCC_num) {
      ++st.top().second;
      if (graph_sccs[u][st.top().second] != 0 &&
          color[st.top().second] == 'W') {

        color[st.top().second] = 'G';
        st.push(make_pair(st.top().second, 0));
        ++current_depth;
        mais_maior = max<int>(mais_maior, current_depth);
        break; // after we add it to the stack, we break from here, to look at
               // the added node
      }
    }
    // after i visited everyone, we close this vertice
    if (st.top().second == SCC_num) {
      color[u] = 'B';
      st.pop(); // finished verifying current node, so we take it out
      --current_depth;
    }
  }
  return mais_maior;
}

void resetColors(char *color) {
  for (int i = 1; i <= vertices; i++) {
    color[i] = 'W';
  }
}