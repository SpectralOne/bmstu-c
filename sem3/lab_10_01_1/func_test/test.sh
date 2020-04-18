#!/bin/bash

for ((i = 1; i <= 14; i++)) do
    ../app.exe < in"$i" > tmp

    if [ "$?" == "0" ]; then
        if cmp -s kids.txt out"$i"; then
            echo тест № "$i" пройден
        else
            echo тест № "$i" не пройден
            echo фактический результат:
            cat kids.txt
            echo ожидаемый результат:
            cat out"$i"
            echo -e "\n"
        fi
    else
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
    fi
done
rm kids.txt
rm tmp