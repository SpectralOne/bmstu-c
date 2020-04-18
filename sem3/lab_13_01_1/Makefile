CC := gcc
.PHONY : clean
CFLAGS := -std=c99 -Wall -Werror -c


static.exe: test_static.exe main.c non_lib.o da_lib.a
	$(CC) -o static.exe main.c non_lib.o da_lib.a -lm

dynamic.exe: test_dynamic.exe main.c non_lib.o libdaf.so
	$(CC) -o dynamic.exe main.c non_lib.o -L. -ldaf -Wl,-rpath=\$$ORIGIN -lm

dynamic_load.exe: test_dynamic_load.exe main.o non_lib.o libdaf.so
	$(CC) main.o -o dynamic_load.exe non_lib.o -ldl -lm

test_static.exe: test_main.o non_lib.o da_lib.a
	$(CC) -o test_static.exe test_main.c non_lib.o da_lib.a -lm

test_dynamic.exe: test_main.o non_lib.o libdaf.so
	$(CC) -o test_dynamic.exe test_main.c non_lib.o -L. -ldaf -Wl,-rpath=\$$ORIGIN -lm

test_dynamic_load.exe: test_dyn_load.o non_lib.o libdaf.so
	$(CC) test_dyn_load.o -o test_dynamic_load.exe non_lib.o -ldl -lm

libdaf.so: da_lib.o 
	$(CC) -shared -o libdaf.so da_lib.o -lm

da_lib.a: da_lib.o	
	ar rc da_lib.a da_lib.o
	ranlib da_lib.a

da_lib.o: da_lib.c da_lib.h
	$(CC) $(CFLAGS) -fPIC da_lib.c

main.o: main.c da_lib.h
	$(CC) $(CFLAGS) -D LOAD main.c -lm

test_main.o: test_main.c da_lib.h
	$(CC) $(CFLAGS) -D LOAD test_main.c -lm

test_dyn_load.o: test_dyn_load.c da_lib.h
	$(CC) $(CFLAGS) test_dyn_load.c -lm

non_lib.o: non_lib.c non_lib.h
	$(CC) $(CFLAGS) non_lib.c -lm

clean :
	rm -f *.o *.exe *.a *.so *.d 