CC=gcc -g
CFLAGS=-Wall -Iinclude -fPIC 
INC_DIR=include/
BUILD_DIR=build
SRC_DIR=src
TST_DIR=tst

STRUCTS  = $(wildcard src/structs/*.c)
TERMINAL = $(wildcard src/terminal/*.c)
TOOLS    = $(wildcard src/tools/*.c)
TST      = $(wildcard tst/*.c)
PROTOCOL = $(wildcard src/protocol/*.c)
SRC 	 = $(STRUCTS) $(TERMINAL) $(TOOLS) $(PROTOCOL)
SRC_OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst src/%.c, %.o, $(SRC)))
TST_OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %, $(TST)))

.PHONY: install server test

all: install 

build/tst/%: $(TST_DIR)/%.c $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

install : make_dir $(SRC_OBJS) $(TST_OBJS) $(BUILD_DIR)/server

build/server:	$(SRC_DIR)/server.c $(SRC_OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

test : $(TST_OBJS)
	for tst in $(TST_OBJS); do \
    	valgrind --leak-check=full ./$$tst; \
	done

run : $(BUILD_DIR)/server
	./$< 

debug: $(BUILD_DIR)/server
	valgrind ./$< 
	
make_dir: 
	mkdir -p build build/structs build/tools build/tst build/terminal build/protocol

clean :
	rm -fr $(BUILD_DIR)