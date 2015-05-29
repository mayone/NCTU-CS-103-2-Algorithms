CC = gcc
CFLAGS =  -I.
LDFLAGS = -L.
SOURCES = dijkstra.c
OBJECTS = $(notdir $(SOURCES:.c=.o))
EXECUTE = dijkstra

all: $(OBJECTS) $(EXECUTE)

$(EXECUTE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -c

run:
	./$(EXECUTE) < in.txt
clean:
	rm -rf *~ *.o $(EXECUTE)
