FLAGS=`pkg-config --cflags --libs gtk+-3.0` -rdynamic

all: main.o
	gcc -o Game main.o $(FLAGS) 
    
main.o: src/main.c
	gcc -c src/main.c $(FLAGS) -o main.o
    
clean:
	rm -f *.o Game
