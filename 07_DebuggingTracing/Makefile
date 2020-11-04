TRASH =  *.so 


all: wrapper.c 
	gcc wrapper.c -shared -fPIC -ldl -o wrapper.so

test: export LD_PRELOAD=$(shell pwd)/wrapper.so
test:
	touch filename
	touch filename_with_FIX

	rm filename
	rm filename_with_FIX

	test -f filename_with_FIX

	rm filename_with_FIX

clean:
	rm -f $(TRASH)
