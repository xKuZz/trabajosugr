#!/bin/bash
rm salidaquicksort.dat
contador=1000
while [ $contador -lt 100000 ]; do
./quicksort $contador >> salidaquicksort.dat
let "contador+=1000"
done
