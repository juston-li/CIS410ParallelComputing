############################################################################
# 
# @file src/Makefile
# @Author James Kress
# @date 10/2/2013
# @version 1.00
# @copyright KressEnterprisesInternational - All Rights Reserved
# @description This is the src makefile for BSplines
#
# $Id: Makefile 122 2014-01-22 00:07:00Z kirk $
#
############################################################################

prog:=pipeline_serial
objs:=$(patsubst %.c,%.o,$(wildcard *.cpp))

cc=icpc
ccflags= -MMD -g -Wall
ldflags= -lopencv_core -lopencv_highgui -lopencv_imgproc

%.o: %.c
	$(cc) $(ccflags) -c $<

$(prog): $(objs)
	$(cc) $(ccflags) -o $@ $^ $(ldflags)


.PHONY: clean

clean:
	rm -f garbleVideo *.o *.d counts* *.output *~ $(prog) 
	
-include *.d

# vim: set ts=4: #