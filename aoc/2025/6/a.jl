#!/bin/julia
using Test

function part1(inp)
    inp = strip(inp)
    lineCount = count('\n', inp) + 1
    matrix = reshape(split(inp), :, lineCount)
    sums = [(x[end] == "+" ? sum : prod)(parse.(Int128, x[1:end-1])) for x in eachrow(matrix)]
    sums |> sum
end

function part2(inp)
    lines = split(strip(inp), '\n')
    maxlen = maximum(length(line) for line in lines)

    operators = [(i, x) for (i, x) in enumerate(lines[end]) if !isspace(x)]
    push!(operators, (maxlen + 2, '+'))

    [
        (operator == '+' ? sum : prod)([
            [lines[y][x] for y in 1:length(lines)-1 if lines[y][x] != ' '] |> join |> x -> parse(Int, x)
            for x in at:operators[i+1][1]-2
        ])
        for (i, (at, operator)) in enumerate(operators[1:end-1])
    ] |> sum
end

@test part1(read("./part1ex.in", String)) == 4277556
@test part1(read("./part1.in", String)) == 6299564383938

@test part2(read("./part1ex.in", String)) == 3263827
@test part2(read("./part1.in", String)) == 11950004808442

println("all ok")
