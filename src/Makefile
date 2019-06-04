DATE=$(shell date)
COMPILER = gcc
CFLAGS=-c -Wall -I .
LFLAGS=-Wall -lrt
OBJS=PR_Teclado.o PR_RGB.o PR_Timers.o PR_Entradas.o PR_Relays.o PR_adc.o shared_memory.o
SLIB=minfotronic.a
# Introducimos macros.
#    < Contiene la dependencia del target
#    @ Contiene el target

main: $(OBJS)
	ar rcs lib$(SLIB) $(OBJS)

%.o: %.c
	$(COMPILER) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f *.a

all: clean main