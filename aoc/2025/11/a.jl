#!/bin/julia
using Test

function calcOrder(inp, start)
    lines = split(strip(inp), '\n')
    graph = Dict(line[1:findfirst(':', line)-1] => split(line[findfirst(':', line)+2:end], ' ') for line in lines)
    graph["out"] = []

    revGraph = Dict(k => [] for k in keys(graph))
    deg = Dict(k => 0 for k in keys(graph))
    for (v, arr) in graph
        for u in arr
            push!(revGraph[u], v)
            deg[u] += 1
        end
    end

    queue = [v for (v, c) in deg if c == 0 && v != start]
    while !isempty(queue)
        v = pop!(queue)
        for u in graph[v]
            if (deg[u] -= 1) == 0 && u != start
                push!(queue, u)
            end
        end
    end

    order = [start]
    at = 1
    while at <= length(order)
        v = order[at]
        at += 1
        for u in graph[v]
            if (deg[u] -= 1) == 0
                push!(order, u)
            end
        end
    end

    (graph, revGraph, order)
end

function findWayCount(graph, revGraph, order, start, out)
    muls = Dict(k => 0 for k in keys(graph))
    muls[start] = 1
    for v in order[findfirst(==(start), order)+1:end]
        muls[v] = [muls[u] for u in revGraph[v]] |> sum
    end
    muls[out]
end

function part1(inp)
    (graph, revGraph, order) = calcOrder(inp, "you")

    findWayCount(graph, revGraph, order, "you", "out")
end

function part2(inp)
    (graph, revGraph, order) = calcOrder(inp, "svr")

    svrToFft = findWayCount(graph, revGraph, order, "svr", "fft")
    fftToDac = findWayCount(graph, revGraph, order, "fft", "dac")
    dacToOut = findWayCount(graph, revGraph, order, "dac", "out")
    branch1 = svrToFft * fftToDac * dacToOut

    svrToDac = findWayCount(graph, revGraph, order, "svr", "dac")
    dacToFft = findWayCount(graph, revGraph, order, "dac", "fft")
    fftToOut = findWayCount(graph, revGraph, order, "fft", "out")
    branch2 = svrToDac * dacToFft * fftToOut

    branch1 + branch2
end

@test part1(read("./part1ex.in", String)) == 5
@test part1(read("./part1.in", String)) == 782

@test part2(read("./part2ex.in", String)) == 2
@test part2(read("./part1.in", String)) == 401398751986160

println("all ok")
