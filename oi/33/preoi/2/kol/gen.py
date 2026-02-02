import math

def genZ(n, m, q):
    colors = [(i % m)+1 for i in range(n)]
    queries = [0 for i in range(q)]
    qi = 0
    while qi < q:
        if qi > 0: print("loop!", qi)
        for i in range(1, m+1):
            if qi >= q: break
            for j in range(i+1, m+1):
                if i == j: continue
                if qi >= q: break
                queries[qi] = (i, j)
                qi += 1

    return (n, m, q, colors, queries)

z = 5
n = 100000
m = math.floor(math.sqrt(n))*2
q = 200000
sets = [genZ(n, m, q) for i in range(z)]

with open("gen/0.in", "w") as f:
    f.write(f"{z}\n")
    for n, m, q, colors, queries in sets:
        f.write(f"{n} {m} {q}\n")
        for v in colors:
            f.write(f"{v} ")
        f.write(f"\n")
        for a, b in queries:
            f.write(f"{a} {b}\n")
