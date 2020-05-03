#
# Makefile
#

CIRCLEHOME = ../..

OBJS	= Main.o Kernel.o

LIBS	= $(CIRCLEHOME)/lib/sched/libsched.a \
	  $(CIRCLEHOME)/lib/libcircle.a \
	  $(CIRCLEHOME)/addon/linux/liblinuxemu.a

include ../Rules.mk

-include $(DEPS)