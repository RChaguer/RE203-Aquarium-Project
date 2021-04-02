CFLAGS=CFLAGS=-Wall -Wextra -Iinclude -fPIC -O3

CTR_DIR=Controler/
AQ_DIR=Aquarium/
INC_DIR=include/
SRC_DIR=src/
BUILD_DIR=build/

.PHONY: controler_install controler_tst

all: controler_install controler_tst

controler_install:
	make install --no-print-directory -C $(CTR_DIR)

controler_tst:
	make tst --no-print-directory -C $(CTR_DIR)

controler_run:
	make run --no-print-directory -C $(CTR_DIR)
clean:
	make clean --no-print-directory -C $(CTR_DIR)