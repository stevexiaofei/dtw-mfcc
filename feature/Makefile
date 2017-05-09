vpath  %.d depend
vpath  %.o obj
VPATH=../include:depend
BINPATH=../bin
TESTBINPATH=../testbin
LIBPATH=../lib
ALLBINS= gettemplate
ALLLIBS=
ALLTESTBINS=mfcctest
CXXFLAGS+=-D DEBUGE -I../
LDFLAGS+=../lib/libutil.a

mfcctestobjs=$(addprefix obj/,mfcctest.o mfcc.o )
mfcctest:$(mfcctestobjs)
	$(CC)  -o $@ $(mfcctestobjs) $(LDFLAGS)
	cp $@ ../testbin

gettemplateobjs=$(addprefix obj/,gettemplate.o mfcc.o)
gettemplate:$(gettemplateobjs)
	$(CC) -o $@ $^ $(LDFLAGS)
	cp $@ ../testbin
include ../Makefile.env

