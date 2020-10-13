CFLAGS = -Wall -fPIC
GENERATES = prog prog-a prog-so README liboutput.so liboutput_static.a
TRASH = *.o *~ o.* *.txt

all:    README prog prog-a prog-so

fun.o:	outlib.h

#libraries
liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so:	const.o fun.o
	cc -shared $^ -o $@

#binaries
prog:	const.o fun.o prog.o

prog-a:	prog.o liboutput_static.a
	cc $(CFLAGS) -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. prog.o -loutput -o $@


README:	prog
	./$< 2> $@

test:export LD_LIBRARY_PATH=$(shell pwd)
test: prog prog-a prog-so

	./prog  2 > prog_0.txt 
	./prog-a 2 > prog-a_0.txt 
	./prog-so 2 > prog-so_0.txt 
	
	./prog arg1  2> prog_1.txt 
	./prog-a arg1  2> prog-a_1.txt 
	./prog-so arg1  2> prog-so_1.txt 
	
	./prog arg1 arg2 arg3  2 > prog_3.txt 
	./prog-a arg1 arg2 arg3  2 > prog-a_3.txt 
	./prog-so arg1 arg2 arg3  2 > prog-so_3.txt 

	cmp prog_0.txt prog-a_0.txt
	cmp prog_0.txt prog-so_0.txt
	cmp prog-so_0.txt prog-a_0.txt

	cmp prog_1.txt prog-a_1.txt
	cmp prog_1.txt prog-so_1.txt
	cmp prog-so_1.txt prog-a_1.txt

	cmp prog_3.txt prog-a_3.txt
	cmp prog_3.txt prog-so_3.txt
	cmp prog-so_3.txt prog-a_3.txt

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)
