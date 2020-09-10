# Define the machine object files for your program
OBJECTS = ibt004Project5Part2.o HashTable.o
# Define your include file
INCLUDES = HashTable.h

# make for the executable
p5p2: ${OBJECTS}
	gcc -g -o p5p2 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c -O3 $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
