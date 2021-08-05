/*
 *	This file is part of LCQPow.
 *
 *	LCQPow -- A Solver for Quadratic Programs with Commplementarity Constraints.
 *	Copyright (C) 2020 - 2021 by Jonas Hall et al.
 *
 *	LCQPow is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	LCQPow is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with LCQPow; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <iostream>
#include "LCQProblem.hpp"

using namespace LCQPow;

int main() {
    std::cout << "Preparing Maximum Penalty Test...\n";

    /* Setup data of first QP. */
    double H[2*2] = { 2.0, 0.0, 0.0, 2.0 };
    double g[2] = { -2.0, -2.0 };
    double S1[1*2] = {1.0, 0.0};
    double S2[1*2] = {0.0, 1.0};

    double x0[2] = {1.0, 1.0};
    double y0[4] = {0.0, 0.0, 0.0, 0.0};

    int nV = 2;
    int nC = 0;
    int nComp = 1;

    LCQProblem lcqp( nV, nC, nComp );

	Options options;
    options.setPrintLevel(PrintLevel::INNER_LOOP_ITERATES);
    options.setQPSolver(QPSolver::QPOASES_DENSE);
    options.setMaxRho( 1 );
	lcqp.setOptions( options );

    // Solve first LCQP
	ReturnValue retVal = lcqp.loadLCQP( H, g, S1, S2, 0, 0, 0, 0, 0, 0, 0, 0, 0, x0, y0);

    if (retVal != SUCCESSFUL_RETURN)
    {
        printf("Failed to load LCQP.\n");
        return 1;
    }

    retVal = lcqp.runSolver();

    if (retVal == MAX_PENALTY_REACHED)
    {
        printf("Succeeded test (failed to solve LCQP due to maximal penalty).\n\n");
        return 0;
    }

    return 1;
}
