all: main.c
	gcc -m32 -shared -I/usr/include/python2.7/ -lpython2.7 -o MainModule.so main.c
	mv MainModule.so ../controller

clean:
	rm -f *.so
	rm -f ../controller/MainModule.so
