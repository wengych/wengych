#Makefile

TOPDIR=../..
RULEDIR=$(TOPDIR)/Rule/$(OSNAME)

## must define env for var :CCTYPE(CC,CXX)                                 ##
ifeq ("x$(CCTYPE)","x")
include $(RULEDIR)/CCTYPE
endif

HEADER= ${TOPDIR}/include/macro.h \
        ${TOPDIR}/include/define.h \
        ${TOPDIR}/include/rtncode.h \
        ${TOPDIR}/include/fedef.h \
        ${TOPDIR}/include/fecom.h \
        ${TOPDIR}/include/ysdef.h \
        ${TOPDIR}/include/ysrtn.h \
        ${TOPDIR}/include/ysmacro.h \
        ${TOPDIR}/include/ysvar.h \
        ${TOPDIR}/include/yscom.h 
INCLIB=
INCINC=
OBJFLAG=
BINFLAG=

# g++ 
TARGET1=libyscom.so
TARGET=$(TARGET1)

##  objects
OBJ-$(TARGET1)=yspkg.o \
    ysvar.o \
    ysarray.o \
    ysfifo.o \
    userbus.o 

## objects(.pc)
SRCPC=

include $(RULEDIR)/Libso.Rule
#include $(RULEDIR)/Liba.Rule
#include $(RULEDIR)/Bin.Rule

