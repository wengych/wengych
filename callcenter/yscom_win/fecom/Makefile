#Makefile

TOPDIR=../..
RULEDIR=$(TOPDIR)/Rule/$(OSNAME)

## must define env for var :CCTYPE(CC,CXX)                                 ##
ifeq ("x$(CCTYPE)","x")
include $(RULEDIR)/CCTYPE
endif

#HEADER= ${TOPDIR}/include/macro.h \
#        ${TOPDIR}/include/define.h \
#        ${TOPDIR}/include/rtncode.h \
#        ${TOPDIR}/include/fedef.h \
#        ${TOPDIR}/include/fecom.h  \
#        ${TOPDIR}/include/fevar.h  \
#        log.h \
#        md5.h \
#        unicode2gbk.h \
#        var.h 
HEADER=
INCLIB=
INCINC=-I./var
OBJFLAG=
BINFLAG=

# g++ 
TARGET1=libfecom.so
TARGET=$(TARGET1)

##  objects
OBJ-$(TARGET1)=string.o \
    des.o \
    md5.o \
    hashfunc.o \
    unicode2gbk.o \
    unicode2utf8.o \
    gbkcheck.o \
    vartools.o \
    varinfo.o \
    vartype.o \
    varstype.o \
    varpointer4.o \
    varbin.o \
    varstring.o \
    varobject.o \
    varfunc.o \
    varroot.o \
    vararray.o \
    varfifo.o \
    varfilo.o \
    varlink.o \
    varhash.o \
    var.o \
    pack.o \
    keyvalue.o

## objects(.pc)
SRCPC=

include $(RULEDIR)/Libso.Rule
#include $(RULEDIR)/Liba.Rule
#include $(RULEDIR)/Bin.Rule

