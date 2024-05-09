# Lab 3 Makefile
# Trevor Gerald

CFLAGS= -std=c99 -pedantic -Wformat -Wreturn-type 
all:  tags headers lab3

headers: *.c tags
	headers.sh

tags: *.c
	ctags -R .

# this is our master compiler rule to generate .o files.
# It needs all 4 warnings
%.o: %.c *.h
	gcc $(CFLAGS) -g -c $< -o $@

lab3: lab3.o memory.o lists.o bits.o input.o physics.o sim.o output.o n2.h structs.h constants.h
	gcc -g -o $@ $^ -L. -lbtp -lncurses -lm -llinkedlist

# * PROTOTYPES HAVE BEEN GRADED *
# Read hex input from file and determine if it is a mascot
proto_one: proto_one.o
	gcc -o $@ $^ -L. -lbtp -lncurses -lm

# Check to see if memory allocation works as expected
proto_two: proto_two.o bits.o structs.h
	gcc -o $@ $^ -L. -lbtp -lncurses -lm

# Read in output and create coin or mascot object with input values
proto_three: proto_three.o bits.o
	gcc -o $@ $^ -L. -lbtp -lncurses -lm

# Experiment with insert and iterate with linked lists and strings
proto_four: proto_four.o libll.h
	gcc -o $@ $^ -L. -lbtp -lncurses -lm -llinkedlist

# Zip Target  
lab3.zip: makefile *.c *.h *.sh README_LAB3 libbtp.a liblinkedlist.a
	zip $@ $^
# 	first remove old install folder
	rm -rf install
# 	create the install folder
	mkdir install
# 	unzip to the install folder
	unzip lab3.zip -d install
# 	make all applicable prototypes
	make -r proto_one
	make -r proto_two
	make -r proto_three
	make -r proto_four
# 	LOOK FOR ERRORS BELOW HERE
	make -C install -r lab3
# 	LOOK FOR BUILD ERRORS ABOVE HERE
	rm -rf install

