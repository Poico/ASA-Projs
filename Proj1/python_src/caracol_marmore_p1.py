# código teste para o proj1 de asa
from queue import PriorityQueue
import math
import copy

def mostra_matriz(matriz : list) -> str: 
    
    out = "["
    for i in range(len(matriz)):
        out += str(matriz[i]) + "\n "
    return out.rstrip() + "]"


def valor_mais_macho(matriz : list, slabs : list) -> int: 
    
    res = 0
    #TODO: add variable for the len <- reduce time calculating
    
    for line in range(1,len(matriz)):
        for column in range(1,len(matriz[line])):
            # max de 1 até n peças
            #   peça  preço
            minus_inf = -math.inf
            lst = []
            # for k in range(1,line):


                

    return res

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
    
    slabs_values = copy.deepcopy(matriz)
    
    slabs_n = int(input())

    for _ in range(slabs_n):
        x, y, value = map(int, input().split()) # x e y são tamanhos e value é valor da peça x
        slabs_values[x][y] = value
    


    # algoritmo para calcular valor máximo
    print(mostra_matriz(matriz), end="\n\n")
    print(mostra_matriz(slabs_values))
    valor_mais_macho(matriz, slabs_values)



if __name__ == "__main__":
    main()
