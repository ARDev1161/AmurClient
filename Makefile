CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lprotobuf -lpthread -lrt
SOURCES=AmurClient.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=AmurClient
RM =/bin/rm -rf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@$(RM) *.o
	@$(RM) $(EXECUTABLE)*
