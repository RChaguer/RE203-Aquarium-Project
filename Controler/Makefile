CFLAGS=-Wall -Wextra -Iinclude -fPIC 

INC_DIR=include/

BUILD_DIR=build/

all: install

src/%.o: src/%.c
	gcc $(CFLAGS) -o $(BUILD_DIR)$(patsubst src/%.o,%.o,$@) -c $<

make_dir: 
	mkdir -p build build/structs build/tools build/tst build/terminal

install : make_dir src/tools/list.o  src/structs/view.o  src/structs/aquarium.o src/terminal/prompt.o

tst : tst/simple_test.c tst/parser_test.c
	gcc $(CFLAGS) -o $(BUILD_DIR)tst/simple_test $(BUILD_DIR)tools/list.o \
												 $(BUILD_DIR)structs/view.o \
												 $(BUILD_DIR)structs/aquarium.o \
												 tst/simple_test.c
	valgrind ./$(BUILD_DIR)tst/simple_test

	gcc $(CFLAGS) -o $(BUILD_DIR)tst/parser_test $(BUILD_DIR)tools/list.o \
												 $(BUILD_DIR)structs/view.o \
												 $(BUILD_DIR)structs/aquarium.o \
												 $(BUILD_DIR)terminal/prompt.o \
												 tst/parser_test.c
	valgrind ./$(BUILD_DIR)tst/parser_test

run : src/terminal/main_t.c
	gcc $(CFLAGS) -o $(BUILD_DIR)term $(BUILD_DIR)tools/list.o \
										  $(BUILD_DIR)structs/view.o \
										  $(BUILD_DIR)structs/aquarium.o \
										  $(BUILD_DIR)terminal/prompt.o \
										  $< -lreadline
	./$(BUILD_DIR)term
clean :
	rm -r $(BUILD_DIR)