#t: $(wildcard *.cpp)
#	g++ -std=c++14 -g -Wall -Wextra -Werror -Wpedantic -o t $^ \
#		-lsfml-graphics -lsfml-window -lsfml-system

PROJECT=xr
SOURCES=$(shell find . -type f -name '*cpp')
LIB_TYPE=
INCPATHS=
LIBPATHS=
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
CFLAGS=-std=c++14 -c -Wall -Wextra -Werror -Wpedantic -g
#CFLAGS=-std=c++14 -c -Wall -Wextra -Werror -Wpedantic -O3 -DNDEBUG
CC=g++

# ------------ MAGIC BEGINS HERE -------------

# Automatic generation of some important lists
OBJECTS=$(SOURCES:.cpp=.o)
INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
LIBFLAGS=$(foreach TMP,$(LIBPATHS),-L$(TMP))

# Set up the output file names for the different output types
ifeq "$(LIB_TYPE)" "shared"
	BINARY=lib$(PROJECT).so
	LDFLAGS += -shared
else ifeq "$(LIB_TYPE)" "static"
	BINARY=lib$(PROJECT).a
else
	BINARY=$(PROJECT)
endif

all: $(SOURCES) $(BINARY)

$(BINARY): $(OBJECTS)
# Link the object files, or archive into a static library
ifeq "$(LIB_TYPE)" "static"
	ar rcs $(BINARY) $(OBJECTS)
else
	$(CC) $(LIBFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
endif

.cpp.o:
	$(CC) $(INCFLAGS) $(CFLAGS) -fPIC $< -o $@

distclean: clean
	rm -f $(BINARY)

clean:
	rm -f $(OBJECTS)
