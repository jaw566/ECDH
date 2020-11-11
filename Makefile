all: main

main: main.cpp ecdh.cpp
	gcc main.cpp ecdh.cpp -o main -lm

clean:
	rm -f main
