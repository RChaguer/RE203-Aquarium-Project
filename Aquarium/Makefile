SRC_DIR=src
LIB_DIR=lib
BUILD_DIR=build

CFLAGS = --module-path ${LIB_DIR} --add-modules javafx.controls
FLAGS = --module-path ../${LIB_DIR} --add-modules javafx.controls

install: mkdir_dir client

mkdir_dir:
	mkdir -p ${BUILD_DIR}

client:
	javac -d ${BUILD_DIR} $(CFLAGS) ${SRC_DIR}/*.java

run1:
	cd $(BUILD_DIR) && java $(FLAGS) src.Main ../src/affichage1.cfg 

run2:
	cd $(BUILD_DIR) && java $(FLAGS) src.Main ../src/affichage2.cfg 

run3:
	cd $(BUILD_DIR) && java $(FLAGS) src.Main ../src/affichage3.cfg 

run4:
	cd $(BUILD_DIR) && java $(FLAGS) src.Main ../src/affichage4.cfg 

run5:
	cd $(BUILD_DIR) && java $(FLAGS) src.Main ../src/affichage5.cfg 

clean :
	rm -fr $(BUILD_DIR)