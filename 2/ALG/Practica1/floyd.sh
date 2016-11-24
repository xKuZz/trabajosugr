#!/bin/bash
rm salidafloyd.dat
contador=1000
while [ $contador -lt 100000 ]; do
./floyd $contador >> salidafloyd.dat
let "contador+=1000"
done
