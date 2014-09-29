CFLAGS=-c -std=c11 -O3 -Wall -Werror -pedantic
LIBS=-lm -lpng16

SRC=main.c sets.c render.c

OBJ=$(SRC:.c=.o)
BUILD=fractal-generator

all: $(SRC) $(BUILD)

$(BUILD): $(OBJ)
	gcc $(LIBS) $(OBJ) -o $@

.c.o:
	gcc $(CFLAGS) $(LIBS) $< -o $@

clean:
	rm -f *.o $(BUILD)
