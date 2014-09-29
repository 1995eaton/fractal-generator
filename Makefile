CFLAGS=-c -std=c11 -O3 -Wall -Werror -pedantic
LIBS=-lm -lpng16 `pkg-config --cflags --libs gtk+-3.0`

SRC=main.c sets.c render.c viewer.c

OBJ=$(SRC:.c=.o)
BUILD=fractal-generator

all: $(SRC) $(BUILD)

$(BUILD): $(OBJ)
	gcc $(LIBS) $(OBJ) -o $@

.c.o:
	gcc $(CFLAGS) $(LIBS) $< -o $@

clean:
	rm -f *.o $(BUILD)
