#!/bin/julia
using Test

function solve(inp, count) 
    nums = map(x -> parse.(Int128, x), split.(split(strip(inp), "\n"), ""))
    map(nums) do arr
        num = 0
        arri = 1
        for i in 1:count
            (n1, h1) = findmax(arr[arri:end-(count-i)])
            arri += h1
            num += n1 * 10^(count-i)
        end
        num
    end |> sum
end

function part1(inp)
    solve(inp, 2)
end
@test part1(read("./part1ex.in", String)) == 357
@test part1(read("./part1.in", String)) == 17109

function part2(inp)
    solve(inp, 12)
end
@test part2(read("./part1ex.in", String)) == 3121910778619
@test part2(read("./part1.in", String)) == 169347417057382

println("all ok")
