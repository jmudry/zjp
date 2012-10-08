
all: main

main:
	cc main.c -o main

run: main
	./main

clean: 
	rm -f main
