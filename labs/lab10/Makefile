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
ccflags= -MMD -g -Wall -std=c++11
ldflags= -lopencv_core -lopencv_highgui -lopencv_imgproc

#%.o: %.c
#	$(cc) $(ccflags) -c $<
all: pipeline_serial pipeline_tbb

pipeline_serial: pipeline_serial.cpp
	$(cc) $(ccflags) -o $@ $^ $(ldflags)

pipeline_tbb: pipeline_tbb.cpp
	$(cc) $(ccflags) -o $@ $^ $(ldflags) -ltbb


.PHONY: clean

clean:
	rm -f garbleVideo *.o *.d counts* *.output *~ $(prog) 
	
-include *.d

# vim: set ts=4: #
