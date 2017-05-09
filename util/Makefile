vpath  %.d depend
vpath  %.o obj
VPATH=../include:depend
BINPATH=../bin
TESTBINPATH=../testbin
LIBPATH=../lib
ALLBINS=
ALLLIBS=libutil.a
ALLTESTBINS=iotest testcpuFFT featIOtest
CXXFLAGS+= #-D DEBUGE

featiotestobjs=$(addprefix obj/, featIOtest.o)
featIOtest:$(featiotestobjs)
	$(CC) $(LDFLAGS) -o $@ $^

objs=$(addprefix obj/,cpuFFT.o )
libutil.a:$(objs)
	$(AR) $@ $(objs)
	cp $@ ../lib

iotestobjs=$(addprefix obj/,io-test.o )
iotest:$(iotestobjs)
	$(CC) $(LDFLAGS) -o iotest $(iotestobjs)
	cp $@ ../testbin

testcpufft=$(addprefix obj/,cpuFFT.o testcpuFFT.o)
testcpuFFT:$(testcpufft)
	$(CC) $(LDFLAGS) -o testcpuFFT $(testcpufft)
	cp $@ ../testbin

include ../Makefile.env

