/*
Objectivos:
- 2 DFS para identificar os SCCs 
- Construir o Grafo dos SCCs
- DFS no grafo SCCs para achar ordem topológica
- Árvore com maior profundidade na floresta DFS

flags de compilação:  g++ -std=c++11 -O3 -Wall file.cpp -lm
*/

#include <vector>
#include <stdio.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int vertices, edges;
    // read input
    scanf("%d %d", vertices, edges);
    
    // construct input graph
    vector<vector<int>> graph_input(vertices);
    for (int i = 0; i < edges; i++) {
        
    }
    
    
    return 0;
}
