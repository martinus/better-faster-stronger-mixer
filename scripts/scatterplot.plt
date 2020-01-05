#!/bin/env gnuplot
reset

# png
set terminal pngcairo size 882,650 enhanced font 'Verdana,10'
set output '../docs/scatterplot.png'

#set border linewidth 1.5
# Set first two line styles to blue (#0060ad) and red (#dd181f)

unset key

set xlabel "worst PractRand failure length at testlength 2^x. tlmax=40"
set ylabel "million mixing operations per second"
set title font 'Verdana,16' "Mixer speed over worst PractRand 0.95 2^x failure"
set rmargin 8
set tmargin 4

set style line 12 lc rgb'#808080' lt 0 lw 1
set grid back ls 12

set format y "%.0s"

plot '../scripts/results.dat' using 2:1:4:3 with labels left rotate by 32 font "Verdana,8" point pt 7 ps 2 lc rgb variable offset char 0.3,0.1 notitle

