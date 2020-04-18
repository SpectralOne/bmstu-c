@echo off
chcp 861 

del test_now.txt /f /q
del results.txt /f /q

for /L %%i in (1, 1, 8) do ( 
..\app.exe < in%%i.txt > test_now.txt  

echo Test case #%%i >> results.txt
fc test_now.txt out%%i.txt >> results.txt 
)

del test_now.txt /f /q 
