#!/bin/env ruby

printf("%s:\n", ARGV[0])
printf("   |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n")
printf("---+----------------------------------------------------------------")
64.times do |i|
    if i % 16 == 0
        printf("\n%2d |", i)
    end

    filename = sprintf("%s_%02d.txt", ARGV[0], i)

    has_failed = false
    exponent = 0
    begin
        File.open(filename).each_line do |l|
            has_failed |= /FAIL/.match(l)
            m = /^length=.*\(2\^(\d+) bytes\)/.match(l)
            next unless m
            exponent = m[1]
        end
        printf(" %s%2d", has_failed ? " " : ">", exponent)
    rescue
        printf("   -", has_failed ? " " : ">", exponent)
    end
end
printf("\n")
