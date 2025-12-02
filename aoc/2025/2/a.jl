#!/bin/julia
using Test

function numsInRec(x, y, isPart2, l=1, seq=0, seen = Set())
    sum = 0
    for i in 0:9
        if i == 0 && l == 1
            continue
        end
        nseq = seq * 10 + i
        num = nseq * 10^l + nseq
        num > y && break

        while num ≤ y
            if num ≥ x && num ∉ seen
                sum += num
                push!(seen, num)
            end
            isPart2 || break
            num *= 10^l
            num += nseq
        end

        if l ≤ 7
            sum += numsInRec(x, y, isPart2, l + 1, nseq, seen)
        end
    end
    sum
end

function numsIn((x, y), isPart2)
    sum = numsInRec(x, y, isPart2)
    # println("$x-$y = $sum")
    sum
end

function run(inp, numsInFunc, isPart2=false)
    rangesStr = split.(split(strip(inp), ','), '-')
    ranges = map(x -> parse.(Int128, x), rangesStr)
    numsInFunc.(ranges, isPart2) |> sum
end

function part1(inp)
    run(inp, numsIn)
end
@test part1(read("./part1ex.in", String)) == 1227775554
@test part1(read("./part1.in", String)) == 37314786486

function part2(inp)
    run(inp, numsIn, true)
end

@test part2(read("./part1ex.in", String)) == 4174379265
@test part2(read("./part1.in", String)) == 47477053982

println("all ok")
