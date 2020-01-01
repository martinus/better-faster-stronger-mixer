#!/bin/env ruby

def gen(name, is_reverse)
    printf("%s %s:\n", name, is_reverse ? "reverse" : "identity")
    printf("   |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n")
    printf("---+----------------------------------------------------------------")

    exponents = []
    64.times do |i|
        if i % 16 == 0
            printf("\n%2d |", i)
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
            printf(" %s%2d", has_failed ? " " : ">", exponent)
        rescue
            printf("   -", has_failed ? " " : ">", exponent)
        end
    end
    printf("\n")
    exponents_avg = 0
    exponents_min = 0
    exponents_max = 0
    unless exponents.empty?
        exponents_avg = exponents.inject(0.0) { |sum, el| sum + el } / exponents.size
        exponents_min = exponents.min
        exponents_max = exponents.max
    end
    printf("min: %2d, max: %2d, avg: %4.1f\n\n", exponents_min, exponents_max, exponents_avg)
end

gen(ARGV[0], false)
gen(ARGV[0], true)
