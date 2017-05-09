VPATH=./include
TOPDIR=$(shell pwd )
export BINPATH =$(TOPDIR)/bin
export TESTPATH=$(TOPDIR)/testbin
export LIBPATH=$(TOPDIR)/lib
ALLBINS=
ALLLIBS=
ALLTESTBINS=

include Makefile.env

