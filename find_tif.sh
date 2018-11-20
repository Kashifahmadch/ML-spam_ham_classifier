#!/bin/bash

for f in $(find . -iname "*.spam.txt" -type f)
do
    echo "$(basename $f)"
done

for f in $(find . -iname "*.zip" -type f)
do
    less $f | grep "tif" | awk '{print $NF}'
done
