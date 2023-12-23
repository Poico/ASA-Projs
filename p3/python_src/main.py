from pulp import *

n_toys, n_packs, max_toys = map(int, input().split())

listaBrinquedos = [(0,0)]
for _ in range(n_toys):
 listaBrinquedos += [tuple(map(int, input().split()[:2]))]

listaPacotes = []
for _ in range(n_packs):
 listaPacotes += [tuple(map(int, input().split()[:4]))]


print(listaBrinquedos)
print(listaPacotes)
 
prob = LpProblem("FabricaNatal", LpMaximize)

 