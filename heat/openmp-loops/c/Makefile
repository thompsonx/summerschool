ifeq ($(COMP),)
COMP=gnu
endif

COMMONDIR=$(shell \
  if test -d '../../common'; then \
    echo '../../common/'; \
  elif test -d '../../../common'; then \
    echo '../../../common/'; \
  fi; \
)

ifeq ($(COMP),cray)
CC=cc
CCFLAGS=-O3 -I/appl/opt/libpng/include -I$(COMMONDIR) -fopenmp
LDFLAGS=-L/appl/opt/libpng/lib
LIBS=-lpng -lz
endif

ifeq ($(COMP),gnu)
CC=gcc
CCFLAGS=-O3 -Wall -I$(COMMONDIR) -fopenmp
LDFLAGS=
LIBS=-lpng
endif

EXE=heat_openmp_loops
OBJS=core.o setup.o utilities.o io.o main.o
OBJS_PNG=$(COMMONDIR)/pngwriter.o


all: $(EXE)

$(COMMONDIR)/pngwriter.o: $(COMMONDIR)/pngwriter.c $(COMMONDIR)/pngwriter.h
core.o: core.c heat.h
utilities.o: utilities.c heat.h
setup.o: setup.c heat.h
io.o: io.c heat.h
main.o: main.c heat.h

$(OBJS_PNG): C_COMPILER := $(CC)
$(OBJS): C_COMPILER := $(CC)

$(EXE): $(OBJS) $(OBJS_PNG)
	$(CC) $(CCFLAGS) $(OBJS) $(OBJS_PNG) -o $@ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(C_COMPILER) $(CCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-/bin/rm -f $(EXE) a.out *.o *.png *~
