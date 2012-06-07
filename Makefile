# the file "Depend" must exist for make to run
# for lemke code only

.SUFFIXES:
.SUFFIXES: .c .o .h

CC = gcc
# -lm  links the math library in
CFLAGS = -ansi -Wall -O3 -g

# needed for gmp library
LIBDIR     = /usr/local/lib

%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

DEPFILE = Depend

COMOBJ  = alloc.o col.o mp.o rat.o

INLEMOBJ  = lemke.o inlemke.o 

INLHOBJ = inlemkehowson.o lemke.o 

GMPOBJ = gmpwrap.o glemke.o

ALLOBJ = $(COMOBJ) $(INLEMOBJ) $(TREEOBJ) $(METHOBJ) $(GMPOBJ)

# local variables for single substitutions

GMP = $(COMOBJ) $(TREEOBJ) $(METHOBJ) $(GMPOBJ) 

INLEMKE = $(COMOBJ) $(INLEMOBJ)

INLH = $(COMOBJ) $(INLHOBJ)

inlh: $(INLH)
	$(CC) $(CFLAGS) $(INLH) -o inlh

inlemke: $(INLEMKE)
	$(CC) $(CFLAGS) $(INLEMKE) -o inlemke 

depend:: 
	gcc -MM $(ALLOBJ:.o=.c) > $(DEPFILE)

.PHONY : clean 

clean:
	-rm -f *.o core *.exe $(DEPFILE); touch $(DEPFILE); make depend

include $(DEPFILE)
