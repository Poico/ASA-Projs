from pulp import *

# constants
PROFIT = "profit"
LIMIT = "limit"
CONTENT = "content"

# lets a go
n_toys, n_packs, max_toys = map(int, input().split())
prob = LpProblem("NatalBanal", LpMaximize)

# fetch and init individual toys 
toys_info = {}
for i in range(n_toys):
    profit, limit = map(int, input().split())
    toys_info[i] = {PROFIT: profit, LIMIT: limit}

toy_vars = LpVariable.dicts("toy", toys_info, 0, cat=LpInteger)
for toy in toy_vars:
    prob += toy_vars[toy] <= toys_info[toy][LIMIT]

# now get packs data
packs_info = {}
for i in range(n_packs):
    toy1, toy2, toy3, profit = map(int, input().split())
    packs_info[i] = {CONTENT: (toy1-1, toy2-1, toy3-1), PROFIT: profit}

pack_vars = LpVariable.dicts("pack", packs_info, 0, cat=LpInteger)

for pack in pack_vars:
    prob += pack_vars[pack] + lpSum([toy_vars[toy] for toy in packs_info[pack][CONTENT]])\
         <= min([toys_info[toy][LIMIT] for toy in packs_info[pack][CONTENT]])

# final restriction
prob += lpSum([toy_vars[toy] for toy in toy_vars]) + lpSum([3*pack_vars[i] for i in pack_vars]) <= max_toys

# Objective function
prob += lpSum([toy_vars[toy]*toys_info[toy][PROFIT] for toy in toy_vars]) + \
        lpSum(pack_vars[i]*packs_info[i][PROFIT] for i in pack_vars)

# print(prob)
# the solution
prob.solve(GLPK(msg=0))
if (prob.status == LpStatusOptimal):
    print(value(prob.objective))
