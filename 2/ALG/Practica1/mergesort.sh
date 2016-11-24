#!/bin/bash
rm salidamergesort.dat
contador=1000
while [ $contador -lt 100000 ]; do
./mergesort $contador >> salidamergesort.dat
let "contador+=1000"
done
