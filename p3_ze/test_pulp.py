from pulp import *

n_vars, n_restr = map(int, input().split())
prob = LpProblem("test", LpMaximize)

objective = {}
for i in range(1, n_vars+1):
    coef = int(input())
    objective[i] = {"coef" :coef}

obj_vars = LpVariable.dicts("x", objective.keys(), 0, cat=LpInteger)

for i in range(1, n_restr+1):
    c1, c2, limit = map(int, input().split())
    prob += lpSum(obj_vars[1]*c1 + obj_vars[2]*c2) <= limit

# print(objective)

# objective function
prob += lpSum([obj_vars[i]*objective[i]["coef"] for i in objective.keys()])

# print(prob)
prob.solve(GLPK(msg=0))
if (prob.status == LpStatusOptimal):
    print(value(prob.objective))