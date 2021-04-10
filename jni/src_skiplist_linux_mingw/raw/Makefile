
ZLIB_HOME=../../thirdparty/zlib-master/

all: main

main : decoder.c
	gcc -g $(C_FLAGS) $^ -o $@ -L${ZLIB_HOME} -I${ZLIB_HOME} -lz 

run:
	./main


# Clean
clean:
	rm -rf *.o main
