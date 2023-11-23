# código teste para o proj1 de asa
from queue import PriorityQueue

import copy

def mostra_matriz(matriz : list) -> str: 
    
    out = "["
    for i in range(len(matriz)):
        out += str(matriz[i]) + "\n "
    return out.rstrip() + "]"


def valor_mais_macho(matriz : list) -> int: 
    
    #TODO: add variable for the len <- reduce time calculating
    # 3x1 = 2
    # 1x1 = 3
    # soma do coiso mais o max
    for line in range(1,len(matriz)):
        for column in range(1,len(matriz[line])):
            # max de 1 até n peças
            #minus_inf = -math.inf
            lst = []
            # get value calculated before for each possible cut (either in X or Y)
            for k in range(1,line+1):
                #print(f"line:{line} column:{column} k:{k}", end="\n")
                #print(matriz[line-k][column], slabs_values[line][column], end="\n")
                lst.append(matriz[line-k][column] + matriz[line-(line-k)][column])
                #lst.append(matriz[line-k][column] + matriz[k-line][column])
                #lst.append(matriz[line-k][column] + slabs_values[line][column])
                
            for k in range(1, column+1):
                #print(f"line:{line} column:{column} k:{k}", end="\n")
                #print(matriz[line][column-k], slabs_values[line][column], end="\n")
                lst.append(matriz[line][column-k] + matriz[line][column-(column-k)])
                #lst.append(matriz[line][column-k] + slabs_values[line][column])
            print(lst)
            matriz[line][column] = max(lst)

    return matriz[len(matriz)-1][len(matriz[0])-1]

def main():
    """
    função que tem código para ser executado
    """

    # ler as primeiras 2 linhas para ter as dimensões
    rows, columns = map(int, input().split()) # ler input e dizer logo que é int
    
    # matriz com valores terá rows linhas e columns colunas
    matriz = []
    # por tudo a zeros
    for i in range(rows+1):
        matriz.append([])
        for _ in range(columns+1):
            matriz[i].append(0)
    
    
    
    slabs_n = int(input())

    for _ in range(slabs_n):
        x, y, value = map(int, input().split()) # x e y são tamanhos e value é valor da peça x
        matriz[x][y] = value
        try:
            matriz[y][x] = value
        except IndexError:
            pass


    # algoritmo para calcular valor máximo
    
    #print(mostra_matriz(slabs_values))
    
    print(valor_mais_macho(matriz))
    #1x1 3
    
    #2x1 2

    #print(mostra_matriz(matriz), end="\n\n")


if __name__ == "__main__":
    main()
