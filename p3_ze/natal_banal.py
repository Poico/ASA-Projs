from pulp import *

# constants
PROFIT = "profit"
LIMIT = "limit"
CONTENT = "content"
RESTRICTION = "restrictions"

# letsa go. uahoo. itsa me, mario
n_toys, n_packs, max_toys = map(int, input().split())
prob = LpProblem("NatalBanal", LpMaximize)

# get toys data 
toys_info = {}
for i in range(n_toys):
    profit, limit = map(int, input().split())
    toys_info[i] = {PROFIT: profit, LIMIT: limit, RESTRICTION: []}

toy_vars = LpVariable.dicts("toy", toys_info, 0, cat=LpInteger)

for toy in toy_vars:
    toys_info[toy][RESTRICTION] += [toy_vars[toy]]

# now get packs data
packs_info = {}
for i in range(n_packs):
    toy1, toy2, toy3, profit = map(int, input().split())
    packs_info[i] = {CONTENT: (toy1-1, toy2-1, toy3-1), PROFIT: profit}

pack_vars = LpVariable.dicts("pack", packs_info, 0, cat=LpInteger)

# add pack_vars to toy restrictions
for pack in pack_vars:
    # always O(1) because CONTENT of a pack is always 3 elements, a constant
    for toy in packs_info[pack][CONTENT]: 
        toys_info[toy][RESTRICTION] += [pack_vars[pack]]

# restrictions
for toy in toy_vars:
    prob += lpSum(toys_info[toy][RESTRICTION]) <= toys_info[toy][LIMIT]

# for toy in toy_vars:
#     conjunto = [toy_vars[toy]]
#     for pack in pack_vars:
#         if toy in packs_info[pack][CONTENT]:
#             conjunto.append(pack_vars[pack])
#     prob += lpSum(conjunto) <= toys_info[toy][LIMIT]

# final restriction
prob += lpSum([toy_vars[toy] for toy in toy_vars]) + lpSum([3*pack_vars[pack] for pack in pack_vars]) <= max_toys

# Objective function
prob += lpSum([toy_vars[toy]*toys_info[toy][PROFIT] for toy in toy_vars]) + \
        lpSum(pack_vars[i]*packs_info[i][PROFIT] for i in pack_vars)

# print(prob)
# the solution
prob.solve(GLPK(msg=0))
if (prob.status == LpStatusOptimal):
    print(value(prob.objective))
else:
    print("0")

# for v in prob.variables():
#     print(v.name, "=", v.varValue)