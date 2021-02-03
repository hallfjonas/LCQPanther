﻿##
##	This file is part of lcqpOASES.
##
##	lcqpOASES -- A Solver for Quadratic Programs with Commplementarity Constraints.
##	Copyright (C) 2020 - 2021 by Jonas Hall et al.
##
##	lcqpOASES is free software; you can redistribute it and/or
##	modify it under the terms of the GNU Lesser General Public
##	License as published by the Free Software Foundation; either
##	version 2.1 of the License, or (at your option) any later version.
##
##	lcqpOASES is distributed in the hope that it will be useful,
##	but WITHOUT ANY WARRANTY; without even the implied warranty of
##	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
##	See the GNU Lesser General Public License for more details.
##
##	You should have received a copy of the GNU Lesser General Public
##	License along with lcqpOASES; if not, write to the Free Software
##	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
##



INTRODUCTION
============

lcqpOASES extends qpOASES with the recently proposed solution strategy for
Quadratic Programs with Complementarity Constraints. The approach is based on
a standard penalty homotopy reformulated using sequential convex programming.
The convex sequence derives from linearizing the (necessarily) nonconvex 
penalty function. This leads to a constant objective Hessian matrix throughout
all iterates, and thus enables us to solve the linear complementarity quadratic
program with a single factorization of the KKT matrix (by using qpOASES).



GETTING STARTED
===============


1. The whole software package can be obtained from 
      https://gitlab.syscop.de/jonas.hall/lcqpOASES

2. We provide a Dockerfile which installing lcqpOASES and running a first test example.
   For direct installation on your system refer to the steps taken in this Dockerfile.

2. The file LICENSE.txt contains a copy of the GNU Lesser General Public 
   License (v2.1). Please read it carefully before using lcqpOASES!




CONTACT THE AUTHORS
===================

If you have got questions, remarks or comments on lcqpOASES, it is strongly 
encouraged to report them by creating a new ticket at the lcqpOASES webpage.

Finally, you may contact one of the main authors directly:

        Jonas Hall,  hall.f.jonas@gmail.com

Also bug reports, source code enhancements or success stories are most welcome!


##
##	end of file
##
