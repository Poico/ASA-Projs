#include <iostream>
using namespace std;

// translation: the biggest better value
int valor_mais_melhor_bom(int ** matrix, int rows, int columns){ 
    // bottom-up approach
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            int max = 0;
            // cuts on the marble in one dimension
            for (int k = 1; k <= i; k++){
                int current_solution = matrix[k][j] + matrix[i-k][j];
                if (max < current_solution)
                    max = current_solution;
            }
            // cuts on the marble in the other dimension
            for (int k = 1; k <= j; k++){
                int current_solution = matrix[i][k] + matrix[i][j-k];
                if (max < current_solution)
                    max = current_solution;
            }
            matrix[i][j] = max; 
        }   
    }
    return matrix[rows-1][columns-1];
}


int main() {
    
    int rows, columns, n_pieces;
    int **marble;

    // get marble slab
    scanf("%d %d", &rows, &columns);
    scanf("%d", &n_pieces);

    // initialize marble
    rows += 1;             // in order to have a 0xY or Xx0 entries always at zero. 
    columns += 1;
    
    marble = new int*[rows];
    for (int i = 0; i < rows; i++)
        marble[i] = new int[columns];
    
    // get value for a piece of specific size. he's a bit picky
    for (int i = 0; i < n_pieces; i++) {
        int x, y, value;
        scanf("%d %d %d", &x, &y, &value);
        // insert marble piece price/value duplicated because a piece in X,Y = Y,X. it's true. just rotate it. 
        if (x < rows && y < columns)
            marble[x][y] = value;
        if (y < rows && x < columns)
            marble[y][x] = value;   
    }

    //print stuff
    printf("ola\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++)
            printf("%2d ", marble[i][j]);
        printf("\n");
    }

    printf("%d\n", valor_mais_melhor_bom(marble, rows, columns));

    return 0;
}
