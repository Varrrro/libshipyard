CC = gcc
VPATH = src
BUILD_DIR = build


.PHONY: all checkdir clean

all: checkdir libshipyard.a

libshipyard.a: sched.o
	ar rcs $(BUILD_DIR)/$@ $(BUILD_DIR)/$<

sched.o: sched.c sched.h
	$(CC) -o $(BUILD_DIR)/$@ -c $<

checkdir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -r $(BUILD_DIR)
