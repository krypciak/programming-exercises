#!/bin/julia
using Test

displayGrid(grid) = println.(String.(eachrow(grid |> permutedims)))

END_NODE = (0, 0)

function buildGraph(inp)
    grid = hcat(collect.(split(strip(inp), '\n'))...)
    w, h = size(grid)

    sx, sy = findfirst(==('S'), grid) |> Tuple
    splitters = [findall(==('^'), grid[x, :]) for x in 1:w]
    splittersIndexes = ones(Int, w)

    graph = Dict{Tuple{Int,Int},Vector{Tuple{Int,Int}}}()
    graph[END_NODE] = []

    queue = Vector{Tuple{Int,Int}}()

    function tryEnqueue(ox, oy, x, y, parentNeigh)
        (x < 1 || x > w) && return

        i = searchsortedlast(splitters[x], y) + 1
        if i == length(splitters[x]) + 1
            push!(parentNeigh, END_NODE)
            return
        end
        y = splitters[x][i]

        push!(parentNeigh, (x, y))
        grid[x, y] == '$' && return
        grid[x, y] = '$'
        push!(queue, (x, y))
    end

    tryEnqueue(sx, sy, sx, sy + 1, get!(graph, (sx, sy), []))

    while !isempty(queue)
        ox, oy = pop!(queue)

        neigh = get!(graph, (ox, oy), [])

        tryEnqueue(ox, oy, ox - 1, oy, neigh)
        tryEnqueue(ox, oy, ox + 1, oy, neigh)
    end
    (graph, (sx, sy))
end

function part1(inp)
    (graph, s) = buildGraph(inp)
    length(graph) - 2
end

function topSort(graph, revGraph, s)
    degs = Dict(k => length(v) for (k, v) in collect(revGraph))
    order = [s]
    at = 1
    while at <= length(order)
        v = order[at]
        at += 1
        for u in graph[v]
            if (degs[u] -= 1) == 0
                push!(order, u)
            end
        end
    end
    order
end

function reverseGraph(graph)
    revGraph = Dict()
    for (v, neigh) in graph
        get!(revGraph, v, [])
        for u in neigh
            push!(get!(revGraph, u, []), v)
        end
    end
    return revGraph
end

function part2(inp)
    (graph, s) = buildGraph(inp)

    revGraph = reverseGraph(graph)
    order = topSort(graph, revGraph, s)

    muls = Dict{Tuple{Int,Int},Int}()
    muls[s] = 1
    for v in order[2:end]
        muls[v] = [muls[u] for u in revGraph[v]] |> sum
    end
    muls[END_NODE]
end

@test part1(read("./ex0.in", String)) == 4
@test part1(read("./part1ex.in", String)) == 21
@test part1(read("./part1.in", String)) == 1656

@test part2(read("./ex1.in", String)) == 6
@test part2(read("./part1ex.in", String)) == 40
@test part2(read("./part1.in", String)) == 76624086587804

println("all ok")
