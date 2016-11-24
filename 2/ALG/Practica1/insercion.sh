#!/bin/bash
rm salidainsercion.dat
contador=1000
while [ $contador -lt 100000 ]; do
./insercion $contador >> salidainsercion.dat
let "contador+=1000"
done
