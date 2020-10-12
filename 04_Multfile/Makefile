GENERATES = prog README
TRASH = *.o *~ o.*

all:    README prog

prog:   const.o fun.o prog.o

README: prog
	./$< 2> $@

fun.o:  outlib.h

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
