import math
import random


def gen(name):
    random.seed(1)
    minV = int(-1e6)
    maxV = int(1e6)
    n = int(1e6)
    m = int(1e6)

    def pickNum():
        return maxV
        return random.randrange(minV, maxV)

    nums = [pickNum() for _ in range(n)]
    queries = []
    expected = []
    for i in range(m):
        # t = random.randrange(1, 2)
        # left = random.randrange(1, n)
        # right = random.randrange(1, n)
        left = 1
        right = n
        if i == m - 1:
            t = 1
        else:
            t = 2

        if t == 1:
            queries.append((t, left, right))

            summed = sum(nums[left - 1:right])
            expected.append(summed)
        else:
            value = pickNum()
            # for i in range(left - 1, right):
            #     nums[i] += value
            queries.append((t, left, right, value))

    with open(f"{name}.in", "w") as f:
        f.write(f"{n} {m}\n")
        for v in nums:
            f.write(f"{v} ")
        f.write("\n")
        for tup in queries:
            for v in tup:
                f.write(f"{v} ")
            f.write("\n")

    with open(f"{name}.out", "w") as f:
        for v in expected:
            f.write(f"{v}\n")


for i in range(1):
    gen(f"gen/{i}")
