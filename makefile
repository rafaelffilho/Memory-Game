FLAGS=`pkg-config --cflags --libs gtk+-3.0` -rdynamic

all: src/main.o
	gcc -o Game src/main.o $(FLAGS) 
    
src/main.o: src/main.c
	gcc -c src/main.c $(FLAGS) -o src/main.o
    
clean:
	rm -f *.o src/*.o Game
