#!/bin/bash
#A batch script used to collect timing data for the Hungarian Algorithm routine

for k in {20..25..1}
  do
  echo $k
  for i in {9..1..-1}
     do
     j1=$(awk "BEGIN {print $i * 10**-$k}")
     j2=$(awk "BEGIN {print $i / 2 * 10**-$k}")
     echo $j
  
     echo "obsfile CH4_YT10to10_296K_2300-3400_E-25.inp" >> inputfile-$k-$i
     echo "calcfile CH4_YT10to10_296K_2300-3400_E-25_rand.inp" >> inputfile-$k-$i
     echo "calcIthresh" $j2 >> inputfile-$k-$i
     echo "obsIthresh" $j1 >> inputfile-$k-$i
     echo "obsrange 2400 3400" >> inputfile-$k-$i
     echo "calcrange 2400 3400" >> inputfile-$k-$i
  
     ./ExoMatch.exe inputfile-$k-$i > outputfile-$k-$i
     done
  done