FILENAME=main

.PHONY: all clean

all: ${FILENAME}.o


print: ${FILENAME}.o
	./${FILENAME}.o

${FILENAME}.o: ${FILENAME}.cpp
	gcc ${FILENAME}.cpp -lstdc++ -o ${FILENAME}.o
	
clean:
	rm -f ${FILENAME}.o
