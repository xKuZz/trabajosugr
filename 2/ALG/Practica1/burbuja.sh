#!/bin/bash
rm salidaburbuja.dat
contador=1000
while [ $contador -lt 100000 ]; do
./burbuja $contador >> salidaburbuja.dat
let "contador+=1000"
done
