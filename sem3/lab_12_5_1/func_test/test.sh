#!/bin/bash

for ((i = 1; i <= 9; i++)) do
    ../app.exe < in"$i" > tmp
    if cmp -s tmp out"$i"; then
    echo тест № "$i" пройден
    else
    echo тест № "$i" не пройден
    echo фактический результат:
    cat tmp
    echo ожидаемый результат:
    cat out"$i"
    echo -e "\n"
    fi
done
rm tmp