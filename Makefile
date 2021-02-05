##
##	This file is part of qpOASES.
##
##	qpOASES -- An Implementation of the Online Active Set Strategy.
##	Copyright (C) 2007-2017 by Hans Joachim Ferreau, Andreas Potschka,
##	Christian Kirches et al. All rights reserved.
##
##	qpOASES is free software; you can redistribute it and/or
##	modify it under the terms of the GNU Lesser General Public
##	License as published by the Free Software Foundation; either
##	version 2.1 of the License, or (at your option) any later version.
##
##	qpOASES is distributed in the hope that it will be useful,
##	but WITHOUT ANY WARRANTY; without even the implied warranty of
##	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
##	See the GNU Lesser General Public License for more details.
##
##	You should have received a copy of the GNU Lesser General Public
##	License along with qpOASES; if not, write to the Free Software
##	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
##



##
##	Filename:  Makefile
##	Author:    Hans Joachim Ferreau
##	Version:   3.2
##	Date:      2007-2017
##

include make.mk

##
##	targets
##


all: src examples
#src_aw testing

src:
	@cd $@; ${MAKE} -s 

examples: src
	@cd $@; ${MAKE} -s

doc:
	@cd $@; ${MAKE} -s 

test:
	@mkdir -p ${BUILDDIR}
	@cd build && ${CMAKE} .. 
	@cd build && ${MAKE}
	build/TestUtils

debugging:
	@cd $@; ${MAKE} -s 

clean:
	@cd src               && ${MAKE} -s clean
	@cd examples          && ${MAKE} -s clean
	@${ECHO} "Cleaning up (debug)"  && ${RM} -rf debug
	@${ECHO} "Cleaning up (bin)"  && ${RM} -rf bin	
	@${ECHO} "Cleaning up (build)"  && ${RM} -rf build	

clobber: clean

.PHONY : all src examples doc testing debugging clean clobber


##
##   end of file
##
