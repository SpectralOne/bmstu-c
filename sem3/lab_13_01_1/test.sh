#!/bin/bash

make clean
echo -e "\n--- Static func test ---"
echo -e "----"
make static.exe
echo -e "----"
for ((i = 1; i <= 8; i++)) do
    ./static.exe < func_test/in"$i".txt > tmp.txt
    if cmp -s tmp.txt func_test/out"$i".txt; then
    echo тест № "$i" пройден
    else
    echo тест № "$i" не пройден
    echo фактический результат:
    cat tmp.txt
    echo ожидаемый результат:
    cat func_test/out"$i".txt
    echo -e "\n"
    fi
done

make clean
echo -e "\n--- Dynamic func test ---"
echo -e "----"
make dynamic.exe
echo -e "----"

for ((i = 1; i <= 8; i++)) do
    ./dynamic.exe < func_test/in"$i".txt > tmp.txt
    if cmp -s tmp.txt func_test/out"$i".txt; then
    echo тест № "$i" пройден
    else
    echo тест № "$i" не пройден
    echo фактический результат:
    cat tmp.txt
    echo ожидаемый результат:
    cat func_test/out"$i".txt
    echo -e "\n"
    fi
done
make clean

echo -e "\n--- Dynamic load func test ---"
echo -e "----"
make dynamic_load.exe
echo -e "----"

for ((i = 1; i <= 8; i++)) do
    ./dynamic_load.exe < func_test/in"$i".txt > tmp.txt
    if cmp -s tmp.txt func_test/out"$i".txt; then
    echo тест № "$i" пройден
    else
    echo тест № "$i" не пройден
    echo фактический результат:
    cat tmp.txt
    echo ожидаемый результат:
    cat func_test/out"$i".txt
    echo -e "\n"
    fi
done
make clean
rm tmp.txt