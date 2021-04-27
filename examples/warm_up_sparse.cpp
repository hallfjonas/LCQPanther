/*
 *	This file is part of lcqpOASES.
 *
 *	lcqpOASES -- A Solver for Quadratic Programs with Commplementarity Constraints.
 *	Copyright (C) 2020 - 2021 by Jonas Hall et al.
 *
 *	lcqpOASES is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	lcqpOASES is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with lcqpOASES; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <iostream>
#include "LCQProblem.hpp"

using namespace lcqpOASES;

int main() {
    std::cout << "Preparing warm up problem...\n";

    /* Setup data of first QP. */
    int H_nnx = 3;
    double H_data[3] = { 2.0, 2.0 };
    int H_i[3] = {0, 1};
    int H_p[3] = {0, 1, 2};

    double g[2] = { -2.0, -2.0 };

    int S1_nnx = 1;
    double S1_data[1] = { 1.0 };
    int S1_i[1] = {0};
    int S1_p[3] = {0, 1, 1};

    int S2_nnx = 1;
    double S2_data[1] = { 1.0 };
    int S2_i[1] = {0};
    int S2_p[3] = {0, 0, 1};

    int nV = 2;
    int nC = 0;
    int nComp = 1;

    LCQProblem lcqp( nV, nC, nComp );

	Options options;
    options.printLvl = printLevel::INNER_LOOP_ITERATES;
	lcqp.setOptions( options );

    // Solve first LCQP
	returnValue retVal = lcqp.loadLCQP( H_data, H_nnx, H_i, H_p, g, S1_data, S1_nnx, S1_i, S1_p, S2_data, S2_nnx, S2_i, S2_p );

    if (retVal != SUCCESSFUL_RETURN)
    {
        printf("Failed to load LCQP.\n");
        return 1;
    }

    retVal = lcqp.runSolver();

    if (retVal != SUCCESSFUL_RETURN)
    {
        printf("Failed to solve LCQP.\n");
        return 1;
    }

    // Get solutions
    double* xOpt = new double[2];
	double* yOpt = new double[nV + nC + 2*nComp];
	lcqp.getPrimalSolution( xOpt );
	lcqp.getDualSolution( yOpt );
	printf( "\nxOpt = [ %g, %g ];  yOpt = [ %g, %g ]; \n\n",
			xOpt[0],xOpt[1],yOpt[0],yOpt[1]);

    delete[] xOpt; delete[] yOpt;


    return 0;
}
