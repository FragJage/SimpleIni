#
#	Makefile de SimpleIni
#

# CFLAGS_RELEASE := -02
# CFLAGS_DEBUG := -g -Wall
CFLAGS=-ggdb3 -O0 -DLINUX -Iinclude
LDFLAGS=-lm

VPATH = src:test:examples
OBJS_test = SimpleIni.o main.o
OBJS_example1  = SimpleIni.o example1.o
OBJS_example2  = SimpleIni.o example2.o
OBJS_example3  = SimpleIni.o example3.o

all:	    unittest example1 example2 example3

unittest: $(OBJS_test)
	        g++ -o $@ $(OBJS_test) $(CFLAGS) $(LDFLAGS)
example1: $(OBJS_example1)
	        g++ -o $@ $(OBJS_example1) $(CFLAGS) $(LDFLAGS)
example2: $(OBJS_example2)
	        g++ -o $@ $(OBJS_example2) $(CFLAGS) $(LDFLAGS)
example3: $(OBJS_example2)
	        g++ -o $@ $(OBJS_example3) $(CFLAGS) $(LDFLAGS)

clean:
	    rm -f test example1 example2 example3 $(OBJS_test)

.cpp.o:
	    g++ $(CFLAGS) -c $<