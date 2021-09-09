CFLAGS=CFLAGS=-Wall -Wextra -Iinclude -fPIC -O3 -g

CTR_DIR=Controler/
AQ_DIR=Aquarium/
INC_DIR=include/
SRC_DIR=src/
BUILD_DIR=build/

.PHONY: controler_install controler_tst

all: controler_install client_install

controler_install:
	make install --no-print-directory -C $(CTR_DIR)

controler_debug:
	make debug --no-print-directory -C $(CTR_DIR) 

controler_test:
	make test --no-print-directory -C $(CTR_DIR)

controler_run:
	make run --no-print-directory -C $(CTR_DIR)
	
client_install:
	make install --no-print-directory -C $(AQ_DIR)

client_run1:
	make run1 --no-print-directory -C $(AQ_DIR) 
	
client_run2:
	make run2 --no-print-directory -C $(AQ_DIR) 

client_run3:
	make run3 --no-print-directory -C $(AQ_DIR) 

client_run4:
	make run4 --no-print-directory -C $(AQ_DIR) 

client_run5:
	make run5 --no-print-directory -C $(AQ_DIR) 

lib_config: lib_config.sh
	bash $^

clean:
	rm $(AQ_DIR)lib/*
	cp $(AQ_DIR).lib_windows/* $(AQ_DIR)lib/
	make clean --no-print-directory -C $(CTR_DIR)
	make clean --no-print-directory -C $(AQ_DIR)
