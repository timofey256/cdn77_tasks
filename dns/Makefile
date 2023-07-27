FILENAME=main

.PHONY: all clear

all: ${FILENAME}.o


print: ${FILENAME}.o
	./${FILENAME}.o

${FILENAME}.o: ${FILENAME}.cpp
	gcc ${FILENAME}.cpp -lstdc++ -o ${FILENAME}.o
	
clear:
	rm -f ${FILENAME}.o
