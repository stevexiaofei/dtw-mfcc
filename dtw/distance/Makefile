vpath  %.d depend
vpath  %.o obj
VPATH=../include:depend
BINPATH=../bin
TESTBINPATH=../testbin
LIBPATH=../lib
ALLBINS=
ALLLIBS=
ALLTESTBINS=testcomputedist
CXXFLAGS+=-D DEBUGE -I../../
LDFLAGS+=../../lib/libutil.a

disttestobjs=$(addprefix obj/,testcomputedist.o util.o )
testcomputedist:$(disttestobjs)
	$(CC)  -o $@ $^ $(LDFLAGS)
	cp $@ $(TESTPATH)

include ../../Makefile.env

