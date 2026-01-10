import random
import math


def gen(name, n, q, maxV, solve=True):
    arr = []
    for i in range(n):
        arr.append(random.randint(0, maxV))

    queries = []
    for i in range(q):
        t = random.randint(1, 2)
        t = 2
        if t == 2:
            k = random.randint(0, math.floor(math.log2(n)))
            k = 17
            left = random.randint(1, n - (2**k))
            queries.append((t, left, k))
        else:
            i = random.randint(1, n)
            v = random.randint(0, maxV)
            queries.append((t, i, v))

    with open(f"gen/{name}.in", "w") as file:
        file.write(f"{n} {q}\n")
        for v in arr:
            file.write(f"{v} ")
        file.write("\n")

        for a, b, c in queries:
            file.write(f"{a} {b} {c}\n")

    if not solve:
        return
    sol = []
    for t, l, r in queries:
        # print("arr:", arr)
        # print(t, l, r)
        if t == 1:
            l -= 1
            arr[l] = r
            # print(f"set {l} to {r}")
        else:
            k = r
            l -= 1
            # print(f"query from {l} k {k}")
            assert t == 2
            if k == 0:
                sol.append(arr[l])
            else:
                to = l + 2**k
                # print(l, to, to - l, len(arr))
                values = [arr[i] for i in range(l, to)]
                # print(values)
                while len(values) > 1:
                    values = [
                        abs(values[i] - values[i + 1]) for i in range(0, len(values), 2)
                    ]
                    # print(values)

                sol.append(values[0])

    with open(f"gen/{name}.out", "w") as file:
        for v in sol:
            file.write(f"{v}\n")


random.seed(2)
for i in range(10):
    gen(f"{i}", 200000, 200000, int(1e9), False)
    print(f"{i} done")
