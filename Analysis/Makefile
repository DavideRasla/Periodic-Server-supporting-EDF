CFLAGS=-Wall -Wextra -pedantic
CFLAGS+=-std=c11

all: h_test sbf_test tda_test

h_test:   h_test.o   dbf.o task_io.o sbf.o
sbf_test: sbf_test.o                 sbf.o
tda_test: tda_test.o dbf.o task_io.o

clean:
	rm -f *.o
	rm -f h_test sbf_test tda_test
