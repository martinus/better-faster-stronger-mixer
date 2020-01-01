#!/bin/env ruby

if ARGV.size != 3
    STDERR.puts "usage: practrand_feeder.rb <num_threads: 16> <tlmin: 10> <tlmax: 40> <mixer>"
    exit(1)
end

num_threads = ARGV.shift.to_i
tlmax = ARGV.shift.to_i
mixer = ARGV.shift

cmd_mixer = "./mixer --out=/dev/null -ns -tc=\"practrand_feeder<c_#{mixer}>\""
cmd_pract = "../../practrand/RNG_test stdin64 -tf 2 -tlmin 10 -tlmax #{tlmax}"

# create task queue (threadsave)
tasks = Queue.new
2.times do |bitreverse|
    64.times do |rotation|
        # cmd_envir = "MIXER_REVERSE="{0..1}" MIXER_ROTATION="{00..63}"
        tasks << sprintf("MIXER_REVERSE=%d MIXER_ROTATION=%02d %s | %s >%s_%d_%02d.txt", bitreverse, rotation, cmd_mixer, cmd_pract, mixer, bitreverse, rotation)
    end
end

# push sentinels for each thread
num_threads.times do
    tasks.push nil
end


# Create threads
threads = []
num_threads.times do
    threads << Thread.new do
        loop do
            task = tasks.pop
            break if task == nil
            puts task
            system(task)
        end
    end
end

p [num_threads, tlmax, mixer]

threads.each do |thread|
    thread.join
end
puts "done!"
