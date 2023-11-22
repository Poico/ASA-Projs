# código teste para o proj1 de asa
from queue import PriorityQueue
import math

def mostra_matriz(matriz : list) -> str: 
    
    out = "["
    for i in range(len(matriz)):
        out += str(matriz[i]) + "\n "
    return out.rstrip() + "]"


def valor_mais_macho(matriz : list, slabs : dict) -> int: 
    
    res = 0
    #TODO: add variable for the len <- reduce time calculating
    
    for line in range(1,len(matriz)):
        for column in range(1,len(matriz[line])):
            # max de 1 até n peças
            #   peça  preço
            prioq = PriorityQueue() # para ir buscar o valor máximo em O(1)
            # valores que estão imediatamente ao lado
            prioq.put(matriz[line-1][column])
            prioq.put(matriz[line][column-1])
            minus_inf = -math.inf
            
            for slab, value in slabs.items():
                x, y = slab # coordenadas da peça
                print(f"line {line}, column {column}: ", end="")
                print(slab, line - x, column - y)
                

    return res

def main():
    """
    função que tem código para ser executado
    """

    # ler as primeiras 2 linhas para ter as dimensões
    rows, columns = map(int, input().split()) # ler input e dizer logo que é int
    slabs_size = int(input())

    slabs = dict()
    for _ in range(slabs_size):
        x, y, value = map(int, input().split()) # x e y são tamanhos e value é valor da peça x
        slabs[(x, y)] = value
    
    print(slabs)

    # matriz com valores terá rows linhas e columns colunas
    matriz = []

    # por tudo a zeros
    for i in range(rows+1):
        matriz.append([])
        for _ in range(columns+1):
            matriz[i].append(0)
    
    # algoritmo para calcular valor máximo
    print(mostra_matriz(matriz))
    valor_mais_macho(matriz, slabs)



if __name__ == "__main__":
    main()
