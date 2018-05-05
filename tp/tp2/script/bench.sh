#!/bin/bash
EXE="bin/demo/5-colimacon-no-print"

if [ "$#" -eq 0 ];then
  echo "Utilisation: bench.sh [n-echantillon]"
else
  max_echantillon=$1
  total=0
  size=(10 100 1000 10000)
  for i in "${size[@]}"
  do
    for ((e=0; e<=$max_echantillon; e++))
    do
      t=$(./bin/demo/6-colimacon-time $i $i)
      total=$(echo "scale=9; $total+$t" | bc)
    done
    echo "$i $(echo "scale=9; $total / $max_echantillon" | bc)s"
  done
fi
