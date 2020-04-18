# Компилятор
CC := gcc
MAIN_APP := app.exe
TEST_APP := test.exe
.PHONY : clean

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic -pipe
TEST_FLAGS := -fprofile-arcs -ftest-coverage -g0 -pipe

# Файловые зависимости
TEST_FILE := test_main.c
RELEASE_FILES := $(filter-out $(TEST_FILE), $(wildcard *.c))

all : $(MAIN_APP) $(TEST_APP)

# Main app
$(MAIN_APP) : $(patsubst %.c,%.o, $(RELEASE_FILES))
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c -MD $<

include $(wildcard *.d)

# Unit test
$(TEST_APP) : test_main.o io_funcs.o memmory_funcs.o utility_funcs.o
	$(CC) $(TEST_FLAGS) $^ -o $@

$(patsubst %.c,%.o, $(TEST_FILE)) : $(TEST_FILE)
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c -MD $<

# Генерация отчёта покрытия тестов
report : test.exe coverage.info
	genhtml -o report coverage.info

coverage.info : 
	./test.exe && lcov -c -d $(PWD) -o coverage.info

clean :
	rm *.d *.o *.exe

clean_all : clean
	rm *.gcda *.gcno *.info