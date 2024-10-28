#!/bin/bash

for i in {1..20}; do
    mkdir -p "$i"
    echo "$i/$i.txt" > "$i/$i.txt"
done

echo "$i.txt" > 14/14.txt

for i in {1..20}; do
    ln -s "$PWD/$i/$i.txt" "$PWD/$i.txt"
done

for i in {1..20}; do 
    if [[ $i != *4* ]]; then 
        rm -r "$i"  
        rm -f "$i.txt" 
    fi
done

