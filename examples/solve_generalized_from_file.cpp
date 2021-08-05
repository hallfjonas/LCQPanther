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
#include <fstream>
#include <LCQProblem.hpp>
#include <unistd.h>
#include <sys/stat.h>
#include <chrono>

bool PathExists(const std::string &s)
{
    struct stat buffer;
    return (stat (s.c_str(), &buffer) == 0);
}

int main() {

    std::cout << "Preparing optimization problem loaded from file...\n";

    std::string inputdir = "examples/example_data/generalized_constraints";

    if (!PathExists(inputdir)) {
        printf("Input directory does not exist.");
        return -1;
    }

    // Required files
    std::string H_file = inputdir + "/" + "H.txt";
    std::string g_file = inputdir + "/" + "g.txt";
    std::string lb_file = inputdir + "/" + "lb.txt";
    std::string ub_file = inputdir + "/" + "ub.txt";
    std::string S1_file = inputdir + "/" + "S1.txt";
    std::string S2_file = inputdir + "/" + "S2.txt";
    std::string lb_S1_file = inputdir + "/" + "lb_S1.txt";
    std::string lb_S2_file = inputdir + "/" + "lb_S2.txt";
    std::string ub_S1_file = inputdir + "/" + "ub_S1.txt";
    std::string ub_S2_file = inputdir + "/" + "ub_S2.txt";

    int nV = 0;
    int nC = 0;
    int nComp = 0;

    // Count dimensions
    std::string line;

    std::ifstream lbfile(lb_file);
    while (std::getline(lbfile, line))
        nV++;

    std::ifstream S1file(S1_file);
    while (std::getline(S1file, line))
        nComp++;

    nComp = nComp/nV;

    // Optional files
    std::string A_file = inputdir + "/" + "A.txt";
    std::string lbA_file = inputdir + "/" + "lbA.txt";
    std::string ubA_file = inputdir + "/" + "ubA.txt";
    std::string x0_file = inputdir + "/" + "x0.txt";
    std::string y0_file = inputdir + "/" + "y0.txt";

    const char* Af = 0;
    const char* lbAf = 0;
    const char* ubAf = 0;
    const char* x0f = 0;
    const char* y0f = 0;

    if (PathExists(A_file)) {
        Af = &A_file[0];

        std::ifstream Afile(A_file);
        while (std::getline(Afile, line))
            nC++;

        nC = nC/nV;
    }

    if (PathExists(lbA_file)) {
        lbAf = &lbA_file[0];
    }

    if (PathExists(ubA_file)) {
        ubAf = &ubA_file[0];
    }

    if (PathExists(lbA_file)) {
        lbAf = &lbA_file[0];
    }

    if (PathExists(ubA_file)) {
        ubAf = &ubA_file[0];
    }

    if (PathExists(x0_file)) {
        x0f = &x0_file[0];
    }

    if (PathExists(y0_file)) {
        y0f = &y0f[0];
    }

    LCQPow::LCQProblem lcqp( nV, nC, nComp );

    LCQPow::Options opts;
    opts.setPrintLevel( LCQPow::PrintLevel::INNER_LOOP_ITERATES );
    opts.setQPSolver( LCQPow::QPSolver::QPOASES_SPARSE);
    opts.setMaxIterations(19);
    lcqp.setOptions( opts );

    // Run solver
	LCQPow::ReturnValue ret = lcqp.loadLCQP( &H_file[0], &g_file[0], &S1_file[0], &S2_file[0], &lb_S1_file[0], &ub_S1_file[0], &lb_S2_file[0], &ub_S2_file[0], Af, lbAf, ubAf, &lb_file[0], &ub_file[0], x0f, y0f );

    if (ret != LCQPow::SUCCESSFUL_RETURN)
    {
        printf("Failed to load LCQP.\n");
        return 1;
    }

    ret = lcqp.runSolver();

    if (ret != LCQPow::SUCCESSFUL_RETURN)
    {
        printf("Failed to solve LCQP.\n");
        return 1;
    }

    return 0;
}
