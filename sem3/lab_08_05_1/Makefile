# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic

# Сборка программы
app.exe : main.o err_handler.o array_utility_funcs.o io_funcs.o mu_funcs.o
	$(CC) -o app.exe err_handler.o array_utility_funcs.o io_funcs.o mu_funcs.o main.o -lm

err_handler.o : err_handler.c err_handler.h
	$(CC) $(CLFAGS) -c err_handler.c

array_utility_funcs.o : array_utility_funcs.c array_utility_funcs.h
	$(CC) $(CLFAGS) -c array_utility_funcs.c

io_funcs.o : io_funcs.c io_funcs.h
	$(CC) $(CLFAGS) -c io_funcs.c

mu_funcs.o : mu_funcs.c mu_funcs.h
	$(CC) $(CFLAGS) -c mu_funcs.c

main.o: main.c err_handler.h array_utility_funcs.h io_funcs.h mu_funcs.h
	$(CC) $(CFLAGS) -c main.c

# Сборка программы для модульного тестирования
test.exe : test_main.o array_utility_funcs.o
	$(CC) -o test.exe test_main.o array_utility_funcs.o

test_main.o : test_main.c array_utility_funcs.h
	$(CC) $(CFLAGS) -c test_main.c

clean :
	rm *.o *.exe
