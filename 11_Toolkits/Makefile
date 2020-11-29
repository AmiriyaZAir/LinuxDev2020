all: words_counter

words_counter: words_counter.c
	gcc `pkg-config --cflags glib-2.0` words_counter.c `pkg-config --libs glib-2.0` -o words_counter
	
	#gcc words.c -I/usr/include/glib-2.0 
clean:
	rm words_counter