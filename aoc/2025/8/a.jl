#!/bin/julia
using Test

dist(a, b) = (a - b) .^ 2 |> sum

function run(inp, topCount, isPart2)
    points = [parse.(Int, split(line, ',')) for line in inp |> strip |> split]

    dists = [(dist(a, b), (i, j)) for (i, a) in enumerate(points) for (j, b) in enumerate(points) if i > j]
    sort!(dists)

    rep = [i for i in 1:length(points)]
    nodeCount = ones(Int, length(points))
    function union(a, b)
        a = find(a)
        b = find(b)
        a == b && return
        if nodeCount[a] > nodeCount[b]
            a, b = b, a
        end
        rep[a] = b
        nodeCount[b] += nodeCount[a]
    end
    function find(a)
        if rep[a] != a
            rep[a] = find(rep[a])
        end
        return rep[a]
    end

    for (i, (dist, (a, b))) in enumerate(dists)
        newCount = union(a, b)

        if !isPart2
            i >= topCount && break
        else
            if newCount == length(points)
                p1 = points[a]
                p2 = points[b]
                return p1[1] * p2[1]
            end
        end

    end
    @assert !isPart2

    circuitSizes = [x for (i, x) in enumerate(nodeCount) if rep[i] == i]
    sort!(circuitSizes, rev=true)
    circuitSizes[1:3] |> prod
end

part1(inp, topCount) = run(inp, topCount, false)
part2(inp) = run(inp, 9999, true)

@test part1(read("./part1ex.in", String), 10) == 40
@test part1(read("./part1.in", String), 1000) == 352584

@test part2(read("./part1ex.in", String)) == 25272
@test part2(read("./part1.in", String)) == 9617397716

println("all ok")
