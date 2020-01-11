#!/bin/env gnuplot
reset

# png
set terminal pngcairo size 882,650 enhanced font 'Verdana,10'
set output '../docs/singlecolumn.png'

set style line 12 lc rgb'#808080' lt 0 lw 1
set grid back ls 12

set title font 'Verdana,16' "All 16bit Mumx and Muma mixing Quality"
set xlabel "sorted"
set ylabel "1: all numbers unique, no collisions"

plot "mumx16.dat" using ($1/65536) with lines title "mumx", \
     "muma16.dat" using ($1/65536) with lines title "muma"

