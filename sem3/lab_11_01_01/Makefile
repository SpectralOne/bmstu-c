# Компилятор
CC := gcc
TEST_APP := test.exe
.PHONY : clean

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic -pipe
TEST_FLAGS := -fprofile-arcs -ftest-coverage -g0 -pipe

$(TEST_APP) : $(patsubst %.c,%.o, $(wildcard *.c))
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c -MD $<

include $(wildcard *.d)

# clean :
	# rm -f *.d *.o *.exe

report : test.exe coverage.info
	genhtml -o report coverage.info

coverage.info : 
	./test.exe && lcov -c -d $(PWD) -o coverage.info

clean :
	rm -f *.d *.o *.exe

clean_all : clean
	rm -rf *.gcda *.gcno *.info report