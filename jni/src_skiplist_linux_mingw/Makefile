
C_FLAGS=-D_ANDROID_ -std=gnu99

# Default build target
all: main

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
main : main.c
	gcc $(C_FLAGS) $^ -o $@

run:
	./main


# Clean
clean:
	rm -rf *.o main
