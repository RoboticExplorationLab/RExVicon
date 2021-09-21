#!/bin/bash
cp $1 "$1_old"
sed -i 's/-mt-d//g' $1
sed -i 's/-mt//g' $1
sed -i 's/-lboost*l //g' $1
sed -i 's/-lboost_math_c99l //g' $1
sed -i 's/-lboost_math_tr1l //g' $1

