CC = g++
LD = g++

CFLAGS = -Wall -std=c++11
LDFLAGS = -Wall -std=c++11

OBJS = criarTabela.cpp main.cpp crud.cpp componente.cpp

TARGET = main

BD=banco_de_dados.db

LIBRARY_PATH = /usr/lib/x86_64-linux-gnu/libsqlite3.so
LIBRARIES = -lsqlite3

.cpp.o:
	$(CC) $(CFLAGS) -c $@ $<

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@ -L$(LIBRARY_PATH) $(LIBRARIES)

clean:
	rm -f *.o $(TARGET) $(BD)