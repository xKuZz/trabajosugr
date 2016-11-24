#!/bin/bash
rm salidahanoi.dat
contador=1000
while [ $contador -lt 100000 ]; do
./hanoi $contador >> salidahanoi.dat
let "contador+=1000"
done
