#!/bin/bash
rm salidaseleccion.dat
contador=1000
while [ $contador -lt 100000 ]; do
./seleccion $contador >> salidaseleccion.dat
let "contador+=1000"
done
