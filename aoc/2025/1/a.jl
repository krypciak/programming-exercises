#!/bin/julia
using Test

function part1(inp)
    inp |>
    strip |>
    split |>
    x -> [(l[1] == 'L' ? -1 : 1) * parse(Int128, l[2:end]) for l in x] |>
         x -> (x[1] += 50; x) |>
              cumsum |>
              x -> x .% 100 |>
                   x -> count(n -> n == 0, x)
end
@test part1(read("part1ex.in", String)) == 3
@test part1(read("part1.in", String)) == 1118

function part2(inp)
    nums = inp |>
           strip |>
           split |>
           x -> [(l[1] == 'L' ? -1 : 1) * parse(Int128, l[2:end]) for l in x]

    total = 0
    sum = 50
    for x in nums
        prevsum = sum
        sum += x
        total += abs(sum) ÷ 100
        if sum == 0 || (sum < 0 && prevsum != 0)
            total += 1
        end
        sum %= 100
        if (sum < 0)
            sum += 100
        end
    end
    total
end
@test part2(read("part1ex.in", String)) == 6
@test part2(read("part1.in", String)) == 6289
println("all ok!")
println(part1(read("bigboy.in", String)))
println(part2(read("bigboy.in", String)))
