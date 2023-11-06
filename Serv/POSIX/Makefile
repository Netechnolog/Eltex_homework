SRC = $(wildcard *.c)
OBJ = $(patsubt %.c, %.o, $(SRC))

TARGET : Server Client
	gcc $(SRC) -o $(OBJ) -lrt

clear:
	rm Server Client
