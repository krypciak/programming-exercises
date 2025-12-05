#!/bin/julia
using Test

function part1(inp)
    (rangesStr, idsStr) = split(strip(inp), "\n\n")
    ranges = [parse.(Int64, split(x, '-')) for x in split(rangesStr, '\n')]
    ids = parse.(Int64, split(idsStr, '\n'))

    n = max([b for (a, b) in ranges]..., ids...)

    tree = Dict() # zeros(Int, n * 2)
    function query(i)
        sum = 0
        i += n
        while i >= 1
            sum += get(tree, i, 0)
            i >>= 1
        end
        sum
    end
    function addRange(l, r, v)
        l += n
        r += n + 1
        while l < r
            if l & 1 == 1
                tree[l] = get(tree, l, 0) + v
                l += 1
            end
            if r & 1 == 1
                r -= 1
                tree[r] = get(tree, r, 0) + v
            end
            l >>= 1
            r >>= 1
        end
    end

    for (l, r) in ranges
        addRange(l, r, 1)
    end
    fresh = [id for id in ids if query(id) ≥ 1]
    fresh |> length
end

function part2(inp)
    rangesStr = first(split(strip(inp), "\n\n"))
    ranges = [parse.(Int64, split(x, '-')) for x in split(rangesStr, '\n')]
    sort!(ranges)

    at = 0
    sum = 0
    for (l, r) in ranges
        r += 1
        sum += max(0, r - max(l, at))
        at = max(r, at)
    end
    sum
end

@test part1(read("./part1ex.in", String)) == 3
@test part1(read("./part1.in", String)) == 761

@test part2(read("./part1ex.in", String)) == 14
@test part2(read("./part1.in", String)) == 345755049374932

println("all ok")
