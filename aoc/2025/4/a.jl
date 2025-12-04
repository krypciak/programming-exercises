#!/bin/julia
using Test

function solve(inp, isPart2)
    gridRaw = split.(split(strip(inp), '\n'), "")
    w = length(gridRaw[1]) + 2
    h = length(gridRaw) + 2
    grid = fill('.', h, w)
    for y in 1:h-2
        for x in 1:w-2
            grid[y+1, x+1] = first(gridRaw[y][x])
        end
    end

    neighbours = Dict()
    nCount = Dict()
    for (x, y) in [(x, y) for x in 2:w-1 for y in 2:h-1 if grid[y, x] == '@']
        neighbourCords = [(x + x1, y + y1) for x1 in -1:1 for y1 in -1:1 if x1 != 0 || y1 != 0]
        neighbours[(x, y)] = [(nx, ny) for (nx, ny) in neighbourCords if grid[ny, nx] != '.']
        nCount[(x, y)] = length(neighbours[(x, y)])
    end

    queue = [i for (i, x) in neighbours if length(x) < 4]
    removed = Set(queue)
    if isPart2
        while !isempty(queue)
            v = popfirst!(queue)

            for j in neighbours[v]
                nCount[j] -= 1
                if j ∉ removed && nCount[j] < 4
                    push!(queue, j)
                    push!(removed, j)
                end
            end
        end
    end

    removed |> length
end

function part1(inp)
    return solve(inp, false)
end

function part2(inp)
    return solve(inp, true)
end

@test part1(read("./part1ex.in", String)) == 13
@test part1(read("./part1.in", String)) == 1356

@test part2(read("./part1ex.in", String)) == 43
@test part2(read("./part1.in", String)) == 8713

println("all ok")
