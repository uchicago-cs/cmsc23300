CFLAGS=-std=gnu99 -w

all: di1 di2 ds1 ds2

di1: dispatch-int-one

dispatch-int-one: handlers.o

di2: dispatch-int-two

dispatch-int-two: handlers.o

ds1: dispatch-str-one

dispatch-str-one: handlers.o

ds2: dispatch-str-two

dispatch-str-two: handlers.o

clean:
	rm -f dispatch-int-one dispatch-int-two dispatch-str-one dispatch-str-two
	rm -f handlers.o


