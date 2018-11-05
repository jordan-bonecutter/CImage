## MAKEFILE ##

CC = gcc -ansi -std=c99 -Wall -DNDEBUG -DTIMETRIALS -DWINDOWS -Ofast
CO = $(CC) -c

## RULES ##

all: Test.o Image.o ImageEditor.o Editors.o Makefile
	$(CC) Test.o Image.o ImageEditor.o Editors.o -o Test

Test.o: Test.c Image.h ImageEditor.h Editors.h Makefile
	$(CO) Test.c -o Test.o

Image.o: Image.c Image.h Makefile
	$(CO) Image.c -o Image.o

ImageEditor.o: ImageEditor.c ImageEditor.h Image.h Makefile
	$(CO) ImageEditor.c -o ImageEditor.o

Editors.o: Editors.c Editors.h Image.h ImageEditor.h Makefile
	$(CO) Editors.c -o Editors.o

clean:
	rm -f *.o
	rm -f *.dSYM
	rm -f Test
