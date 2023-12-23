from pulp import *

prob = pulp.LpProblem("Exemplo", pulp.LpMaximize)
# Lower bound, upper bound, tipo de variável 
pulp.LpVariable("x1",0,1,pulp.LpInteger) # x1 pertence a {0,1}
x1 = pulp.LpMaximize("x1",0,1,pulp.LpInteger) # x1 pertence a {0,1}
# Sem valores sem upperbound
X2 = pulp.LpMaximize("x2",0,1,cat='Continuous') # x2 pertence a [0,+inf[
# se tiver <= é restrição
prob += pulp.lpSum([2*x1, -x2,-4*x5]) # Função objetivo
 

prob.solve(GLPK(msg=0))

print("Status:", pulp.LpStatus[prob.status])
print("Função objetivo:", pulp.value(prob.objective))
for v in prob.variables():
    print(v.name, "=", v.varValue)
for v in prob.variables():
 print(v.name, "=", value(v))
 
 
