# change application name here (executable output name)
TARGET=XML_FUSION

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O6
# warnings
WARN=-Wall

WEXTRA=-Wextra

PTHREAD=-pthread



CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(WEXTRA)  $(PTHREAD) -pipe


CURL=-lcurl
# linker
LD=gcc
LDFLAGS=$(PTHREAD)   $(CURL)

OBJS=    main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(CURL) -o main.o

clean:
	rm -f *.o $(TARGET)