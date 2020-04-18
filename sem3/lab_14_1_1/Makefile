CFLAGS = -lui -Wl,-rpath,. -lgtk-3 -lgdk-3 -lgobject-2.0 -lglib-2.0 -ldl
CC = gcc

source_dirs := lab10_src

source_files := $(addsuffix /*.c,$(source_dirs)) 

main : app_timer.exe

app_timer.exe: lab14_timer.c $(notdir $(patsubst %.c,%.o,$(wildcard $(source_files))))
	$(CC) $^ -o $@ $(CFLAGS)

app.exe: lab14.c $(notdir $(patsubst %.c,%.o,$(wildcard $(source_files))))
	 $(CC) $^ -o $@ $(CFLAGS)

VPATH := $(source_dirs)

%.o: %.c
	$(CC) -c -MD $(addprefix -I,$(source_dirs)) $<

include $(wildcard *.d) 

ex :
	$(CC) -o example.exe trash/main1.c $(CFLAGS)

clean :
	rm -f *.o *.exe *.d