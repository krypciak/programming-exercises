#!/bin/julia
using Test

function part1(inp)
    corners = [parse.(Int, split(line, ',')) for line in split(strip(inp), '\n')]
    w = maximum([x for (x, y) in corners])
    h = maximum([y for (x, y) in corners])

    operatorMin(ope) = (ope == >) ? typemin(Int) : typemax(Int)

    function findEgdeCorners(xOpe, yOpe)
        mx = operatorMin(xOpe)
        my = operatorMin(yOpe)
        pc = []
        for (x, y) in corners
            if (x == mx || xOpe(x, mx)) && (y == my || yOpe(y, my))
                mx, my = x, y
                pc = [(x, y) for (x, y) in pc if !xOpe(x, mx) && !yOpe(y, my)]
                push!(pc, (x, y))
            elseif xOpe(x, mx) || yOpe(y, my)
                push!(pc, (x, y))
            end
        end
        pc
    end
    nwPc = findEgdeCorners(<, <)
    nePc = findEgdeCorners(>, <)
    swPc = findEgdeCorners(<, >)
    sePc = findEgdeCorners(>, >)

    rectArea(a, b) = prod(abs.(a .- b) .+ 1)

    max(
        maximum(rectArea(a, b) for a in nwPc for b in sePc),
        maximum(rectArea(a, b) for a in nePc for b in swPc)
    )
end

function part2(inp)
    cornersOrig = [parse.(Int, split(line, ',')) for line in split(strip(inp), '\n')]
    xValues = [x for (x, y) in cornersOrig] |> unique |> sort
    yValues = [y for (x, y) in cornersOrig] |> unique |> sort

    # edge case possible since i is not i*2,
    # but puzzle input doesn't seem to have this edge case
    xValueToIndex = Dict(x => i + 1 for (i, x) in enumerate(xValues))
    yValueToIndex = Dict(y => i + 1 for (i, y) in enumerate(yValues))

    xIndexToValue = vcat(0, xValues)
    yIndexToValue = vcat(0, yValues)

    distX(x1, x2) = abs(xIndexToValue[x1] - xIndexToValue[x2])
    distY(y1, y2) = abs(yIndexToValue[y1] - yIndexToValue[y2])

    corners = [(xValueToIndex[x], yValueToIndex[y]) for (x, y) in cornersOrig]

    w = maximum(x for (x, y) in corners) + 1
    h = maximum(y for (x, y) in corners) + 1

    grid = fill('.', w, h)
    for (i, (x1, y1)) in enumerate(corners)
        (x2, y2) = corners[i == length(corners) ? 1 : i + 1]
        if y1 == y2
            for x in x1:sign(x2 - x1):x2
                grid[x, y1] = '#'
            end
        else
            @assert x1 == x2
            for y in y1:sign(y2 - y1):y2
                grid[x1, y] = '#'
            end
        end
    end


    center = round.(Int, (
        sum(x for (x, y) in corners),
        sum(y for (x, y) in corners)
    ) ./ length(corners))

    # fill
    toVisit = [center]
    while !isempty(toVisit)
        (x, y) = pop!(toVisit)

        function visit(x, y)
            if grid[x, y] == '.'
                grid[x, y] = 'X'
                push!(toVisit, (x, y))
            end

        end

        for y1 in [y - 1, y + 1]
            visit(x, y1)
        end
        for x1 in [x - 1, x + 1]
            visit(x1, y)
        end
    end

    ps = zeros(Int, w + 1, h + 1)
    for (x, y) in [(x, y) for x in 1:w for y in 1:h]
        ps[x+1, y+1] = (grid[x, y] != '.' ? 1 : 0) + ps[x+1, y] + ps[x, y+1] - ps[x, y]
    end
    function prefixSumQuery((x1, y1), (x2, y2))
        (mx, my) = (min(x1, x2), min(y1, y2))
        (Mx, My) = (max(x1, x2), max(y1, y2)) .+ 1
        return ps[Mx, My] - ps[Mx, my] - ps[mx, My] + ps[mx, my]
    end


    maxArea = 0
    for (i, (x1, y1)) in enumerate(corners)
        for (x2, y2) in corners[i+1:end]
            coveredArea = prefixSumQuery((x1, y1), (x2, y2))
            fullArea = (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1)
            coveredArea != fullArea && continue

            area = (distX(x1, x2) + 1) * (distY(y1, y2) + 1)
            maxArea = max(maxArea, area)
        end
    end
    maxArea
end

@test part1(read("./part1ex.in", String)) == 50
@test part1(read("./part1.in", String)) == 4738108384

@test part2(read("./part1ex.in", String)) == 24
@test part2(read("./part1.in", String)) == 1513792010


println("all ok")
