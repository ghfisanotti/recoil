#!/bin/bash
# Build the gnuplot file with all the csv files in the directory
FN="plot.gnuplot"
FIRST=1
printf "plot " > $FN
for i in *.csv
  do
    [ $FIRST != 1 ] && printf ", " >> $FN
    printf "\"%s\" lw 4" "$i" >> $FN
    FIRST=0
  done
printf "\n" >> $FN
#
# invoke gnuplot to graph the csv(s)
#
gnuplot -p setup.gnuplot plot.gnuplot
