# !/usr/bin/env bash
# -*- coding:utf-8 -*-

echo "read the ending price to new files"
for file in `ls`; do
    echo $file
    newfile=`echo $file | sed 's/\.TXT/\ending.txt/'` ;
    # 1data 2time 3opening 4high 5low 6ending 7amount 8position
    awk '{print $1,$2,$6}' $file>$newfile
    rm $file;
    echo $newfile
done
