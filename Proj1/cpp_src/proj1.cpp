#include <stdio.h>

using namespace std;

int main(){
    int lin,col;
    int cutNumber;
    int line, column,price;
    scanf("%d %d", &lin , &col);
    lin+=1;
    col+=1;
    int** matrix = new int*[lin];
    for (int i = 0; i < lin; ++i) {
        matrix[i] = new int[col];
    }
    scanf("%d", &cutNumber);
    for(int i = 0; i < cutNumber; i++) {
        scanf("%d %d %d", &line, &column, &price);
        if(line < lin && column < col ) {
            matrix[line][column]=price;
        } 

        if (column < lin && line < col) {
            matrix[column][line]=price;
        }
    } 
    int maximo;
    for(int line=1; line < lin; line++){
        for(int column=1;column<col;column++){
            maximo=0;
            for(int k=1;k<=line;k++)
                if (maximo<(matrix[line-k][column] + matrix[line-(line-k)][column]))
                    maximo = (matrix[line-k][column] + matrix[line-(line-k)][column]);
            for(int k=1;k<=column;k++)
                if (maximo<(matrix[line][column-k] + matrix[line][column-(column-k)]))
                    maximo = matrix[line][column-k] + matrix[line][column-(column-k)];
            matrix[line][column]=maximo;
        }
    }
    printf("%d\n",matrix[lin-1][col-1]);
    return 0;
}