#!/bin/bash

for ((i = 1; i <= 10; i++)) do
    ../app.exe < in"$i".txt > tmp.txt
    if cmp -s tmp.txt out"$i".txt; then
    echo тест № "$i" пройден
    else
    echo тест № "$i" не пройден
    echo фактический результат:
    cat tmp.txt
    echo ожидаемый результат:
    cat out"$i".txt
    echo -e "\n"
    fi
done
rm tmp.txt

