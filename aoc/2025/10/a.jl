#!/bin/julia
using Test
using JuMP
using GLPK

struct Constraint
    value::Int
    vars::Vector{Int}
end

function varToString(v::Int)
    return v + 'a'
end

function Base.show(io::IO, x::Constraint)
    print(io, "$(x.value) = $(join([varToString(v) for v in x.vars], " + "))")
end

function part1(inp)
    lines = strip.(split(strip(inp), '\n'))
    res = 0
    for line in lines
        lights = [c == '.' ? 0 : 1 for c in line[2:findfirst(']', line)-1]]
        buttons = [parse.(Int, split(str[2:end-1], ',')) for str in split(strip(line[findfirst(']', line)+1:findfirst('{', line)-1]), ' ')]

        canTurnOn = [Int[] for i in 1:length(lights)]
        for (i, button) in enumerate(buttons)
            for bi in button
                push!(canTurnOn[bi+1], i - 1)
            end
        end

        constraints = [Constraint(lights[i], canTurnOn[i]) for i in 1:length(lights)]

        function doesSatisfy(c::Constraint, values::Int64)
            return sum((values >> v) & 1 for v in c.vars) % 2 == c.value
        end

        function doesSatisfyAll(arr::Vector{Constraint}, values::Int64)
            return all(x -> doesSatisfy(x, values), arr)
        end


        maxIte = (2^length(buttons)) - 1
        minRes = typemax(Int)
        for v in 1:maxIte
            if doesSatisfyAll(constraints, v)
                minRes = min(minRes, count_ones(v))
            end
        end
        @assert minRes != typemax(Int)
        res += minRes
    end
    res
end

function part2Jump(inp)
    lines = strip.(split(strip(inp), '\n'))
    res = 0
    for (li, line) in enumerate(lines)
        buttons = [parse.(Int, split(str[2:end-1], ',')) for str in split(strip(line[findfirst(']', line)+1:findfirst('{', line)-1]), ' ')]
        jolReq = parse.(Int, split(line[findfirst('{', line)+1:end-1], ','))

        canInc = [Int[] for i in 1:length(jolReq)]
        for (i, button) in enumerate(buttons)
            for bi in button
                push!(canInc[bi+1], i)
            end
        end

        constraints = [Constraint(jolReq[i], canInc[i]) for i in 1:length(jolReq)]
        sort!(constraints, lt=(a, b) -> length(a.vars) < length(b.vars))

        num_vars = length(buttons)
        model = Model(GLPK.Optimizer)
        @variable(model, x[1:num_vars] >= 0, Int)
        for c in constraints
            @constraint(model, sum(x[i] for i in c.vars) == c.value)
        end

        @objective(model, Min, sum(x))
        optimize!(model)

        minClicks = sum(Int(value(x[i])) for i in 1:num_vars)

        res += minClicks
    end

    res
end


@test part1(read("./part1ex.in", String)) == 7
@test part1(read("./part1.in", String)) == 390

@test part2Jump(read("./part1ex.in", String)) == 33
@test part2Jump(read("./part1.in", String)) == 14677

println("all ok")
