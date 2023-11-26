def mostra_matriz(matriz : list) -> str: 
    
    out = "["
    for i in range(len(matriz)):
        out += str(matriz[i]) + "\n "
    return out.rstrip() + "]"


def valor_mais_macho(matriz : list) -> int: 
    #TODO: add variable for the len <- reduce time calculating
    for line in range(1,len(matriz)):
        for column in range(1,len(matriz[line])):
            lst = []
            for k in range(1,line+1):
                lst.append(matriz[line-k][column] + matriz[line-(line-k)][column])
            for k in range(1, column+1):
                lst.append(matriz[line][column-k] + matriz[line][column-(column-k)])
            matriz[line][column] = max(lst)
    return matriz[len(matriz)-1][len(matriz[0])-1]

def main():
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
        try:
            matriz[x][y] = value
        except IndexError:
            pass
        try:
            matriz[y][x] = value
        except IndexError:
            pass
    print(valor_mais_macho(matriz))


if __name__ == "__main__":
    main()
