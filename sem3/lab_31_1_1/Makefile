CC := gcc
CFLAGS := -std=c99 -Wall -pedantic -pipe -g3 -ggdb

app.exe : $(patsubst %.c,%.o, $(wildcard *.c))
	$(CC) $(CFLAGS) $^ -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) -c -MD $<

include $(wildcard *.d)

clean :
	rm -f *.d *o *.exe
