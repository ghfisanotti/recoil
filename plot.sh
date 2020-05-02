#!/bin/bash
# Function: Build the plot.gnuplot file with all the csv files in the directory
#           then invoke gnuplot to display the graph
# Author: Gerardo Fisanotti, 1-may-2020
#
FN="plot.gnuplot"
FIRST=1
printf "plot " > $FN
for i in *.csv
  do
    [ $FIRST != 1 ] && printf ", " >> $FN # comma separator before each file
    printf "\"%s\" lw 4" "$i" >> $FN # plot with linewidth 4
    FIRST=0
  done
printf "\n" >> $FN
#
# invoke gnuplot to graph the csv(s)
#
gnuplot -p setup.gnuplot plot.gnuplot
