CC = gcc
CFLAGS = -Wall -pthread

# Source files
SRC = resource_manager.c resource_utils.c example_clients.c example_maintenance.c
OBJ = $(SRC:.c=.o)

# Executable files
EXE1 = example_clients
EXE2 = example_maintenance

all: $(EXE1) $(EXE2)

# Build the resource management library
resource_manager.o: resource_manager.c resource_manager.h
	$(CC) $(CFLAGS) -c resource_manager.c -o resource_manager.o

resource_utils.o: resource_utils.c resource_utils.h
	$(CC) $(CFLAGS) -c resource_utils.c -o resource_utils.o

# Compile example programs
example_clients: example_clients.o resource_manager.o resource_utils.o
	$(CC) $(CFLAGS) example_clients.o resource_manager.o resource_utils.o -o example_clients

example_maintenance: example_maintenance.o resource_manager.o resource_utils.o
	$(CC) $(CFLAGS) example_maintenance.o resource_manager.o resource_utils.o -o example_maintenance

# Build object files for examples
example_clients.o: example_clients.c resource_manager.h resource_utils.h
	$(CC) $(CFLAGS) -c example_clients.c -o example_clients.o

example_maintenance.o: example_maintenance.c resource_manager.h resource_utils.h
	$(CC) $(CFLAGS) -c example_maintenance.c -o example_maintenance.o

# Clean build files
clean:
	rm -f *.o $(EXE1) $(EXE2)
