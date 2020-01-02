#!/bin/env ruby

=begin
|      |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15
|-----:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:
| **0**| 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14
|**16**| 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14
|**16**| 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14
|**32**| 14 | 14 | 14 |>40 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14
|**48**| 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14
=end
def gen(name, is_reverse)
    if (is_reverse) 
        printf("### identity, rotation 0 - 63\n\n")
    else
        printf("### identity, rotation 0 - 63\n\n")
    end

    printf("|      |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15\n")
    printf("|-----:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:")

    exponents = []
    64.times do |i|
        if i % 16 == 0
            printf("\n|%s**%d**", i<=9 ? " " : "", i)
        end

        filename = sprintf("%s_%d_%02d.txt", name, is_reverse ? 1 : 0, i)

        has_failed = false
        exponent = 0
        begin
            File.open(filename).each_line do |l|
                has_failed |= /FAIL/.match(l)
                m = /^length=.*\(2\^(\d+) bytes\)/.match(l)
                next unless m
                exponent = m[1]
            end
            exponents += [exponent.to_i]
            printf("|%s%2d ", has_failed ? " " : ">", exponent)
        rescue
            printf("|  -", has_failed ? " " : ">", exponent)
        end
    end
    printf("\n\n")
    exponents_avg = 0
    exponents_min = 0
    exponents_max = 0
    unless exponents.empty?
        exponents_avg = exponents.inject(0.0) { |sum, el| sum + el } / exponents.size
        exponents_min = exponents.min
        exponents_max = exponents.max
    end

    printf("* min: 2^%d\n", exponents_min)
    printf("* max: 2^%d\n", exponents_max)
    printf("* mean: 2^%4.1f\n", exponents_avg)
    printf("\n");

end

printf("## %s\n\n", ARGV[0])
gen(ARGV[0], false)
gen(ARGV[0], true)
