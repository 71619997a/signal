all: compile

compile: siggy.c
	gcc -o siggy.out siggy.c

run: compile
	./siggy.out

clean:
	rm siggy.out
