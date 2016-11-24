#!/bin/bash
rm salidaheapsort.dat
contador=1000
while [ $contador -lt 100000 ]; do
./heapsort $contador >> salidaheapsort.dat
let "contador+=1000"
done
