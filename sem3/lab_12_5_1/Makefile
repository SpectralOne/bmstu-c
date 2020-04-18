# Компилятор
CC := gcc
MAIN_APP := app.exe
TEST_APP := test.exe
.PHONY : clean

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic -pipe -g3
TEST_FLAGS := -fprofile-arcs -ftest-coverage -g0 -pipe

# Файловые зависимости
TEST_FILE := test_main.c
RELEASE_FILES := $(filter-out $(TEST_FILE), $(wildcard *.c))
TEST_APP_OBJECTS := test_main.o list_operations.o

all : $(MAIN_APP) $(TEST_APP)

# Main app
$(MAIN_APP) : $(patsubst %.c,%.o, $(RELEASE_FILES))
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c -MD $<

include $(wildcard *.d)

# Unit test
$(TEST_APP) : $(TEST_APP_OBJECTS)
	$(CC) $(TEST_FLAGS) $^ -o $@

$(patsubst %.c,%.o, $(TEST_FILE)) : $(TEST_FILE)
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c -MD $<

# Генерация отчёта покрытия тестов
report : test.exe coverage.info
	genhtml -o report coverage.info

coverage.info : 
	./test.exe && lcov -c -d $(PWD) -o coverage.info

func : $(MAIN_APP)
	cd func_test && ./test.sh

clean :
	rm -f *.d *.o *.exe

clean_all : clean
	rm -f *.gcda *.gcno *.info