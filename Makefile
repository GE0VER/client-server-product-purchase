CC = gcc
CFLAGS = -Wall -g
SRC = main.c client.c server.c
OBJ = $(SRC:.c=.o)
EXEC = server_program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)
