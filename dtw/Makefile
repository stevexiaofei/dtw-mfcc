VPATH=./include
BINPATH=./bin
TESTBINPATH=./testbin
LIBPATH=./lib
ALLBINS= dtwAsr
ALLLIBS=
ALLTESTBINS=testAccumDist

CXXFLAGS+= -D DEBUGE -I../
LDFLAGS+=

accumdistobjs=$(addprefix obj/, testAccumDist.o)
testAccumDist:$(accumdistobjs)
	$(CC) -o $@ $^ $(LDFLAGS)
	cp $@ $(TESTPATH)

dtwasrobjs=$(addprefix obj/, dtwAsr.o) distance/obj/util.o
dtwAsr:$(dtwasrobjs)
	$(CC) -o $@ $^ $(LDFLAGS)

dtwAsr:

include ../Makefile.env

